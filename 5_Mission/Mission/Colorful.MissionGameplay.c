modded class MissionGameplay extends MissionBase
{
	WrapSpacerWidget m_BadgesPanel;

	Widget m_CompassFrame;
	TextWidget m_CardinalDirection;
	TextWidget m_Heading;
	int m_CurrentPlayerDirection;
	string m_CurrentPlayerCardinalDirection;

	Widget m_HealthStatsFrame;
	Widget m_FoodStatsFrame;
	TextWidget m_HealthValueText;
	TextWidget m_BloodValueText;
	TextWidget m_ThirstValueText;
	TextWidget m_HungerValueText;
	ref array<TextWidget> m_HealthWidgets;

	Man m_Player;
	PlayerBase m_PlayerBase;
	int m_CurrentHealth;
	int m_CurrentBlood;
	int m_CurrentThisrt;
	int m_CurrentHunger;

    override void OnInit() 
    {
        super.OnInit();
		m_UIManager 	= GetGame().GetUIManager();
		m_Player 		= GetGame().GetPlayer();
		m_PlayerBase	= PlayerBase.Cast( m_Player );
 
		m_HealthWidgets = new array<TextWidget>;

        // if ( m_HudRootWidget )
        //     m_HudRootWidget.Unlink();


		if ( m_HudRootWidget )
		{
			m_HudRootWidget	= GetGame().GetWorkspace().CreateWidgets("Colorful-HUD/GUI/layouts/Colorful.day_z_hud.layout");
			m_HudRootWidget.Show(true);	
			m_Chat.Init(m_HudRootWidget.FindAnyWidget("ChatFrameWidget"));
			m_ActionMenu.Init( m_HudRootWidget.FindAnyWidget("ActionsPanel"), TextWidget.Cast( m_HudRootWidget.FindAnyWidget("DefaultActionWidget") ) );	
			m_Hud.Init( m_HudRootWidget.FindAnyWidget("HudPanel") );
			m_MicrophoneIcon = ImageWidget.Cast( m_HudRootWidget.FindAnyWidget("mic") );
			m_MicrophoneIcon.Show(false);
			m_VoiceLevels = m_HudRootWidget.FindAnyWidget("VoiceLevelsPanel");
			m_VoiceLevelsWidgets = new map<int, ImageWidget>; 
			m_VoiceLevelTimers = new map<int,ref WidgetFadeTimer>; 
		
			if ( m_VoiceLevels )
			{
				m_VoiceLevelsWidgets.Set(VoiceLevelWhisper, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Whisper") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelTalk, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Talk") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelShout, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Shout") ));			
				m_VoiceLevelTimers.Set(VoiceLevelWhisper, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelTalk, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelShout, new WidgetFadeTimer);
			}
			
			HideVoiceLevelWidgets();

			m_ChatChannelArea				= m_HudRootWidget.FindAnyWidget("ChatChannelPanel");
			m_ChatChannelText				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("ChatChannelText"));
			m_CompassFrame 					= Widget.Cast(m_HudRootWidget.FindAnyWidget("CompassFrame"));
			m_CardinalDirection				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("CardinalDirection"));
			m_Heading						= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("Heading"));
			m_HealthStatsFrame				= Widget.Cast(m_HudRootWidget.FindAnyWidget("HealthStatsFrame"));
			m_HealthValueText				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("HealthValueText"));
			m_BloodValueText				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("BloodValueText"));
			m_FoodStatsFrame				= Widget.Cast(m_HudRootWidget.FindAnyWidget("FoodStatsFrame"));
			m_ThirstValueText				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("ThirstValueText"));
			m_HungerValueText				= TextWidget.Cast(m_HudRootWidget.FindAnyWidget("HungerValueText"));
			m_BadgesPanel 					= WrapSpacerWidget.Cast(m_HudRootWidget.FindAnyWidget("BadgesPanel"));

			m_HealthWidgets.Insert(m_BloodValueText);
			m_HealthWidgets.Insert(m_ThirstValueText);
			m_HealthWidgets.Insert(m_HungerValueText);
			m_HealthWidgets.Insert(m_HealthValueText);
			m_CompassFrame.Show(true);
		}
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdatePlayerHUDCompass, 75, true);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdatePlayerHUD, 150, true);
    }

	void ~MissionGameplay() 
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.UpdatePlayerHUDCompass);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.UpdatePlayerHUD);
	}

	int CalculateColor( Widget widget, int val ) {
		if ( !val && !widget ) return ARGB( 255, 255, 255, 255 );
		float alpha = widget.GetAlpha();

		switch (true) {
			case( val >= 85 ): {
				return ARGB( 255, 255, 255, 255 );
				break;
			}
			case( val < 85 && val >= 80 ): {
				return ARGB( 255, 247, 226, 126 );
				break;
			}
			case( val < 80 && val >= 70 ): {
				return ARGB( 255, 234, 199, 42 );
				break;
			}
			case( val < 70 && val >= 60 ): {
				return ARGB( 255, 234, 199, 42 );  
				break;
			}
			case( val < 60 && val >= 50 ): {
				return ARGB( 255, 250, 175, 74 );  
				break;
			}
			case( val < 50 && val >= 40 ): {
				return ARGB( 255, 241, 144, 24 );  
				break;
			}
			case( val < 40 && val >= 30 ): {
				return ARGB( 255, 255, 99, 99 );	
				break;
			}
			case( val < 30 && val >= 20 ): {
				return ARGB( 255, 204, 51, 51 );  
				break;
			}
			case( val < 20 && val >= 10 ): {
				return ARGB( 255, 204, 51, 51 ); 
				break;
			}
			case( val < 10 && val >= 0 ): {
				return ARGB( 255, 204, 51, 51 );  
				break;
			}
			default: {}
		}
		return ARGB( 255, 255, 255, 255 );
	}

	void UpdatePlayerHUDCompass() 
	{
		m_Player 		= GetGame().GetPlayer();
		m_PlayerBase	= PlayerBase.Cast( m_Player );
		
		if ( !m_PlayerBase ) 
			return;

		m_CurrentPlayerDirection 			= m_PlayerBase.calculatePlayerDirectionDegrees();
		m_CurrentPlayerCardinalDirection 	= m_PlayerBase.calculatePlayerCardinalDirection( m_CurrentPlayerDirection );

		m_Heading.SetText( m_CurrentPlayerDirection.ToString() + "°" );
		m_CardinalDirection.SetText( m_CurrentPlayerCardinalDirection );
	}

	void UpdatePlayerHUD() 
	{
		m_Player	  = GetGame().GetPlayer();
		m_PlayerBase  = PlayerBase.Cast( m_Player );
		
		if (!m_Player) 
			return;
	
		m_CurrentHealth = m_PlayerBase.GetPlayerHealth();
		m_CurrentBlood 	= m_PlayerBase.GetPlayerBlood();
		m_CurrentThisrt = m_PlayerBase.GetPlayerWater();
		m_CurrentHunger = m_PlayerBase.GetPlayerFood();

		for ( int i = 0; i < m_HealthWidgets.Count(); i++ )
		{
			auto m_StatWidget = m_HealthWidgets[i];
			switch(m_StatWidget.GetName()) 
			{
				case "HealthValueText": 
				{
					m_StatWidget.SetText(string.Format("%1", m_CurrentHealth) + "%");
					m_StatWidget.SetColor(CalculateColor(m_StatWidget, m_CurrentHealth));
					break;
				}

				case "BloodValueText": 
				{
					m_StatWidget.SetText(string.Format("%1", m_CurrentBlood) + "%");
					m_StatWidget.SetColor(CalculateColor(m_StatWidget, m_CurrentBlood));
					break;
				}

				case "ThirstValueText": 
				{
					m_StatWidget.SetText(string.Format("%1", m_CurrentThisrt) + "%");
					m_StatWidget.SetColor(CalculateColor(m_StatWidget, m_CurrentThisrt));
					break;
				}

				case "HungerValueText": 
				{
					m_StatWidget.SetText(string.Format("%1", m_CurrentHunger) + "%");
					m_StatWidget.SetColor(CalculateColor(m_StatWidget, m_CurrentHunger));
					break;
				}
			}
		}
	}
};

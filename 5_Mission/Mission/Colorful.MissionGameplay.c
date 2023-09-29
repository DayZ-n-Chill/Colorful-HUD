modded class MissionGameplay
{
	WrapSpacerWidget m_BadgesPanel;

	Widget m_CompassFrame;
	ImageWidget m_CompassArrow;
	TextWidget m_CardinalDirection;
	TextWidget m_Heading;

	Widget m_HealthStatsFrame;
	Widget m_FoodStatsFrame;
	TextWidget m_HealthValueText;
	TextWidget m_BloodValueText;
	TextWidget m_ThirstValueText;
	TextWidget m_HungerValueText;
	ref array<TextWidget> m_HealthWidgets;

	private static PlayerBase m_Player;

	static int WHITE_COLOR 			= ARGB(255, 255, 255, 255);
	static int LIGHT_YELLOW_COLOR 	= ARGB(255, 247, 226, 126);
	static int YELLOW_COLOR 		= ARGB(255, 234, 199, 42);
	static int ORANGE_COLOR 		= ARGB(255, 250, 175, 74);
	static int DARK_ORANGE_COLOR 	= ARGB(255, 241, 144, 24);
	static int DARK_RED_COLOR 		= ARGB(255, 204, 51, 51);

	static autoptr TStringArray CARDINAL_DIRECTIONS = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

    override void OnInit() 
    {
        super.OnInit();

		m_UIManager = GetGame().GetUIManager();
		CastPlayer();
 
		m_HealthWidgets = new array<TextWidget>;

		if ( m_HudRootWidget )
		{
			m_HudRootWidget	= GetGame().GetWorkspace().CreateWidgets("Colorful-HUD/GUI/layouts/Colorful.day_z_hud.layout");
			m_HudRootWidget.Show(true);

			m_Chat.Init( m_HudRootWidget.FindAnyWidget("ChatFrameWidget") );
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
			m_CompassArrow 					= ImageWidget.Cast(m_HudRootWidget.FindAnyWidget("CompassArrow"));
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

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdatePlayerInfo, 75, true);
    }

	void ~MissionGameplay() 
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdatePlayerInfo);
	}

	void UpdatePlayerInfo()
	{
		if (!CastPlayer())
			return;

		UpdatePlayerHUDCompass();
		UpdatePlayerHUD();
	}

	protected void UpdatePlayerHUDCompass()
	{
		if ( m_Hud.IsHudVisible() != m_CompassFrame.IsVisible() )
			m_CompassFrame.Show(m_Hud.IsHudVisible());

		int currentPlayerDirection = m_Player.GetDirectionInDegrees();
		string currentPlayerCardinalDirection = GetCardinalDirection( currentPlayerDirection );
		
		m_Heading.SetText( string.Format("%1", currentPlayerDirection) + "°" );
		m_CardinalDirection.SetText( currentPlayerCardinalDirection );
		m_CompassArrow.SetRotation( 0, 0, currentPlayerDirection );
	}

	protected void UpdatePlayerHUD() 
	{
		for ( int i = 0; i < m_HealthWidgets.Count(); i++ )
		{
			auto m_StatWidget = m_HealthWidgets[i];
			switch( m_StatWidget.GetName() ) 
			{
				case "HealthValueText":
				{
					int currentHealth = m_Player.GetClientHealthPercent();

					m_StatWidget.SetText(string.Format("%1", currentHealth) + "%");
					m_StatWidget.SetColor(CalculateColor(currentHealth));
					m_StatWidget.SetAlpha(1.0);
					break;
				}
				case "BloodValueText":
				{
					int currentBlood = m_Player.GetClientBloodPercent();

					m_StatWidget.SetText(string.Format("%1", currentBlood) + "%");
					m_StatWidget.SetColor(CalculateColor(currentBlood));
					m_StatWidget.SetAlpha(1.0);
					break;
				}
				case "ThirstValueText":
				{
					int currentThisrt = m_Player.GetClientThirstPercent();

					m_StatWidget.SetText(string.Format("%1", currentThisrt) + "%");
					m_StatWidget.SetColor(CalculateColor(currentThisrt));
					m_StatWidget.SetAlpha(1.0);
					break;
				}
				case "HungerValueText":
				{
					int currentHunger = m_Player.GetClientEnergyPercent();

					m_StatWidget.SetText(string.Format("%1", currentHunger) + "%");
					m_StatWidget.SetColor(CalculateColor(currentHunger));
					m_StatWidget.SetAlpha(1.0);
					break;
				}
			}
		}
	}

	// Val is meant to be between 0 and 100
	static int CalculateColor(int val)
	{
		if (val >= 85)
			return WHITE_COLOR;
		else if (val >= 80)
			return LIGHT_YELLOW_COLOR;
		else if (val >= 70)
			return YELLOW_COLOR;
		else if (val >= 50)
			return ORANGE_COLOR;
		else if (val >= 40)
			return DARK_ORANGE_COLOR;
		else if (val >= 20)
			return DARK_RED_COLOR;

		// Default dark red color for values less than 20
		return DARK_RED_COLOR;
	}

	static bool CastPlayer()
	{
		if ( m_Player )
			return true;

		m_Player = PlayerBase.Cast(GetGame().GetPlayer());
		
		return m_Player != NULL;
	}

    static string GetCardinalDirection(int direction)
    {
		if (direction < 0 || direction > 360)
			return "ERROR: Invalid direction";

		// 360 / Amount of Slices (in this case 8) = 45
		// 360 / 45
		// now we want to offset everything so north start at 337 and not 0
		// so we grab half of 45
		// (360 + 22.5) / 45
		int index = Math.Floor(((direction + 22.5) / 45) );

		// prevents out of bound stuff
		if ( index > CARDINAL_DIRECTIONS.Count() - 1 )
			index -= CARDINAL_DIRECTIONS.Count();
		else if ( index < 0 )
			index = 0;
		
		return CARDINAL_DIRECTIONS[index];
    }
};

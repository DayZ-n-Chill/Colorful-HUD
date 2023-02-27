modded class ItemActionsWidget extends ScriptedWidgetEventHandler 
{
	override void Update()
	{
		if(!g_Game.GetProfileOption(EDayZProfilesOptions.HUD))
		{
			m_Root.Show(false);
			return;
		};

		if(m_Player && !m_Player.IsAlive())
		{
			m_Player = null;
			m_AM = null;
		}
		if(!m_Player) GetPlayer();
		if(!m_AM) GetActionManager();

		GetActions();
		GetEntityInHands();
		
		if((m_EntityInHands || m_Interact || m_ContinuousInteract || m_Single || m_Continuous) && GetGame().GetUIManager().GetMenu() == null)
		{
			CheckForActionWidgetOverrides();
			BuildCursor();
			CheckRefresherFlagVisibility();
			m_Root.Show(true);
		}
		else
		{
			if (m_Root.IsVisible())
			{
				m_Root.Show(false);
			}
		}
		m_MaxWidthChild = 200;
	}
};

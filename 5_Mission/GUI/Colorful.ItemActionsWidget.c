modded class ItemActionsWidget
{
	override void Update()
	{
    	// Check if HUD is enabled in the player's profile
		if(!g_Game.GetProfileOption(EDayZProfilesOptions.HUD))
		{
			m_Root.Show(false);
			return;
		}

    	// Reset player-related variables if the player is dead
		if(m_Player && !m_Player.IsAlive())
		{
			m_Player = null;
			m_AM = null;
		}

    	// Initialize player and action manager if not already done
		if(!m_Player)
			GetPlayer();

		if(!m_AM)
			GetActionManager();

    	// Retrieve actions and entity in the player's hands
		GetActions();
		GetEntityInHands();
		
		bool isDoingSomething = m_Interact || m_ContinuousInteract || m_Single || m_Continuous;

		// Check if the game menu is not open and there are interaction-related elements
    	if(GetGame().GetUIManager().GetMenu() == NULL && m_EntityInHands && !isDoingSomething)
		{
			CheckForActionWidgetOverrides();
			BuildCursor();
			CheckRefresherFlagVisibility();
			m_Root.Show(true);
		}
		else if (m_Root.IsVisible())
		{
			// Hide the HUD if no interaction-related elements are found or the menu is open
        	m_Root.Show(false);
		}
		
    	// Set the maximum width for child elements
		m_MaxWidthChild = 200;
	}
};
class BlowTablets_Mdfr: ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_IsPersistent = true;
		m_ID 					= SEModifiers.MDF_BLOWTABLETS;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnActivate(PlayerBase player)
	{		
		if( player.GetNotifiersManager() ) 
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
			player.SetHealth("GlobalHealth","Shock", 0);
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		if( player.GetNotifiersManager() ) 
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
	}
};
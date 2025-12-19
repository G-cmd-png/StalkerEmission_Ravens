modded class BlowTablets_Mdfr
{
	override bool DeactivateCondition(PlayerBase player)
	{
		return (!EmissionSystem.GetInstance().IsEmissionActive() && !EmissionSystem.GetInstance().IsWarningActive());
	}

    override void OnTick(PlayerBase player, float deltaT)
	{
		if (EmissionSystem.GetInstance().IsEmissionActive() || EmissionSystem.GetInstance().IsWarningActive())
		{
			player.SetHealth("GlobalHealth","Shock", 0);
		}
	}
};
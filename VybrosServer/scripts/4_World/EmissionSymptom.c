modded class EmissionSymptom extends SymptomBase
{
    protected float damageTick = 0.0;

    protected float damageEmission = EmissionGlobalSettings.DEFAULT_DAMAGE_PER_SECOND;

    override void OnUpdateServer( PlayerBase player, float deltatime )
    {
        damageTick = damageTick + deltatime;

        if ( damageTick >= 5 )
        {
            //原代码玩家伤害逻辑
            if ( player.IsInShelterSync() == false && !player.GetModifiersManager().IsModifierActive(SEModifiers.MDF_BLOWTABLETS))
            {
                player.AddHealth( -damageEmission );
            }

            // eAI伤害逻辑：玩家附近遍历
            array<Object> nearby = new array<Object>;
            GetGame().GetObjectsAtPosition(player.GetPosition(), 500, nearby, null);

            foreach (Object obj : nearby)
            {
                eAIBase ai = eAIBase.Cast(obj);
                if (ai && !ai.IsInShelterSync())
                {
                    ai.AddHealth(-damageEmission);
                }
            }

            damageTick = 0.0;
        }
    }

    override void OnGetDeactivatedServer(PlayerBase player)
	{
		player.GetModifiersManager().DeactivateModifier(SEModifiers.MDF_BLOWTABLETS);
	}
}

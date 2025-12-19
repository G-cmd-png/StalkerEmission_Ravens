modded class PlayerBase
{
    protected float ShelterTick = 0.0;

    bool IsInShelter()
    {
        vector rayStart = GetPosition();
        rayStart[1] = rayStart[1] + 0.5;
        
        vector rayEnd = rayStart;
        rayEnd[1] = rayEnd[1] + EmissionGlobalSettings.DEFAULT_SHELTER_CHECK_HEIGHT;
        
        vector contact_pos;
        vector contact_dir;
        int contact_component;
        
        return DayZPhysics.RaycastRV(rayStart, rayEnd, contact_pos, contact_dir, contact_component, null, null, this, false, false, ObjIntersectView, 0.0);
    }

    override void OnScheduledTick(float deltaTime)
	{
        super.OnScheduledTick(deltaTime);

        ShelterTick = ShelterTick + deltaTime;

        if (EmissionSystem.GetInstance().IsEmissionActive() || EmissionSystem.GetInstance().IsWarningActive())
        {
            if ( ShelterTick >= 2 )
            {
                if ( IsInShelter() )
                {
                    SetIsInShelter(true);
                }
                else
                {
                    SetIsInShelter(false);
                }

                ShelterTick = 0.0;
            }
        }
        
    }
} 
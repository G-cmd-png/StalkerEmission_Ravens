modded class eAIBase
{
    protected float ShelterTickAI = 0.0;
    protected bool m_IsInShelterAI;

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

        ShelterTickAI += deltaTime;

        if (EmissionSystem.GetInstance().IsEmissionActive() || EmissionSystem.GetInstance().IsWarningActive())
        {
            if (ShelterTickAI >= 2)
            {
                if (IsInShelter())
                {
                    m_IsInShelterAI = true;
                }
                else
                {
                    m_IsInShelterAI = false;
                }

                ShelterTickAI = 0.0;
            }
        }
    }

    bool IsInShelterSync()
    {
        return m_IsInShelterAI;
    }
}

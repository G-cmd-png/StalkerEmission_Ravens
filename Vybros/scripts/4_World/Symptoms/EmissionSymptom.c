modded class SymptomManager
{
    override void Init()
    {
        super.Init();

        RegisterSymptom( new EmissionSymptom );
    }
}

class EmissionSymptom extends SymptomBase
{
    protected ref PPERequester_EmissionEffect m_EmissionEffectRequester;

    const float CAMERASHAKE_TICK = 1.0;
    const float CAMERASHAKE_STRENGTH = 0.4;
    const float CAMERASHAKE_RADIUS = 2.0;
    const float CAMERASHAKE_SMOOTHNESS = 1.3;
    const float CAMERASHAKE_RADIUS_DECAY_SPEED = 1.4;

    protected float cameraShakeTick = 0.0;

    override void OnInit()
    {
        m_SymptomType = SymptomTypes.SECONDARY;
        m_Priority = 102;
        m_ID = EmissionSymptomsIDs.Emission;
        m_DestroyOnAnimFinish = true;
        m_SyncToClient = true;
        m_Duration = 200;
        m_IsPersistent = false;
    }

    override void OnGetActivatedClient( PlayerBase player )
    {
        EffectSound emissionStart;
        player.PlaySoundSet( emissionStart, "EmissionStartSoundSet", 0, 0 );
        emissionStart.SetSoundAutodestroy( true );

        if (!m_EmissionEffectRequester)
        {
            m_EmissionEffectRequester = PPERequester_EmissionEffect.Cast(PPERequesterBank.GetRequester(PPERequester_EmissionEffect));
        }
        
        if (m_EmissionEffectRequester)
        {
            m_EmissionEffectRequester.Start();
        }
    }

    override void OnGetActivatedServer( PlayerBase player )
    {
    }

    override void OnUpdateClient( PlayerBase player, float deltatime )
    {
        cameraShakeTick = cameraShakeTick + deltatime;
        if (cameraShakeTick >= CAMERASHAKE_TICK)
        {
            cameraShakeTick = 0.0;
            
            player.GetCurrentCamera().SpawnCameraShake(CAMERASHAKE_STRENGTH, CAMERASHAKE_RADIUS, CAMERASHAKE_SMOOTHNESS, CAMERASHAKE_RADIUS_DECAY_SPEED);
        }
    }

    override void OnGetDeactivatedClient( PlayerBase player )
    {
        player.GetCurrentCamera().SpawnCameraShake( 0, 0, 0, 0 );

        EffectSound emissionEnd;
        player.PlaySoundSet( emissionEnd, "EmissionEndSoundSet", 0, 0 );
        emissionEnd.SetSoundAutodestroy( true );

        if (m_EmissionEffectRequester)
        {
            m_EmissionEffectRequester.Stop();
        }
    }
}

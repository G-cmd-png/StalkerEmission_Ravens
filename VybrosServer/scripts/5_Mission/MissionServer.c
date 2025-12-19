modded class MissionServer
{
    private ref EmissionSystem m_EmissionSystem;

    override void OnInit()
    {
        super.OnInit();
        
        if (EmissionGlobalSettings.EnableEmissionSystem)
        {
            m_EmissionSystem = EmissionSystem.GetInstance();
        }
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        
        m_EmissionSystem.OnClientConnected(player);
    }
} 
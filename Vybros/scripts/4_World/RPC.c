class EmissionRPCHandler
{
    static const int RPC_EMISSION_WARNING = 60001;
    static const int RPC_EMISSION_START = 60002;
    static const int RPC_EMISSION_END = 60003;

    static void SendEmissionWarningToAll()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                SendEmissionWarningToPlayer(player);
            }
        }
    }
    
    static void SendEmissionWarningToPlayer(PlayerBase player)
    {
        if (player && player.GetIdentity())
        {
            GetGame().RPCSingleParam(player, RPC_EMISSION_WARNING, null, true, player.GetIdentity());
        }
    }
    
    static void SendEmissionStartToAll()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                SendEmissionStartToPlayer(player);
            }
        }
    }
    
    static void SendEmissionStartToPlayer(PlayerBase player)
    {
        if (player && player.GetIdentity())
        {
            GetGame().RPCSingleParam(player, RPC_EMISSION_START, null, true, player.GetIdentity());
        }
    }
    
    static void SendEmissionEndToAll()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                SendEmissionEndToPlayer(player);
            }
        }
    }
    
    static void SendEmissionEndToPlayer(PlayerBase player)
    {
        if (player && player.GetIdentity())
        {
            GetGame().RPCSingleParam(player, RPC_EMISSION_END, null, true, player.GetIdentity());
        }
    }
}
class EmissionSystem
{
    private static ref EmissionSystem m_Instance;

    bool m_IsEmissionActive;
    bool m_IsWarningActive;
    private bool m_IsEndingActive;
    private float m_EmissionStartTime;
    private float m_LastEmissionTime;
    private float m_NextEmissionTime;
    
    private ref array<Man> m_PlayersInEmission;
    private Weather m_Weather;
    
    void EmissionSystem()
    {
        m_IsEmissionActive = false;
        m_IsWarningActive = false;
        m_IsEndingActive = false;
        m_LastEmissionTime = 0;
        m_NextEmissionTime = EmissionGlobalSettings.DEFAULT_EMISSION_INTERVAL;
        m_PlayersInEmission = new array<Man>;
        
        m_Weather = GetGame().GetWeather();
        
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Update, 1000, true);
    }
    
    static EmissionSystem GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = new EmissionSystem();
        }
        return m_Instance;
    }

    bool IsEmissionActive()
    {
        return m_IsEmissionActive;
    }

    bool IsWarningActive()
    {
        return m_IsWarningActive;
    }
    
    void Update()
    {
        float currentTime = GetGame().GetTime() * 0.001; 

        if (!m_IsWarningActive && !m_IsEmissionActive && !m_IsEndingActive && (currentTime - m_LastEmissionTime >= m_NextEmissionTime))
        {
            //Print("=== Update: calling StartEmissionWarning V0.2 ===");
            StartEmissionWarning();
        }
        
        if (m_IsWarningActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION))
        {
            m_IsWarningActive = false;
            StartEmission();
        }
        
        if (m_IsEmissionActive && !m_IsEndingActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION + EmissionGlobalSettings.DEFAULT_EMISSION_DURATION))
        {
            m_IsEmissionActive = false;
            StartEmissionEnding();
        }
        
        if (m_IsEndingActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION + EmissionGlobalSettings.DEFAULT_EMISSION_DURATION + EmissionGlobalSettings.DEFAULT_ENDING_DURATION))
        {
            EndEmission();
        }
        //Print("=== EmissionSystem Update running V0.2 ===");
    }
    
    void StartEmissionWarning()
    {
        //Print("=== StartEmissionWarning triggered V0.2 ===");  // 确认方法真正执行
        m_IsWarningActive = true;
        m_EmissionStartTime = GetGame().GetTime() * 0.001;
        // 原代码天气效果
        m_Weather.GetRain().Set(0.2, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);
        m_Weather.GetFog().Set(0.5, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);
        m_Weather.GetOvercast().Set(0.8, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);

        m_Weather.SetStorm(1.0, 0.4, 8);
        
        EmissionRPCHandler.SendEmissionWarningToAll();

        // === 在警告阶段生成 Raven ===
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                vector pos = player.GetPosition();

                // 定义一次半径范围
                float radiusMin = 8.0;   // 最小水平距离，保证不贴脸生成Raven
                float radiusMax = 30.0;  // 最大水平距离

                // 每个玩家生成 8 只 Raven（要修改就改下面的数字8）
                for (int i = 0; i < 8; i++)
                {
                    // 随机角度
                    const float TWO_PI = 6.283185;
                    float angle = Math.RandomFloat(0, TWO_PI);

                    // 随机半径，保证至少 radiusMin
                    float radius = Math.RandomFloat(radiusMin, radiusMax);

                    float offsetX = Math.Cos(angle) * radius;
                    float offsetZ = Math.Sin(angle) * radius;

                    // 随机抬高，让乌鸦在空中生成
                    float offsetY = Math.RandomFloat(8, 20);

                    vector spawnPos = pos + Vector(offsetX, offsetY, offsetZ);

                    Object raven = GetGame().CreateObject("Animal_Raven_Airborne", spawnPos, false, true, true);
                    //Print("[Raven] Spawned near " + player.GetIdentity().GetName() + " at " + spawnPos);
                }
            }
        }
    }
    
    void StartEmission()
    {
        m_IsEmissionActive = true;
        
        m_Weather.GetRain().Set(1.0, 180, 180);
        m_Weather.GetFog().Set(0.9, 180, 180);
        m_Weather.GetOvercast().Set(1.0, 180, 180);

        m_Weather.SetStorm(1, 0.4, 2);
        
        EmissionRPCHandler.SendEmissionStartToAll();
        
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                player.GetSymptomManager().QueueUpSecondarySymptom(EmissionSymptomsIDs.Emission);

                // 喷发开始时杀死玩家附近的鸟类（我加入了Hunterz的渡鸦和海鸥的classname，若你有其他的动物要杀死，可以在下方typeName加入相应的classname。）
                array<Object> objects = new array<Object>;
                GetGame().GetObjectsAtPosition(player.GetPosition(), 500, objects, null);

                foreach (Object obj : objects)
                {
                    AnimalBase animal = AnimalBase.Cast(obj);
                    if (animal)
                    {
                        string typeName = animal.GetType();
                        if (typeName == "Animal_Seagull" || typeName == "Animal_Raven_Airborne" || typeName == "Animal_Raven2" || typeName == "Animal_Raven")
                        {
                            // 服务端直接清零生命值，立即死亡
                            animal.SetHealth("", "", 0.0);
                            Print("[CrowDebug] Bird killed by emission: " + typeName);
                        }
                    }
                }
            }
        }
    }

    void StartEmissionEnding()
    {
		m_IsEndingActive = true;
        
        EmissionRPCHandler.SendEmissionEndToAll();
        
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player)
            {
                player.GetSymptomManager().RemoveSecondarySymptom(EmissionSymptomsIDs.Emission);
            }
        }
        
        m_Weather.GetRain().Set(0.4, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);
        m_Weather.GetFog().Set(0.7, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);
        m_Weather.GetOvercast().Set(0.8, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);
        
        m_Weather.SetStorm(0.3, 0.7, 20);
    }
    
    void EndEmission()
    {
        m_IsEndingActive = false;
        m_LastEmissionTime = GetGame().GetTime() * 0.001;
        m_NextEmissionTime = EmissionGlobalSettings.DEFAULT_EMISSION_INTERVAL + Math.RandomFloat(-300, 300);
        
        m_Weather.GetRain().Set(0.1, 15, 0);
        m_Weather.GetFog().Set(0.5, 60, 0);
        m_Weather.GetOvercast().Set(0.6, 60, 0);
        
        m_Weather.SetStorm(0, 1.0, 60);
    }

    void OnClientConnected(PlayerBase player)
    {
        //Print("=== OnClientConnected triggered V0.2 ===");
        if (m_IsWarningActive)
        {
            EmissionRPCHandler.SendEmissionWarningToPlayer(player);
        }
        else if (m_IsEmissionActive)
        {
            EmissionRPCHandler.SendEmissionStartToPlayer(player);
            
            player.GetSymptomManager().QueueUpSecondarySymptom(EmissionSymptomsIDs.Emission);
        }
        else if (m_IsEndingActive)
        {
            EmissionRPCHandler.SendEmissionEndToPlayer(player);
        }
        // 调试：玩家上线时生成一只 Raven
        //DebugSpawnRaven(player);（本尝试始于该代码，就保留在这了）
    }
    
} 

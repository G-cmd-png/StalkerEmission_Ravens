modded class PlayerBase
{
    protected EffectSound Emissionrumble;
    protected bool m_IsInShelter;

    protected Widget m_HudShelterWidget;
    protected ImageWidget m_ShelterIcon;

    protected float ShelterTickClient = 0.0;

    // 乌鸦预警最小延迟逻辑变量
    protected bool m_CrowDelayActive = false;
    protected float m_CrowDelayTimer = 0.0;
    protected float m_CrowDelayThreshold = 20.0; // 默认值， 20 秒后播放下一阶段
    protected int m_LastDelayPrintSecond = -1;   // 缓存变量，避免重复打印

    override void Init()
	{
        //确认脚本加载
        //Print("[CrowDebug] PlayerBase Init loaded");
        
        super.Init();

        RegisterNetSyncVariableBool("m_IsInShelter");
    }
    
    bool IsInShelterSync()
    {
        return m_IsInShelter;
    }
    
    void SetIsInShelter(bool value)
    {
        m_IsInShelter = value;
        
        if (GetGame().IsServer())
        {
            SetSynchDirty();
        }
    }
    
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);
        
        switch (rpc_type)
        {
            case EmissionRPCHandler.RPC_EMISSION_WARNING:
                if (GetGame().IsClient())
                {
                    if (!m_HudShelterWidget)
                    {
                        m_HudShelterWidget = GetGame().GetWorkspace().CreateWidgets("Vybros/data/hudshelter.layout");
                        m_ShelterIcon = ImageWidget.Cast(m_HudShelterWidget.FindAnyWidget("Shelter"));
                        
                        if (m_ShelterIcon)
                        {
                            m_ShelterIcon.Show(false);
                        }
                    }

                    // 乌鸦预警轮次：启动一次性延迟播放
                    m_CrowDelayActive = true;
                    m_CrowDelayTimer = 0.0;
                    m_CrowDelayThreshold = 30.0; // 可调，xx秒后播放下一阶段

                    // 延迟启动预警音效和 rumble
                    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PlayEmissionWarning, 31000, false); // 31000毫秒后启动预警音频
                }
                break;
                
            case EmissionRPCHandler.RPC_EMISSION_START:
                if (GetGame().IsClient())
                {
                    // 调试输出：确认喷发开始
                    //Print("[CrowDebug] RPC_EMISSION_START received ++ emission begins, stopping crow timeline");
                    
                    // 移除定时器/CallQueue，防止残留调用
                    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.PlayEmissionWarning);
                    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.PlayCrow);
                    
                    // 重置乌鸦预警轮次变量，保证下次预警干净
                    m_CrowDelayActive = false;
                    m_CrowDelayTimer = 0.0;
                    m_CrowStage = 0;
                }
                break;
                
            case EmissionRPCHandler.RPC_EMISSION_END:
                if (GetGame().IsClient())
                {
                    // 调试输出：确认喷发结束
                    //Print("[CrowDebug] RPC_EMISSION_END received ++ emission ends, cleaning up crow timeline");

                    StopSoundSet( Emissionrumble );

                    if (m_HudShelterWidget)
                    {
                        m_HudShelterWidget.Unlink();
                        m_HudShelterWidget = null;
                        m_ShelterIcon = null;
                    }
                    m_CrowDelayActive = false;
                    m_CrowDelayTimer = 0.0;
                    m_CrowStage = 0;
                }
                break;
        }
             


    }

    //当前乌鸦预警轮次处于第几个阶段
    protected int m_CrowStage = 0;

    override void OnScheduledTick(float deltaTime)
	{
        super.OnScheduledTick(deltaTime);

        // 原版：HUD shelter 更新逻辑
        ShelterTickClient += deltaTime;

        if (GetGame().IsClient())
        {
            if ( ShelterTickClient >= 2 )
            {
                if (m_ShelterIcon)
                {
                    if (IsInShelterSync())
                    {
                        m_ShelterIcon.Show(true);
                    }
                    else
                    {
                        m_ShelterIcon.Show(false);
                    }
                }

                ShelterTickClient = 0.0;
            }

            // === 乌鸦预警轮次延迟逻辑 ===
        if (m_CrowDelayActive)
            {
                m_CrowDelayTimer += deltaTime;

                    int currentSecond = Math.Floor(m_CrowDelayTimer);
                    if (currentSecond % 5 == 0 && currentSecond != m_LastDelayPrintSecond)
                    {
                        Print("[CrowDebug] Delay timer = " + currentSecond + "s, Stage=" + m_CrowStage);
                        m_LastDelayPrintSecond = currentSecond;
                    }

                    if (m_CrowStage == 0 && m_CrowDelayTimer >= 0)
                    {
                        PlayCrow("EmissionCrowVeryFar_SoundSet");
                        m_CrowStage = 1;
                        m_CrowDelayTimer = 0.0;
                    }
                    else if (m_CrowStage == 1 && m_CrowDelayTimer >= 30)
                    {
                        PlayCrow("EmissionCrowFar_SoundSet");
                        m_CrowStage = 2;
                        m_CrowDelayTimer = 0.0;
                    }
                    else if (m_CrowStage == 2 && m_CrowDelayTimer >= 60)
                    {
                        PlayCrow("EmissionCrowPrettyFar_SoundSet");
                        m_CrowStage = 3;
                        m_CrowDelayTimer = 0.0;
                    }
                    else if (m_CrowStage == 3 && m_CrowDelayTimer >= 90)
                    {
                        PlayCrow("EmissionCrowMedium_SoundSet");
                        m_CrowStage = 4;
                        m_CrowDelayTimer = 0.0;
                    }
                    else if (m_CrowStage == 4 && m_CrowDelayTimer >= 120)
                    {
                        PlayCrow("EmissionCrowCloseMedium_SoundSet");
                        m_CrowStage = 5;
                        m_CrowDelayTimer = 0.0;
                    }
                    else if (m_CrowStage == 5 && m_CrowDelayTimer >= 150)
                    {
                        PlayCrow("EmissionCrowClose_SoundSet");
                        m_CrowDelayActive = false; // 完成后关闭
                    }
                }
            }
        }
    // 播放一次性乌鸦音效，自动销毁
    void PlayCrow(string soundSetName)
    {
        vector playerPos = GetPosition();
        // 随机方向在玩家附近 30 米生成乌鸦声
        float angle = Math.RandomFloat(0, Math.PI2);
        vector dir = Vector(Math.Cos(angle), 0, Math.Sin(angle));
        vector soundPos = playerPos + (dir * 30);

        EffectSound crowSound;
        PlaySoundSet(crowSound, soundSetName, 0, 0);
        crowSound.SetPosition(soundPos);
        crowSound.SetSoundAutodestroy(true);

        //Print("[CrowDebug] PlayCrow at " + soundPos.ToString() + " (random 30m around player)");
    }

    void PlayEmissionWarning()
    {
        // 播放预警音效
        EffectSound emissionWarn;
        PlaySoundSet(emissionWarn, "EmissionWarningSoundSet", 0, 0);
        emissionWarn.SetSoundAutodestroy(true);

        // 播放循环 rumble 背景音
        PlaySoundSetLoop(Emissionrumble, "EmissionRumbleSoundSet", 0.0, 1.0);

        // 创建 HUD shelter 图标
        if (!m_HudShelterWidget)
        {
            m_HudShelterWidget = GetGame().GetWorkspace().CreateWidgets("Vybros/data/hudshelter.layout");
            m_ShelterIcon = ImageWidget.Cast(m_HudShelterWidget.FindAnyWidget("Shelter"));

            if (m_ShelterIcon)
            {
                m_ShelterIcon.Show(false);
            }
        }

        //Print("[CrowDebug] Emission warning + rumble started after crow delay");
    }

} 
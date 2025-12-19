class EmissionGlobalSettings
{
    // Interval between emissions in seconds (default: 2 hours/7200)
    static const float DEFAULT_EMISSION_INTERVAL = 2700;   // 45 分钟 = 2700 秒
    
    // Duration of the warning before emission in seconds
    static const float DEFAULT_WARNING_DURATION = 200;   // 预警，建议200秒或以上。我没有多次测试过少于200秒乌鸦声的轮次会怎么样
    
    // Emit duration in seconds (default is 5 minutes)
    static const float DEFAULT_EMISSION_DURATION = 300;   // 喷发持续 5 分钟，上个洗手间吧（笑
    
    // Duration of the recovery phase after emission in seconds
    static const float DEFAULT_ENDING_DURATION = 120;   // 恢复期 2 分钟
    
    // Damage per second during emission without cover
    static const float DEFAULT_DAMAGE_PER_SECOND = 30.0;   //每 5 秒扣 30 点生命值。屋外暴露大约 15–20 秒就会死亡。
    
    // Maximum height of cover check (meters above the player)
    static const float DEFAULT_SHELTER_CHECK_HEIGHT = 30.0;   // 默认即可，检测建筑物高度
    
    // The flag for enabling/disabling the emission system
    static bool EnableEmissionSystem = true;   // 默认即可，开启喷发系统


    /*
    Original Author: Venatus, Hunterz
    Secondary Creator: Snake_Vista
    
    本模组以 Venatus: StalkerEmission 为基础，搭配动物模组 Hunterz: DayZ-Raven 制作而成。 感谢互联网开源精神，让我们能够在 DayZ 世界中创造更真实、更沉浸的末日体验。
    English: This mod is built upon Venatus: StalkerEmission, combined with the animal mod Hunterz: DayZ-Raven. Special thanks to the spirit of open-source on the internet, which makes it possible to create a more authentic and immersive post-apocalyptic experience in DayZ.
    */

} 
class CfgPatches
{
	class Vybros
	{
		units[]={};
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
		weapons[]={};
	};
};
class CfgMods
{
	class Vybros
	{
		type="mod";
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"Vybros\data\Vybros.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"Vybros/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"Vybros/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"Vybros/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgSoundSets
{
	class baseSoundSet;
	class baseCharacter_SoundSet;
	class EmissionWarningSoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"EmissionWarningSoundShader"
		};
	};
	class EmissionStartSoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"EmissionStartSoundShader"
		};
	};
	class EmissionEndSoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"EmissionEndSoundShader"
		};
	};
	class EmissionRumbleSoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"EmissionRumbleSoundShader"
		};
	};
	// 乌鸦音效空间化 （我希望spatial有用）
    class EmissionCrowClose_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowClose_SoundShader" };
    };
    class EmissionCrowCloseMedium_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowCloseMedium_SoundShader" };
    };
    class EmissionCrowMedium_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowMedium_SoundShader" };
    };
    class EmissionCrowFar_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowFar_SoundShader" };
    };
    class EmissionCrowPrettyFar_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowPrettyFar_SoundShader" };
    };
    class EmissionCrowVeryFar_SoundSet: baseSoundSet
    {
        spatial = 1;
        loop = 0;
        soundShaders[] = { "EmissionCrowVeryFar_SoundShader" };
    };
};
class CfgSoundShaders
{
	class EmissionWarningSoundShader
	{
		samples[]=
		{
			
			{
				"Vybros\Sounds\warn",
				1
			}
		};
		volume=1;
	};
	class EmissionStartSoundShader
	{
		samples[]=
		{
			
			{
				"Vybros\Sounds\start",
				1
			}
		};
		volume=1;
	};
	class EmissionEndSoundShader
	{
		samples[]=
		{
			
			{
				"Vybros\Sounds\end",
				1
			}
		};
		volume=1;
	};
	class EmissionRumbleSoundShader
	{
		samples[]=
		{
			
			{
				"Vybros\Sounds\rumble",
				1
			}
		};
		volume=1;
	};
	//乌鸦音效
	class EmissionCrowClose_SoundShader
    {
        samples[] = { { "Vybros\Sounds\close", 1 } };
        volume = 1;
		range = 60;
		fadeOut = 1; // 声音结束前淡出 1 秒
    };
    class EmissionCrowCloseMedium_SoundShader
    {
        samples[] = { { "Vybros\Sounds\closemedium", 1 } };
        volume = 1;
		range = 80;
		fadeOut = 1; // 声音结束前淡出 1 秒
    };
    class EmissionCrowMedium_SoundShader
    {
        samples[] = { { "Vybros\Sounds\medium", 1 } };
        volume = 1;
		range = 100;
		fadeOut = 1; // 声音结束前淡出 1 秒
    };
    class EmissionCrowFar_SoundShader
    {
        samples[] = { { "Vybros\Sounds\far", 1 } };
        volume = 1;
		range = 120;
		fadeOut = 2; // 声音结束前淡出 2 秒
    };
    class EmissionCrowPrettyFar_SoundShader
    {
        samples[] = { { "Vybros\Sounds\prettyfar", 1 } };
        volume = 1;
		range = 150;
		fadeOut = 2; // 声音结束前淡出 2 秒
    };
    class EmissionCrowVeryFar_SoundShader
    {
        samples[] = { { "Vybros\Sounds\veryfar", 1 } };
        volume = 1;
		range = 200;
		fadeOut = 2; // 声音结束前淡出 2 秒
    };
};
class CfgVehicles
{
	class Inventory_Base;
	class BlowTablets: Inventory_Base
	{
		scope=2;
		displayName="$STR_CfgBlowTablets0";
		descriptionShort="$STR_CfgBlowTablets1";
		model="\dz\gear\medical\painkillers2.p3d";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"Vybros\data\anabiotik_co.paa"};
		hiddenSelectionsMaterials[] = {"DZ\gear\medical\data\painkiller2.rvmat"};
		itemSize[]={1,2};
		canBeSplit=1;
		varQuantityInit=12;
		varQuantityMin=0;
		varQuantityMax=12;
		varQuantityDestroyOnMin=1;
		varTemperatureMax=1;
		weight=20;
		weightPerQuantityUnit=2;
		stackedUnit="pills";
		quantityBar=0;
		absorbency=0.69999999;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=30;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\medical\data\painkiller2.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\medical\data\painkiller2.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\medical\data\painkiller2_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\medical\data\painkiller2_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\medical\data\painkiller2_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Tablets_open
				{
					soundSet="Tablets_open_SoundSet";
					id=201;
				};
				class Tablets_catch
				{
					soundSet="Tablets_catch_SoundSet";
					id=202;
				};
				class Tablets_close
				{
					soundSet="Tablets_close_SoundSet";
					id=203;
				};
				class pickup
				{
					soundSet="purificationtablets_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundSet="purificationtablets_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};
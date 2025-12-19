class CfgPatches
{
    class VybrosServer
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Sounds_Effects","Vybros"};
    };
};

class CfgMods
{
    class VybrosServer
    {
        type = "mod";
        dependencies[] = {"Mission","World","Game"};

        class defs
        {
            class missionScriptModule
            {
                value = "";
                files[] = {"VybrosServer/scripts/5_mission"};
            };
			class worldScriptModule
            {
                value = "";
                files[] = {"VybrosServer/scripts/4_world"};
            };
			class gameScriptModule
			{
				value = "";
				files[] =
					{
						"VybrosServer/scripts/3_game"
					};
			};
        };
    };
};

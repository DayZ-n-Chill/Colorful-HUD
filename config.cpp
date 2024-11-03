class CfgPatches
{
	class COLORFUL_HUD
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts","DZ_Data"};
	};
};

class CfgAddons
{
	class PreloadBanks{};
	class PreloadAddons
	{
		class DayZ
		{
			list[] = {"DZ_Data","DZ_Scripts","DZ_UI","DZ_UIFonts"};
		};
	};
};

class CfgMods
{
	class COLORFUL_HUD
	{
		dir = "Colorful-HUD";
		extra = 0;
		hideName = 1;
		hidePicture = 1;
		name = "Colorful HUD, A Colorful UI ADDON";
		credits = "Special Thanks to SirPac for the Conecpts, and Motivation.  Another special Thanks to Lieutenent Master for helping out with optimizations.";
		author = "DayZ n' Chill";
		authorID = "76561197969255905";
		type = "mod";
		version = "1.0";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"Colorful-HUD/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"Colorful-HUD/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"Colorful-HUD/5_Mission"};
			};
		};
	};
};

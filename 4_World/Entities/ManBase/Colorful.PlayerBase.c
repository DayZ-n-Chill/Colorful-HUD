modded class PlayerBase extends ManBase
{
    float 		angle;
	float 		sHealth;
	float 		sBlood;
    float 		sEnergy;
	float 		sWater;
    string      sPlayerName;
	string 		sPlayerUID;

    override void Init()
    {
        super.Init();

		RegisterNetSyncVariableFloat("sHealth");
		RegisterNetSyncVariableFloat("sBlood");
		RegisterNetSyncVariableFloat("sEnergy");
		RegisterNetSyncVariableFloat("sWater");

		GetRPCManager().AddRPC("Statistics", "SyncPlayerNameResponse", this, SingeplayerExecutionType.Client);
    }

    int GetPlayerHealth() {	return sHealth;	}

	void SetPlayerHealth(int value)
    {
		sHealth = value;
		SetSynchDirty();
	}

	void SetPlayerBlood(int value)
    {
		sBlood = value;
		SetSynchDirty();
	}

	void SetPlayerEnergy(int value)
    {
		sEnergy = value;
		SetSynchDirty();
	}

	void SetPlayerWater(int value)
    {
		sWater = value;
		SetSynchDirty();
	}

	int GetPlayerBlood()
    {
		int bloodCalculated = sBlood - 2500;
		int val = Math.Round((bloodCalculated / 2500) * 100);
		return val;
	}

	int GetPlayerWater()
    {
		if (sWater <= 26)
			return 1;
        
		if (sWater >= 2600)
			return 100;
        
		int val = (sWater / 2600) * 100;
		return val;
	}

	int GetPlayerFood()
    {
		if (sEnergy <= 26)
			return 1;
        
		if (sEnergy >= 2600)
			return 100;
        
		int val = (sEnergy / 2600) * 100;
		return val;
	}
	
	// string GetPlayerItemInHands()
    // {
	// 	string response = "Empty";

	// 	if (GetItemInHands() && !GetCommand_Vehicle())
	// 		response = GetItemInHands().GetDisplayName();
	// 	else if (GetCommand_Vehicle())
	// 		response = GetCommand_Vehicle().GetTransport().GetDisplayName();
		
	// 	return response;
	// }

    string GetPlayerName()
    {
        return sPlayerName;
    }

	string GetPlayerID() 
	{
		return sPlayerUID;
	}

    int calculatePlayerDirectionDegrees()
    {
        angle = GetGame().GetCurrentCameraDirection().VectorToAngles()[0];
        return angle;
    }

    string calculatePlayerCardinalDirection(int direction)
    {
		if ((direction >= 0 && direction <= 20) || (direction >= 340 && direction <= 360)) 
			return "N";
		else if (direction <= 70 && direction > 20)
			return "NE";
		else if (direction > 70 && direction <= 110)
			return "E";
		else if (direction <= 160 && direction > 110)
			return "SE";
		else if (direction > 160 && direction <= 200)
			return "S";
		else if (direction <= 250 && direction > 200)
			return "SW";
		else if (direction > 250 && direction <= 290)
			return "W";
		else if (direction > 290 && direction < 340)
			return "NW";

        return "ERROR1";
    }

    void SyncPlayerNameResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
		Param2<string, string> data;

		if (type == CallType.Client && GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			if (!ctx.Read(data)) return;
			sPlayerName = data.param1;
			sPlayerUID = data.param2;
		}
	}
};

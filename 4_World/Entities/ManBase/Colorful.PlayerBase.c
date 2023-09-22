modded class PlayerBase
{
	protected int m_ClientHealthPercent;
	protected int m_ClientBloodPercent;
	protected int m_ClientEnergyPercent;
	protected int m_ClientThirstPercent;
	
    override void Init()
    {
        super.Init();

		RegisterNetSyncVariableInt("m_ClientHealthPercent");
		RegisterNetSyncVariableInt("m_ClientBloodPercent");
		RegisterNetSyncVariableInt("m_ClientEnergyPercent");
		RegisterNetSyncVariableInt("m_ClientThirstPercent");
	}

	void SetClientHealth(float value)
	{
		m_ClientHealthPercent = value;
		SetSynchDirty();
	}

	void SetClientBlood(float value)
	{
		m_ClientBloodPercent = ( value / GetMaxHealth( "","Blood" ) ) * 100;
		SetSynchDirty();
	}

	void SetClientEnergy(float value)
	{
		m_ClientEnergyPercent = ( value / PlayerConstants.SL_ENERGY_MAX) * 100;
		SetSynchDirty();
	}

	void SetClientThirst(float value)
	{
		m_ClientThirstPercent = ( value / PlayerConstants.SL_WATER_MAX) * 100;
		SetSynchDirty();
	}

    int GetDirectionInDegrees()
    {
		float angle = GetGame().GetCurrentCameraDirection().VectorToAngles()[0];
        return angle;
    }

	override EStatLevels GetStatLevelHealth()
	{
		SetClientHealth(GetHealth("","Health"));

		return super.GetStatLevelHealth();
	}
	
	override EStatLevels GetStatLevelBlood()
	{
		SetClientBlood(GetHealth("","Blood"));
		
		return super.GetStatLevelBlood();
	}
	
	override EStatLevels GetStatLevelEnergy()
	{
		SetClientEnergy(GetStatEnergy().Get());
		
		return super.GetStatLevelEnergy();
	}
	
	override EStatLevels GetStatLevelWater()
	{
		SetClientThirst(GetStatWater().Get());
		
		return super.GetStatLevelWater();
	}

	int GetClientHealthPercent()
	{
		return m_ClientHealthPercent;
	}

	int GetClientBloodPercent()
	{
		return m_ClientBloodPercent;
	}

	int GetClientEnergyPercent()
	{
		return m_ClientEnergyPercent;
	}

	int GetClientThirstPercent()
	{
		return m_ClientThirstPercent;
	}
};

modded class BloodNotfr: NotifierBase 
{
    override void DisplayTendency(float delta)
	{
		super.DisplayTendency(delta);
		int blood_level = m_Player.GetHealth("","Blood");
        m_Player.SetPlayerBlood(blood_level);
	}
};

modded class HealthNotfr: NotifierBase 
{
    override void DisplayTendency(float delta)
	{
		super.DisplayTendency(delta);
		int health_level = m_Player.GetHealth("","");
        m_Player.SetPlayerHealth(health_level);
	}
};

modded class HungerNotfr: NotifierBase 
{
    override void DisplayTendency(float delta)
	{
		super.DisplayTendency(delta);
		int hunger_level = m_Player.GetStatEnergy().Get();
        m_Player.SetPlayerEnergy(hunger_level);
	}
};

modded class ThirstNotfr: NotifierBase 
{
    override void DisplayTendency(float delta)
	{
		super.DisplayTendency(delta);
		int thirst_level = m_Player.GetStatWater().Get();
        m_Player.SetPlayerWater(thirst_level);
	}
};
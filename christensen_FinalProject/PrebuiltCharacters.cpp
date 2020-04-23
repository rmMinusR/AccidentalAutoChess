#include "PrebuiltCharacters.h"

#pragma region Caitlyn prebuilt

CharacterCaitlyn::CharacterCaitlyn() : Character("Caitlyn", CharacterStats())
{
	stats.max_health = stats.health = 481;
	stats.physical_resist = 28;
	stats.magical_resist = 30;
	stats.physical_damage = 62;
	stats.magical_damage = 0;
	stats.basicattack_speed = 0.681f;

	ability1 = new AbilityPiltoverPeacemaker();
}

AbilityPiltoverPeacemaker::AbilityPiltoverPeacemaker() : Ability(10000) {}

std::string AbilityPiltoverPeacemaker::getName() const
{
	return "Piltover Peacemaker";
}

Damage AbilityPiltoverPeacemaker::sample(CharacterStats* const stats, const time_t& start, const time_t& end)
{
	if (isOnCooldown()) {
		reduceCooldown(end - start);
		return Damage();
	}
	else {
		markCooldown(true);
		return Damage(DamageType::PHYSICAL, 50 + 1.3 * stats->physical_damage);
	}
}

#pragma endregion

#pragma region Khazix prebuilt

CharacterKhazix::CharacterKhazix() : Character("Kha'zix", CharacterStats())
{
	stats.max_health = stats.health = 573;
	stats.physical_resist   = 36;
	stats. magical_resist   = 32;
	stats.physical_damage   = 63;
	stats. magical_damage   = 0;
	stats.basicattack_speed = 0.668f;
	
	ability1 = new AbilityTasteTheirFear();
}

AbilityTasteTheirFear::AbilityTasteTheirFear() : Ability(4000) {}

std::string AbilityTasteTheirFear::getName() const
{
	return "Taste Their Fear";
}

Damage AbilityTasteTheirFear::sample(CharacterStats* const stats, const time_t& start, const time_t& end)
{
	if (isOnCooldown()) {
		reduceCooldown(end - start);
		return Damage();
	}
	else {
		markCooldown(true);
		if(rand()%2 == 1) return Damage(DamageType::PHYSICAL,   (60 + 1.3 * stats->physical_damage));
		else              return Damage(DamageType::PHYSICAL, 2*(60 + 1.3 * stats->physical_damage));
	}
}

#pragma endregion
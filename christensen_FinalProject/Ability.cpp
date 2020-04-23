#include "Ability.h"

inline void Ability::reduceCooldown(const time_t & amount)
{
	cooldown_timer -= amount;
}

inline bool Ability::isOnCooldown() const
{
	return cooldown_timer > 0;
}

inline void Ability::markCooldown(const bool& status)
{
	if (status) cooldown_timer = cooldown;
	else cooldown_timer = 0;
}

Ability::Ability(const time_t& cooldown)
{
	this->cooldown = cooldown;
	cooldown_timer = 0;
}

void Ability::resetCombatState()
{
	markCooldown(false);
}

std::string BasicAttack::getName() const
{
	return "Basic Attack";
}

BasicAttack::BasicAttack(CharacterStats* const stats) : Ability(1000 / stats->basicattack_speed) {}

Damage BasicAttack::sample(CharacterStats* const stats, const time_t & start, const time_t & end)
{
	if (isOnCooldown()) {
		reduceCooldown(end - start);
		return Damage();
	}
	else {
		markCooldown(true);
		return Damage(DamageType::PHYSICAL, stats->physical_damage);
	}
}
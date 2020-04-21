#include "Ability.h"

inline void Ability::reduceCooldown(const float& amount)
{
	cooldown_timer -= amount;
}

inline bool Ability::isOnCooldown() const
{
	return cooldown_timer <= 0;
}

inline void Ability::markCooldown(const bool& status)
{
	if (status) cooldown_timer = cooldown;
	else cooldown_timer = 0;
}

Ability::Ability(const float& cooldown)
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

Damage BasicAttack::sample(CharacterStats* const stats, const float& start, const float& end)
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
/*

Represents a damaging ability to be used by a Character.
Written by Robert Christensen

Certification of Authenticity: This code is mine, written solely by me,
without assistance from any other individuals.

Copyright 2020. You may use and modify this code as you please,
but I must recieve authorship credit. Furthermore you may redistribute
this code only as part of a project--this cannot be redistributed as
a standalone file.

By running or compiling this code or including it in a project, you fully and
irrevocably accept responsibility for any and all damage or other
liabilities that may arise while or after using it. You waive any and
all right to sue me using these code files as a basis.

*/

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



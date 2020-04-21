#include "combat-generic.h"

Damage::Damage() : Damage(DamageType::TRUE, 0) {}

Damage::Damage(DamageType type, float amount)
{
	this->type = type;
	this->amount = amount;
}

inline CharacterStats CharacterStats::operator+(const CharacterStats& other) const
{
	CharacterStats out;

	out.health            = this->health            + other.health;
	out.max_health        = this->max_health        + other.max_health;
	out.physical_resist   = this->physical_resist   + other.physical_resist;
	out.magical_resist    = this->magical_resist    + other.magical_resist;
	out.physical_damage   = this->physical_damage   + other.physical_damage;
	out.magical_damage    = this->magical_damage    + other.magical_damage;
	out.basicattack_speed = this->basicattack_speed + other.basicattack_speed;

	return out;
}

inline CharacterStats CharacterStats::operator-(const CharacterStats& other) const
{
	CharacterStats out;

	out.health            = this->health            - other.health;
	out.max_health        = this->max_health        - other.max_health;
	out.physical_resist   = this->physical_resist   - other.physical_resist;
	out.magical_resist    = this->magical_resist    - other.magical_resist;
	out.physical_damage   = this->physical_damage   - other.physical_damage;
	out.magical_damage    = this->magical_damage    - other.magical_damage;
	out.basicattack_speed = this->basicattack_speed - other.basicattack_speed;

	return out;
}
/*

Generic, minimal-dependency classes and structs commonly used in combat calculations.
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

#include "combat-generic.h"
#include "Character.h"

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
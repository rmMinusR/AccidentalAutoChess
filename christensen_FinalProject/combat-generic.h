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

#pragma once

#include <vector>
#include <string>

enum class DamageType {
	PHYSICAL, MAGICAL, TRUE
};

struct Damage {
	DamageType type;
	float amount;

	Damage();
	Damage(DamageType type, float amount);
};

struct CharacterStats { //Default stats copied from Lv.1 Katarina
	float          health   = 750;
	float      max_health   = 750;
	float physical_resist   =  28;
	float  magical_resist   =  32;
	float physical_damage   =  58;
	float  magical_damage   =   0;
	float basicattack_speed =   0.65f;

	inline CharacterStats operator+(const CharacterStats& other) const;
	inline CharacterStats operator-(const CharacterStats& other) const;
};

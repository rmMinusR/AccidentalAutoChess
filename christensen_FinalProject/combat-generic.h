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

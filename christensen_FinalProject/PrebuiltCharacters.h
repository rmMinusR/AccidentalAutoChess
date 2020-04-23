#pragma once

#include "Character.h"
#include "Ability.h"
#include "combat-generic.h"

class CharacterCaitlyn : public Character {
public:
	CharacterCaitlyn();
};

class AbilityPiltoverPeacemaker : public Ability {
public:
	AbilityPiltoverPeacemaker();

	virtual std::string getName() const override;
	virtual Damage sample(CharacterStats* const stats, const time_t& start, const time_t& end) override;
};

class CharacterKhazix : public Character {
public:
	CharacterKhazix();
};

class AbilityTasteTheirFear : public Ability {
public:
	AbilityTasteTheirFear();

	virtual std::string getName() const override;
	virtual Damage sample(CharacterStats* const stats, const time_t& start, const time_t& end) override;
};
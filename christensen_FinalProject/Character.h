#pragma once

#include <string>
#include <vector>

#include "Ability.h"
#include "combat-generic.h"

#include "sfgr.h"

class Character {
protected:
	Ability* basicAttack;
	Ability* ability1;
	Ability* ability2;
	Ability* ability3;
	Ability* abilityUltimate;

	Character* target;

public:
	Character(const std::string& name, const CharacterStats& stats);
	~Character();

	std::string name;
	CharacterStats stats;

	void selectTarget(Character* who);
	void selectRandomTarget(std::vector<Character*> pool);
	inline Character* getTarget() const;

	inline void takeDamage(const Damage& damage);
	inline bool isDead() const;
	void sample(const float& start, const float& end);

	void resetCombatState();

	sf::StyledTextBlock render() const;
};
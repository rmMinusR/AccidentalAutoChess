#pragma once

#include <string>
#include <vector>

#include "sfgr.h"

#include "Ability.h"
#include "combat-generic.h"
#include "Logger.h"

class Character {
protected:
	Ability* basicAttack;
	Ability* ability1;
	Ability* ability2;
	Ability* ability3;
	Ability* abilityUltimate;

	std::vector<Character*>* enemyTeam;

public:
	Character* target;

	Character(const std::string& name, const CharacterStats& stats);
	~Character();

	void setEnemyTeam(std::vector<Character*>* enemyTeam);

	std::string name;
	CharacterStats stats;

	void selectTarget(Character* who);
	void markForNewTarget();
	inline Character* getTarget();

	void takeDamage(const Damage& damage, Character* const source, Logger& logger, const Ability* const how);
	inline bool isDead() const;
	void sample(const time_t & start, const time_t & end, Logger & logger);

	void resetCombatState();

	sf::StyledTextBlock render() const;
};
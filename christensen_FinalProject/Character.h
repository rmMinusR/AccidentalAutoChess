/*

Character object. Represents a computer-controlled character which can
deal and recieve damage.
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
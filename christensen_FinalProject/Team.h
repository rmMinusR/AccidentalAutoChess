#pragma once

#include <vector>

#include "Character.h"

class Team {
public:
	std::vector< Character* > members;

	bool checkIsTeamDead() const;

	void resetCombatState();
	void simulate(const float& start, const float& end);

	Team();
	~Team();

	void renderAt(const int& x, const int& y, const int& selected = -1) const;
};
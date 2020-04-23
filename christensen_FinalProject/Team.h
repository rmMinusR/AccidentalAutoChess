#pragma once

#include <vector>
#include <ctime>

#include "Character.h"

class Team {
private:
	Team* enemy;

public:
	void setEnemy(Team* enemy);

	std::vector<Character*> members;
	void addMember(Character* member);

	bool checkIsTeamDead() const;
	Character* getRandomAlive();

	void resetCombatState();
	void simulate(const time_t & start, const time_t & end, Logger& logger);

	Team();
	~Team();

	void renderAt(const int& x, const int& y, const int& selected = -1) const;
};
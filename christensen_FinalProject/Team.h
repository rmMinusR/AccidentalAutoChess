/*

represents a group of allied Characters.
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
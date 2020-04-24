/*

Represents a damaging ability to be used by a Character.
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

#include "combat-generic.h"

class Samplable {
public:
	virtual std::string getName() const = 0;
	virtual Damage sample(CharacterStats* const stats, const time_t& start, const time_t& end) = 0;
};

class Ability : public Samplable {
private:
	time_t cooldown{ 0 };
	time_t cooldown_timer{ 0 };

protected:
	inline void reduceCooldown(const time_t & amount);
	inline bool isOnCooldown() const;
	inline void markCooldown(const bool& status = true);

	Ability(const time_t& cooldown);

public:
	virtual std::string getName() const override = 0;
	virtual Damage sample(CharacterStats* const stats, const time_t& start, const time_t& end) override = 0;
	virtual void resetCombatState();
};

class BasicAttack : public Ability {
public:
	BasicAttack(CharacterStats* const stats);

	virtual std::string getName() const override;
	virtual Damage sample(CharacterStats* const stats, const time_t & start, const time_t & end) override;
};
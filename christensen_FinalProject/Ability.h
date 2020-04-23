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
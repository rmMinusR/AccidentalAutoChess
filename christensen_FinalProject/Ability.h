#pragma once

#include "combat-generic.h"

class Samplable {
public:
	virtual std::string getName() const = 0;
	virtual Damage sample(CharacterStats* const stats, const float& start, const float& end) = 0;
};

class Ability : public Samplable {
private:
	float cooldown{ 0 };
	float cooldown_timer{ 0 };

protected:
	inline void reduceCooldown(const float& amount);
	inline bool isOnCooldown() const;
	inline void markCooldown(const bool& status = true);

	Ability(const float& cooldown);

public:
	virtual std::string getName() const override = 0;
	virtual Damage sample(CharacterStats* const stats, const float& start, const float& end) override = 0;
	virtual void resetCombatState();
};

class BasicAttack : public Ability {
public:
	virtual std::string getName() const override;
	virtual Damage sample(CharacterStats* const stats, const float& start, const float& end) override;
};
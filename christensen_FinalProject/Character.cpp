#include "Character.h"
#include "Team.h"

#include <random>

Character::Character(const std::string& name, const CharacterStats& stats)
{
	ability1 = nullptr;
	ability2 = nullptr;
	ability3 = nullptr;
	abilityUltimate = nullptr;

	target = nullptr;

	this->name = name;
	this->stats = stats;

	basicAttack = new BasicAttack(& this->stats);
}

Character::~Character()
{
	if (basicAttack     != nullptr) delete basicAttack;
	if (ability1        != nullptr) delete ability1;
	if (ability2        != nullptr) delete ability2;
	if (ability3        != nullptr) delete ability3;
	if (abilityUltimate != nullptr) delete abilityUltimate;

	if (target != nullptr) delete target;

	if (enemyTeam != nullptr) delete enemyTeam;
}

void Character::setEnemyTeam(std::vector<Character*>* enemyTeam)
{
	this->enemyTeam = enemyTeam;
}

void Character::selectTarget(Character* who)
{
	this->target = who;
}

void Character::markForNewTarget()
{
	selectTarget(nullptr);
}

Character* Character::getTarget()
{
	return target;
}

void Character::takeDamage(const Damage& damage, Character* const source, Logger& logger, const Ability* const how)
{
	if (this == nullptr) return;

	if (damage.amount <= 0) return;

	//Find the appropriate resistance
	float resistance = 0;
	if (damage.type == DamageType::PHYSICAL) resistance = stats.physical_resist;
	if (damage.type == DamageType::MAGICAL) resistance = stats.magical_resist;

	//Damage multiplier formula = 100 / (100+resistance)
	float damageTaken = damage.amount * 100 / (100 + resistance);
	stats.health -= damageTaken;
	logger << (source->name+"'s "+how->getName()+" dealt "+std::to_string(damageTaken)+" damage to "+name);

	if (isDead()) {
		stats.health = 0;
		logger << (source->name + " has killed " + name);
		source->markForNewTarget();
	}
}

inline bool Character::isDead() const
{
	return stats.health <= 0;
}

void Character::sample(const time_t & start, const time_t & end, Logger & logger)
{
	if (isDead()) return;
	if (target == nullptr) return;

	if (target->isDead()) markForNewTarget();

	if (basicAttack     != nullptr) target->takeDamage(basicAttack    ->sample(&stats, start, end), this, logger, basicAttack);
	if (ability1        != nullptr) target->takeDamage(ability1       ->sample(&stats, start, end), this, logger, ability1);
	if (ability2        != nullptr) target->takeDamage(ability2       ->sample(&stats, start, end), this, logger, ability2);
	if (ability3        != nullptr) target->takeDamage(ability3       ->sample(&stats, start, end), this, logger, ability3);
	if (abilityUltimate != nullptr) target->takeDamage(abilityUltimate->sample(&stats, start, end), this, logger, abilityUltimate);
}

void Character::resetCombatState()
{
	stats.health = stats.max_health;
	
	if (basicAttack     != nullptr) basicAttack    ->resetCombatState();
	if (ability1        != nullptr) ability1       ->resetCombatState();
	if (ability2        != nullptr) ability2       ->resetCombatState();
	if (ability3        != nullptr) ability3       ->resetCombatState();
	if (abilityUltimate != nullptr) abilityUltimate->resetCombatState();
}

sf::StyledTextBlock Character::render() const
{
	sf::StyledTextBlock image(20, 3);

	const sf::TextStyle styleAlive(0, 1, 0, 1);
	const sf::TextStyle styleDead (1, 0, 0, 0);

	//Print name
	image.putStr(name+(isDead()?" - DEAD":" - ALIVE"), 0, 0);
	image.fillStyle(isDead() ? styleDead : styleAlive, 0, 0, image.width - 2, 0);

	//Draw pretty health bar
	image.setStyledChar(sf::StyledChar('['), 0, 1);
	image.setStyledChar(sf::StyledChar(']'), image.width-1, 1);
	image.fillChar('=', 1, 1, image.width - 2, 1);
	//Colorize it
	for (int i = 1; i < image.width - 1; i++) {
		if (i / (image.width-2.0) <= stats.health / stats.max_health) {
			image.setStyle(styleAlive, i, 1);
		}
		else {
			image.setStyle(styleDead, i, 1);
		}
	}

	//Print health bar as numbers
	image.putStr(std::to_string((int)stats.health) + " / " + std::to_string((int)stats.max_health), 0, 2);

	return image;
}

#include "Character.h"

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
}

Character::~Character()
{
	if (basicAttack) delete basicAttack;
	if (ability1) delete ability1;
	if (ability2) delete ability2;
	if (ability3) delete ability3;
	if (abilityUltimate) delete abilityUltimate;

	if (target) delete target;
}

void Character::selectTarget(Character* who)
{
	this->target = who;
}

void Character::selectRandomTarget(std::vector<Character*> pool)
{
	selectTarget(pool[rand() % pool.size()]);
}

Character* Character::getTarget() const
{
	return target;
}

inline void Character::takeDamage(const Damage& damage)
{
	//Find the appropriate resistance
	float resistance = 0;
	if (damage.type == DamageType::PHYSICAL) resistance = stats.physical_resist;
	if (damage.type == DamageType::MAGICAL) resistance = stats.magical_resist;

	//Damage multiplier formula = 100 / (100+resistance)
	stats.health -= damage.amount * 100 / (100 + resistance);
}

inline bool Character::isDead() const
{
	return stats.health <= 0;
}

void Character::sample(const float& start, const float& end)
{
	if (isDead()) return;

	if (basicAttack)     target->takeDamage(basicAttack    ->sample(&stats, start, end));
	if (ability1)        target->takeDamage(ability1       ->sample(&stats, start, end));
	if (ability2)        target->takeDamage(ability2       ->sample(&stats, start, end));
	if (ability3)        target->takeDamage(ability3       ->sample(&stats, start, end));
	if (abilityUltimate) target->takeDamage(abilityUltimate->sample(&stats, start, end));
}

void Character::resetCombatState()
{
	stats.health = stats.max_health;
	
	if (basicAttack)     basicAttack    ->resetCombatState();
	if (ability1)        ability1       ->resetCombatState();
	if (ability2)        ability2       ->resetCombatState();
	if (ability3)        ability3       ->resetCombatState();
	if (abilityUltimate) abilityUltimate->resetCombatState();
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

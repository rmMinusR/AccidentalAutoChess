#include "Team.h"

#include <random>

void Team::setEnemy(Team* enemy)
{
	this->enemy = enemy;
}

void Team::addMember(Character* member)
{
	members.push_back(member);
	member->setEnemyTeam(&members);
}

bool Team::checkIsTeamDead() const
{
	for (Character* c : members) {
		if (!c->isDead()) return false;
	}
	return true;
}

Character* Team::getRandomAlive()
{
	int n_alive = 0;
	for (Character* c : members) {
		if (!c->isDead()) n_alive++;
	}

	if (n_alive == 0) return nullptr;

	int ind = rand() % n_alive;
	int i = 0;
	while (ind > 0) {
		i++;
		if(!members[i]->isDead()) ind--;
	}
	return members[i];
}

void Team::resetCombatState()
{
	for (Character* c : members) {
		c->resetCombatState();
		c->selectTarget(enemy->getRandomAlive());
	}
}

void Team::simulate(const time_t & start, const time_t & end, Logger& logger)
{
	for (Character* c : members) {
		if (c->target == nullptr || c->target->isDead()) c->target = enemy->getRandomAlive();
		c->sample(start, end, logger);
	}
}

Team::Team()
{
	enemy = nullptr;
}

Team::~Team()
{
	for (Character* c : members) delete c;
	members.clear();
}

void Team::renderAt(const int& x, const int& y, const int& selected) const
{
	int w = 0, h = -1; //Used for calculating the final screenspace of the Team image
	std::vector<sf::StyledTextBlock> rendered_character_images;
	for (Character* c : members) {
		//Fetch and render
		sf::StyledTextBlock char_img = c->render();
		rendered_character_images.push_back(char_img);

		//Calculate the screenspace the Team image requires
		if (w < char_img.width) w = char_img.width;
		h += char_img.height + 1;
	}

	sf::StyledTextBlock rendered_team_image(w+2, h+2); //Padded by 1 character on all sides
	int iy = 1;
	for (int i = 0; i < rendered_character_images.size(); i++) {
		sf::StyledTextBlock char_img = rendered_character_images[i];
		char_img.blit(rendered_team_image, 1, iy);
		
		//If selected, render a border
		if (i == selected) {
			rendered_team_image.drawBox(sf::TextStyle(), 0, iy-1, char_img.width+1, iy+char_img.height);
		}

		iy += char_img.height + 1;
	}

	rendered_team_image.blit(x, y);

}

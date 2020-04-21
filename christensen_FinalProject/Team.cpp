#include "Team.h"

bool Team::checkIsTeamDead() const
{
	for (Character* c : members) {
		if (!c->isDead()) return false;
	}
	return true;
}

void Team::resetCombatState()
{
	for (Character* c : members) c->resetCombatState();
}

void Team::simulate(const float& start, const float& end)
{
	for (Character* c : members) c->sample(start, end);
}

Team::Team()
{

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
	for (int i = 0; i < members.size(); i++) {
		//Fetch and render
		Character* c = members[i];
		sf::StyledTextBlock char_img = c->render();

		//Gray it out if something else is currently selected
		if (selected >= 0 && i != selected) char_img.fillStyle(sf::TextStyle(0, 0, 0, 1), 0, 0, char_img.width-1, char_img.height-1);
		rendered_character_images.push_back(char_img);

		//Calculate the screenspace the Team image requires
		if (w < char_img.width) w = char_img.width;
		h += char_img.height + 1;
	}

	sf::StyledTextBlock rendered_team_image(w+2, h+2); //Padded by 1 character on all sides
	int iy = 1;
	for (sf::StyledTextBlock char_img : rendered_character_images) {
		char_img.blit(rendered_team_image, 1, iy);
		iy += char_img.height + 1;
	}

	rendered_team_image.blit(x, y);

}

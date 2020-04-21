#include "sfio.h"
#include "sfgr.h"

#include "Team.h"

#include <iostream>
#include <vector>

enum class PROGRAM_STATE {
	MENU, PLAYER_EDIT, PLAYER_STATS_EDIT, SIMULATING, EXITING
};

void drawMenu(int menuState, const std::vector<std::string> menuItems);
void drawTeams(const Team& a, const Team& b, int menuIndex = -1);

int main() {
	const std::vector<std::string> MENU_ITEMS { "Edit teams", "Simulate combat", "Reset battlefield", "Exit" };
	PROGRAM_STATE programState = PROGRAM_STATE::MENU;
	Team teamA, teamB;

	teamA.members.push_back(new Character("Katarina A", CharacterStats()));
	teamA.members.push_back(new Character("Katarina B", CharacterStats()));
	teamB.members.push_back(new Character("Katarina", CharacterStats()));

	int menuIndex = 0;
	while (true) {

		while(programState == PROGRAM_STATE::MENU) {
			sf::cclear();
			drawMenu(menuIndex, MENU_ITEMS);
			drawTeams(teamA, teamB);
			
			//Fetch keyboard input
			char kb_in = sf::cquerych();

			if (kb_in == -32) { //Charcode preceeding arrow keys

				char c = sf::cquerycht(5);
				if (c == 72) {} // UP
				else if (c == 75) { // LEFT
					menuIndex--;
				}
				else if (c == 80) {} // DOWN
				else if (c == 77) { // RIGHT
					menuIndex++;
				}

			}
			else { //It isn't a special key, interpret as normal

				if (kb_in == 13 || kb_in == 32) { // ENTER or SPACE
					if (menuIndex == 0) { programState = PROGRAM_STATE::PLAYER_EDIT; }
					if (menuIndex == 1) { programState = PROGRAM_STATE::SIMULATING ; }
					if (menuIndex == 2) { teamA.resetCombatState(); teamB.resetCombatState();}
					if (menuIndex == 3) { programState = PROGRAM_STATE::EXITING    ; }
				}

			}

			if (menuIndex < 0) menuIndex += MENU_ITEMS.size();
                               menuIndex %= MENU_ITEMS.size();
		}

		while (programState == PROGRAM_STATE::PLAYER_EDIT) {
			sf::cclear();
			drawMenu(0, MENU_ITEMS);
			drawTeams(teamA, teamB);

			//Fetch keyboard input
			char kb_in = sf::cquerych();

			if (kb_in == -32) { //Charcode preceeding arrow keys

				char c = sf::cquerycht(5);
				if (c == 72) {} // UP
				else if (c == 75) { // LEFT
					menuIndex--;
				}
				else if (c == 80) {} // DOWN
				else if (c == 77) { // RIGHT
					menuIndex++;
				}

			}
			else { //It isn't a special key, interpret as normal

				if (kb_in == 13 || kb_in == 32) { // ENTER or SPACE
					
				}

			}
		}
		
	}
	return 0;
}

inline std::string bracketHelper(std::string str, bool b) {
	return (((b) ? "[" : " ") + (str)+((b) ? "]" : " "));
}

void drawMenu(int menuState, const std::vector<std::string> menuItems)
{
	sf::StyledTextBlock image(sf::cgetw() - 40, 3);

	const sf::TextStyle    selected(1, 1, 1, 1);
	const sf::TextStyle notSelected(0, 0, 0, 1);
	
	image.drawBox(notSelected, 0, 0, image.width - 1, image.height - 1);
	for (int i = 0; i < menuItems.size(); i++) {
		int x = 1 + (image.width - 2) * (1 + i) / (1 + menuItems.size()) - menuItems[i].length() / 2;
		image.putStr(bracketHelper(menuItems[i], i == menuState), x, 1);
		image.fillStyle( (menuState==i)?selected:notSelected, x, 1, x + menuItems[i].length(), 1);
	}

	image.blit( (sf::cgetw()-image.width)/2 , 2);
}

void drawTeams(const Team& a, const Team& b, int menuIndex)
{
	a.renderAt( 0, 10, menuIndex);
	b.renderAt(50, 10, menuIndex);
}

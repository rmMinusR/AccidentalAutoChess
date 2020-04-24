#include "sfio.h"
#include "sfgr.h"

#include "Team.h"
#include "Logger.h"

#include "PrebuiltCharacters.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

enum class PROGRAM_STATE {
	MENU, PLAYER_EDIT, PLAYER_STATS_EDIT, SIMULATING, EXITING
};

void drawMenu(int menuState, const std::vector<std::string> menuItems);
void drawTeams(const Team& a, const Team& b, int menuIndex = -1);
void drawLog(const Logger& log);

#define resetAll(); { teamA.resetCombatState(); teamB.resetCombatState(); simulationTime = 0; }
inline long long time() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

int main() {
	srand(time());

	const std::vector<std::string> MENU_ITEMS { "Edit teams", "Simulate combat", "Reset battlefield", "Exit" };
	Logger logger;
	PROGRAM_STATE programState = PROGRAM_STATE::MENU;
	Team teamA, teamB;
	teamA.setEnemy(&teamB);
	teamB.setEnemy(&teamA);

	teamA.addMember(new Character("Katarina", CharacterStats()));
	teamA.addMember(new CharacterCaitlyn());
	teamB.addMember(new CharacterKhazix());

	teamA.resetCombatState(); teamB.resetCombatState();

	int menuIndex = 0;
	time_t simulationTime = 0;
	while (programState != PROGRAM_STATE::EXITING) {

		while (programState == PROGRAM_STATE::MENU) {
			if (sf::hasResized()) sf::cclear();
			drawMenu(menuIndex, MENU_ITEMS);
			drawTeams(teamA, teamB);
			drawLog(logger);

			//Fetch keyboard input
			char kb_in = sf::cquerycht(1000);

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
					if (menuIndex == 1) { programState = PROGRAM_STATE::SIMULATING; }
					if (menuIndex == 2) { resetAll(); logger << "Simulation reset!"; }
					if (menuIndex == 3) { programState = PROGRAM_STATE::EXITING; }
				}

			}

			if (menuIndex < 0) menuIndex += MENU_ITEMS.size();
			menuIndex %= MENU_ITEMS.size();
		}

		while (programState == PROGRAM_STATE::SIMULATING) {
			if (sf::hasResized()) sf::cclear();
			drawMenu(menuIndex, MENU_ITEMS);
			drawTeams(teamA, teamB);
			drawLog(logger);

			time_t startTime = time();
			char kb_in = sf::cquerycht(200);
			time_t elapsedTime = time() - startTime;

			teamA.simulate(simulationTime, simulationTime + elapsedTime, logger);
			teamB.simulate(simulationTime, simulationTime + elapsedTime, logger);

			simulationTime += elapsedTime;

			if (kb_in != 0) {
				programState = PROGRAM_STATE::MENU;
				logger << "Simulation paused!";
			}
			if (teamA.checkIsTeamDead() || teamB.checkIsTeamDead()) {
				programState = PROGRAM_STATE::MENU;
				logger << "Simulation complete!";
			}
		}

		while (programState == PROGRAM_STATE::PLAYER_EDIT) {
			if (sf::hasResized()) sf::cclear();
			drawMenu(0, MENU_ITEMS);
			drawTeams(teamA, teamB, menuIndex);
			drawLog(logger);

			//Fetch keyboard input
			char kb_in = sf::cquerycht(1000);

			if (kb_in == -32) { //Charcode preceeding arrow keys

				char c = sf::cquerycht(5);
				if (c == 72) { // UP
					menuIndex--;
				}
				else if (c == 75) { // LEFT
					menuIndex -= (teamA.members.size() + teamB.members.size()) / 2;
				}
				else if (c == 80) { // DOWN
					menuIndex++;
				}
				else if (c == 77) { // RIGHT
					menuIndex += (teamA.members.size() + teamB.members.size()) / 2;
				}

				int n_options = teamA.members.size() + teamB.members.size() + 4;
				if (menuIndex >= n_options) menuIndex -= n_options;
				if (menuIndex < 0)          menuIndex += n_options;
			}
			else { //It isn't a special key, interpret as normal

				if (kb_in == 13 || kb_in == 32) { // ENTER or SPACE
					if (menuIndex == teamA.members.size() + 1 || menuIndex == teamA.members.size() + teamB.members.size() + 3) {
						programState = PROGRAM_STATE::MENU;
					}

					if (menuIndex == teamA.members.size()) {
						teamA.addMember(new Character("Katarina", CharacterStats()));
						resetAll();
					}

					if (menuIndex == teamA.members.size() + teamB.members.size() + 2) {
						teamB.addMember(new Character("Katarina", CharacterStats()));
						resetAll();
					}
				}

			}
		}

	}
	//Write log
	logger.writeTo("log.txt");

	//Reset console color and exit
	sf::csetcolc(1, 1, 1, 1);
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
	{
		a.renderAt(0, 10, menuIndex);
		
		sf::StyledTextBlock btnAddPlayer(12, 3);
		btnAddPlayer.putStr("Add Player", 1, 1);
		if (menuIndex == a.members.size())    btnAddPlayer.drawBox(sf::TextStyle(), 0, 0, btnAddPlayer.width - 1, btnAddPlayer.height - 1);
		btnAddPlayer.fillStyle(sf::TextStyle(0, 1, 0, 1), 0, 0, btnAddPlayer.width - 1, btnAddPlayer.height - 1);

		sf::StyledTextBlock btnExitMenu(8, 3);
		btnExitMenu.putStr("Exit", 2, 1);
		if (menuIndex == a.members.size() + 1) btnExitMenu.drawBox(sf::TextStyle(), 0, 0, btnExitMenu.width - 1, btnExitMenu.height - 1);
		btnExitMenu.fillStyle(sf::TextStyle(1, 0, 0, 0), 0, 0, btnExitMenu.width - 1, btnExitMenu.height - 1);

		btnAddPlayer.blit(2, sf::cgeth() - 8);
		btnExitMenu .blit(2, sf::cgeth() - 5);
	}

	menuIndex -= a.members.size() + 2; //2 for Add Player button and Exit button
	
	{
		b.renderAt(50, 10, menuIndex);

		sf::StyledTextBlock btnAddPlayer(12, 3);
		btnAddPlayer.putStr("Add Player", 1, 1);
		if (menuIndex == b.members.size())     btnAddPlayer.drawBox(sf::TextStyle(), 0, 0, btnAddPlayer.width - 1, btnAddPlayer.height - 1);
		btnAddPlayer.fillStyle(sf::TextStyle(0, 1, 0, 1), 0, 0, btnAddPlayer.width - 1, btnAddPlayer.height - 1);

		sf::StyledTextBlock btnExitMenu(8, 3);
		btnExitMenu.putStr("Exit", 2, 1);
		if (menuIndex == b.members.size() + 1) btnExitMenu.drawBox(sf::TextStyle(), 0, 0, btnExitMenu.width - 1, btnExitMenu.height - 1);
		btnExitMenu.fillStyle(sf::TextStyle(1, 0, 0, 0), 0, 0, btnExitMenu.width - 1, btnExitMenu.height - 1);

		btnAddPlayer.blit(52, sf::cgeth() - 8);
		btnExitMenu .blit(52, sf::cgeth() - 5);
	}
}

void drawLog(const Logger& log) {
	log.renderTail(sf::cgetw() - 100, sf::cgeth()-10).blit(100, 8);
}
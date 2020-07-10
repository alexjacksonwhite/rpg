#include <iostream>
#include <string>
#include <iomanip>
#include "game.h"
#include "monster.h"

using namespace std;

Game::Game() {
	mPlayerX = 0;
	mPlayerY = 0;
	remainingMoves = 50;
}

void Game::initGame() {
	mPlayerX = 0;
	mPlayerY = 0;
	remainingMoves = 50;
}

int Game::getX() {
	return mPlayerX;
}

int Game::getY() {
	return mPlayerY;
}

int Game::getRemainingMoves() {
	return remainingMoves;
}

void Game::printPlayerPos() {
	cout << "Player position: (" << getX() << ", " << getY() << ")" << endl;
}

void Game::printRemainingMoves() {
	cout << "Remaining moves: " << getRemainingMoves() << endl;
}

bool Game::noMovesLeft() {
	return remainingMoves <= 0;
}

void Game::printGameStats() {
	system("pause");
	system("cls");
	printPlayerPos();
	printRemainingMoves();
	cout << endl;
}

void Game::movePlayer() {
	printPlayerPos();
	int input = 0;
	cout << "1. North" << endl;
	cout << "2. East" << endl;
	cout << "3. South" << endl;
	cout << "4. West" << endl;
	cin >> input;

	switch (input) {
	case 1: //north
		if (getY() == 20) {
			cout << "You can't move off the map!" << endl;
		}
		else {
			++mPlayerY;
			--remainingMoves;
		}
		break;
	case 2: //east
		if (getX() == 20) {
			cout << "You can't move off the map!" << endl;
		}
		else {
			++mPlayerX;
			--remainingMoves;
		}
		break;
	case 3: //south
		if (getY() == -20) {
			cout << "You can't move off the map!" << endl;
		}
		else {
			--mPlayerY;
			--remainingMoves;
		}
		break;
	case 4: //west
		if (getX() == -20) {
			cout << "You can't move off the map!" << endl;
		}
		else {
			--mPlayerX;
			--remainingMoves;
		}
		break;
	default:
		cout << "Invalid option" << endl;
		break;
	}
	system("cls");
}

Monster* Game::randomizeMonster() {
	bool debug = false;
	Monster* monster = 0;
	int lowEnd = 0;
	int highEnd = 60;
	int maxPos = 0;

	if (abs(getX() > abs(getY()))) maxPos = abs(getX());
	else maxPos = abs(getY());

	lowEnd = lowEnd + (maxPos*2);
	highEnd = highEnd + (maxPos*2);

	int roll = rand() % highEnd + lowEnd; //roll 1-60

	if (debug) {
		cout << "Highend: " << highEnd << endl;
		cout << "Lowend: " << lowEnd << endl;
		cout << "Roll: " << roll << endl;
	}

	if (roll <= 20) { // no encounter
		cout << "Nothing to fight, you have moved 1 space for free!" << endl << endl;
		return 0; 
	}
	else if (roll >= 21 && roll <= 40) { //goblin
		monster = new Monster("Goblin", 60, 300, 1, 2, 10, 15);
		cout << "You encountered a Goblin!" << endl;
		cout << "Prepare for battle!" << endl << endl;
	}
	else if (roll >= 41 && roll <= 70) {//orc
		monster = new Monster("Orc", 80, 500, 1, 4, 20, 30);
		cout << "You encountered an Orc!" << endl;
		cout << "Prepare for battle!" << endl << endl;
	}
	else if (roll >= 71 && roll <= 95) {//whelp
		monster = new Monster("Whelp", 90, 600, 1, 3, 25, 35);
		cout << "You encountered a Dragon Whelp!" << endl;
		cout << "Prepare for battle!" << endl << endl;
	}
	else if (roll >= 96) {//boss
		monster = new Monster("Edgy Warlord Boss Name", 120, 900, 3, 6, 40, 55);
		cout << "You encountered an Edgy Warlord Boss Name!" << endl;
		cout << "Better run away!" << endl << endl;
	}
	return monster;
}

void Game::intro() {

	system("cls");
	cout << "==============================" << endl;
	cout << "=====WELCOME TO DANECRAFT=====" << endl;
	cout << "==============================" << endl << endl;
	
	cout << "How to Play!" << endl;
	cout << "1: Pick a Class:" << endl;
	cout << "\t- Rogue" << endl;
	cout << "\t- Mage" << endl;
	cout << "\t- Warrior" << endl;

	cout << "2: Move around the map:" << endl;
	cout << "\t- Dangerous monsters await you the farther you move" << endl;
	cout << "\t- You cannot move more than 20 spaces in any direction" << endl;
		
	cout << "3: You have 50 moves to defeat the final boss:" << endl; 
	cout << "\t- Make sure you level up before venturing out too far!" << endl << endl;
	system("pause");
	system("cls");
}
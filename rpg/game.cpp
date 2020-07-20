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

void Game::deductMoves(int moves) {
	remainingMoves -= moves;
}

void Game::rewardMoves(int moves) {
	remainingMoves += moves;
}

void Game::printGameStats() {
	printPlayerPos();
	printRemainingMoves();
}

void Game::movePlayer() {
	int input;
	bool moving = true;

	while (moving) {
		printPlayerPos();
		cout << "1. North" << endl;
		cout << "2. East" << endl;
		cout << "3. South" << endl;
		cout << "4. West" << endl;
		input = -1;
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			cout << "Invalid input, try again" << endl;
			system("pause");
			system("cls");
			continue;
		}

		switch (input) {
		case 1: //north
			if (getY() == 20) {
				cout << "You can't move off the map!" << endl;
			}
			else {
				++mPlayerY;
				--remainingMoves;
				moving = false;
			}
			break;
		case 2: //east
			if (getX() == 20) {
				cout << "You can't move off the map!" << endl;
			}
			else {
				++mPlayerX;
				--remainingMoves;
				moving = false;
			}
			break;
		case 3: //south
			if (getY() == -20) {
				cout << "You can't move off the map!" << endl;
			}
			else {
				--mPlayerY;
				--remainingMoves;
				moving = false;
			}
			break;
		case 4: //west
			if (getX() == -20) {
				cout << "You can't move off the map!" << endl;
			}
			else {
				--mPlayerX;
				--remainingMoves;
				moving = false;
			}
			break;
		default:
			system("cls");
			cout << "Invalid option" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("cls");
}

Monster* Game::randomizeMonster() {
	bool debug = false;
	Monster* monster = 0;
	string name;
	int lowEnd = 0;
	int highEnd = 60;
	int maxPos = 0;
	int levelModifier = 0;
	int	level = 0;
	int encounterRoll = 0;
	int hpMod, expMod, armorMod, damageMod;
	int experience, armor, hp, lowDamage, highDamage;

	//determine player position
	if (abs(getX() > abs(getY()))) maxPos = abs(getX());
	else maxPos = abs(getY());

	if (maxPos == 0) levelModifier = 1;//if player is at 0,0 coordinate
	else levelModifier = maxPos;

	//set monster level based on how player position
	if (levelModifier == 1) level = 1;
	else level = rand() % levelModifier + (levelModifier - 1);

	//roll an encounter based on player position
	lowEnd = lowEnd + (maxPos * 2);
	highEnd = highEnd + (maxPos * 2);
	encounterRoll = rand() % highEnd + lowEnd; //roll 1-60

	//show rolls
	if (debug) {
		cout << "Highend: " << highEnd << endl;
		cout << "Lowend: " << lowEnd << endl;
		cout << "Roll: " << encounterRoll << endl;
	}

	if (encounterRoll <= 20 && getRemainingMoves() != 49) { // no encounter
		cout << "Nothing to fight, you have moved 1 space for free!" << endl << endl;
		return 0; 
	}
	else if ((encounterRoll >= 21 && encounterRoll <= 40) || getRemainingMoves() == 49) { //goblin
		//mods
		hpMod = 10 * (level - 1);//every level is 10 more health
		expMod = 50 * (level - 1);//every level is 50 more exp
		armorMod = (int)(floor(0.25 * (level - 1 )));//every 4 levels increases armor by 1
		damageMod = 1 * (level - 1);//every level is 1 more damage

		//values
		name = "Goblin";
		hp = 60 + hpMod;
		experience = 300 + expMod;
		armor = 2 + armorMod;
		lowDamage = 10 + damageMod;
		highDamage = 15 + damageMod;
	}
	else if (encounterRoll >= 41 && encounterRoll <= 70) {//orc
		//mods
		hpMod = 10 * (level - 1);//every level is 10 more health
		expMod = 50 * (level - 1);//every level is 50 more exp
		armorMod = (int)(floor(0.25 * (level - 1)));//every 4 levels increases armor by 1
		damageMod = 1 * (level - 1);//every level is 1 more damage

		//values
		name = "Orc";
		hp = 80 + hpMod;
		experience = 500 + expMod;
		armor = 4 + armorMod;
		lowDamage = 20 + damageMod;
		highDamage = 30 + damageMod;
	}
	else if (encounterRoll >= 71 && encounterRoll <= 95) {//whelp
		//mods
		hpMod = 10 * (level - 1);//every level is 10 more health
		expMod = 50 * (level - 1);//every level is 50 more exp
		armorMod = (int)(floor(0.25 * (level - 1)));//every 4 levels increases armor by 1
		damageMod = 1 * (level - 1);//every level is 1 more damage

		//values
		name = "Whelp";
		hp = 90 + hpMod;
		experience = 600 + expMod;
		armor = 3 + armorMod;
		lowDamage = 25 + damageMod;
		highDamage = 35 + damageMod;
	}
	else if (encounterRoll >= 96) {//boss
		//values
		name = "Edgy Warlord Boss";
		hp = 250;
		experience = 900;
		level = 20;
		armor = 6;
		lowDamage = 40;
		highDamage = 55;
	}

	monster = new Monster(name, hp, experience, level, armor, lowDamage, highDamage);
	cout << "You encountered a(n) " << monster->getName() << "!" << endl;
	cout << "Prepare for battle!" << endl << endl;
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

	cout << "WIP / NYI" << endl;
	cout << "\t- More spell choices in combat" << endl;

	cout << endl << endl;
	system("pause");
	system("cls");
}
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include "player.h"
#include "monster.h"

using namespace std;

//constructor with params
Player::Player() {
	healthPoints = 100;
	maxHealthPoints = 100;
	stamina = 0;
	agility = 0;
	strength = 0;
	intelligence = 0;
	primary = 0;
	experience = 0;
	nextLevelExp = 1000;
	level = 1;
	currentResourcePoints = 0;
	maxResourcePoints = 0;
	initResourcePoints = 0;
	critChance = 0;
	critDamage = 0;
	playerGold = 5;
	mSpells;
	status = "normal";
	inCombat = false;
	turn = 0;
	castTime = 0;
}

//setters
void Player::setName(string name) {
	name = name;
}
void Player::setClass(string c) {
	c = c;
}
void Player::setHealth(int hp) {
	healthPoints = hp;
}

//getters
string Player::getName() { return name; }
string Player::getClass() { return c; }
string Player::getStatus() { return status; }
bool Player::getInCombat() { return inCombat; }
int Player::getHealthPoints() { return healthPoints; }
int Player::getCurrentResourcePoints() { return currentResourcePoints; }
int Player::getCritChance() {
	int mod;
	if (status == "STEALTHED") mod = critChance + 50;
	if (status == "COMBUSTION") mod = critChance + 100;
	else mod = critChance;
	status = "normal";
	return mod;
}

void Player::getStats() {

	system("cls");
	cout << "======================" << endl;
	cout << "=====PLAYER STATS=====" << endl;
	cout << "======================" << endl << endl;

	cout << left << setw(20) << "Name: " << name << endl;
	cout << left << setw(20) << "Class: " << c << endl;
	cout << left << setw(20) << "Resource: " << resource << endl;
	cout << left << setw(20) << "Current Resource: " << currentResourcePoints << endl;
	//cout << left << setw(20) << "Primary: " << *primary << endl;
	cout << left << setw(20) << "HealthPoints: " << healthPoints << endl;
	//cout << left << setw(20) << "Stamina: " << stamina << endl;
	cout << left << setw(20) << "Agility: " << agility << endl;
	cout << left << setw(20) << "Intelligence: " << intelligence << endl;
	cout << left << setw(20) << "Strength: " << strength << endl;
	cout << left << setw(20) << "Crit Chance: " << getCritChance() << "%" << endl;
	cout << left << setw(20) << "Crit Damage: " << critDamage << "%" << endl;
	cout << left << setw(20) << "Experience: " << experience << endl;
	cout << left << setw(20) << "Level: " << level << endl;

	for (int i = 0; i < mSpells.size() ; i++) {
		if (i == 0) { cout << endl << "Spells: " << endl; }
		if (i == mSpells.size() - 1) { cout << "\t" << mSpells.at(i).spellName << endl << endl; }
		else { cout << "\t" << mSpells.at(i).spellName + "," << endl; }}
}


//biggers
void Player::createCharacter() {
	string name, c;
	//cout << "Enter your name: ";
	//cin >> name;
	//name = name;
	bool classNotChosen = true;
	this->name = "Adventurer";
	int cNum;
	mSpells.clear();


	while (classNotChosen) {

		cout << "Please select a Class" << endl;
		cout << "1 = Rogue" << endl;
		cout << "2 = Mage" << endl;
		cout << "3 = Warrior" << endl;
		cNum = -1;
		cin >> cNum;
		if (!validInput()) continue;

		switch (cNum) {
		case 1: //Rogue
			this->c = "Rogue";
			resource = "ENERGY";
			agility = 5;
			strength = 3;
			intelligence = 2;
			primary = &agility;
			critChance = 10;
			critDamage = 150;
			currentResourcePoints = 100;
			maxResourcePoints = 100;
			initResourcePoints = 100;
			experience = 0;
			nextLevelExp = 1000;
			level = 1;
			healthPoints = 100;
			maxHealthPoints = 100;
			addSpell("Backstab", "ENERGY", -60, 13, 17, 1.3);
			addSpell("Stealth", "ENERGY", 0, 0, 0, 0);
			//addSpell("Eviscerate", "ENERGY", -60, 13, 17, 1.3);
			classNotChosen = false;
			break;
		case 2: //Mage
			this->c = "Mage";
			resource = "MANA";
			agility = 2;
			strength = 2;
			intelligence = 6;
			primary = &intelligence;
			critChance = 5;
			critDamage = 200;
			currentResourcePoints = 100;
			maxResourcePoints = 100;
			initResourcePoints = maxResourcePoints;
			experience = 0;
			nextLevelExp = 1000;
			level = 1;
			healthPoints = 100;
			maxHealthPoints = 100;
			addSpell("Fireball", "MANA", -40, 25, 30, 1.1);
			addSpell("Combustion", "MANA", -10, 0, 0, 0);
			//addSpell("Pyroblast", "MANA", 10, 0, 0, 0);
			classNotChosen = false;
			break;
		case 3: //Warrior
			this->c = "Warrior";
			resource = "RAGE";
			agility = 4;
			strength = 8;
			intelligence = 1;
			primary = &strength;
			critChance = 5;
			critDamage = 150;
			currentResourcePoints = 0;
			maxResourcePoints = 100;
			initResourcePoints = 0;
			experience = 0;
			nextLevelExp = 1000;
			level = 1;
			healthPoints = 100;
			maxHealthPoints = 100;
			addSpell("Mortal Strike", "RAGE", -40, 18, 23, 1.4);
			addSpell("Battle Shout", "RAGE", 25, 0, 0, 0);
			//addSpell("Execute", "RAGE", 30, ((1.5 * strength) + currentResourcePoints + 15));
			classNotChosen = false;
			break;
		default:
			system("cls");
			cout << "Invalid option" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	getStats();
}

void Player::addSpell(string spellName, string resource, int cost, int lowDamage, int highDamage, double modifier) {
	spells newSpell;
	newSpell.spellName = spellName;
	newSpell.resource = resource;
	newSpell.cost = cost;
	newSpell.lowDamage = lowDamage;
	newSpell.highDamage = highDamage;
	newSpell.modifier = modifier;
	mSpells.push_back(newSpell);
}


bool Player::attackMonster(Monster& monster) {

	bool fastAnimations = true;
	bool encounter = true;
	bool overkill = false;
	int damage, modifier, critRoll, totalDamage, runAwayRoll, wait1, wait2, spellIndex;
	int loopCounter = 0;
	int input;
	spells spell;


	if (!fastAnimations) {
		wait1 = 400;
		wait2 = 1000;
	}

	while (encounter) {
		system("pause");
		system("cls");
		cout << "A(n) " << monster.getName() << " is attacking you! What do you do?" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Run" << endl;
		cout << "3. View Enemy Stats" << endl;
		cout << "4. View Player Stats" << endl;
		input = -1;
		cin >> input;
		loopCounter++;

		if (castTime > turn) {
			cout << "It's not your turn yet" << endl;
			return false;
		}

		system("cls");

		if (!validInput()) continue;

		switch (input) {
		case 1://attack

			for (int i = 0; i < mSpells.size(); i++) {
				if (i == 0) { cout << endl << "Choose an Ability: " << endl; }
				cout << i + 1 << ". " << mSpells.at(i).spellName << endl;
			}
			cin >> spellIndex;
			if (!validInput()) continue;
			system("cls");
			spellIndex -= 1;
			if (spellIndex >= mSpells.size()) {
				cout << "Invalid option" << endl;
				continue;
			}
			spell.cost = mSpells.at(spellIndex).cost;
			spell.spellName = mSpells.at(spellIndex).spellName;
			spell.modifier = mSpells.at(spellIndex).modifier;
			spell.lowDamage = mSpells.at(spellIndex).lowDamage;
			spell.highDamage = mSpells.at(spellIndex).highDamage;

			//catch cooldown abilities
			if (spell.lowDamage == 0 && spell.highDamage == 0) {
				//rogue
				if (spell.spellName == "Stealth") {
					if (status == "STEALTHED") {
						status = "normal";
						cout << "You are already in Stealth . . ." << endl;
						cout << "The attacking " << monster.getName() << " found you!" << endl;
						return false;
					}
					else if (!inCombat) {
						status = "STEALTHED";
						cout << "You have entered Stealth, and may not attack until next turn." << endl;
						return false;
					}
					else if (inCombat) {
						cout << "Cannot enter Stealth in combat." << endl;
						return false;
					}
				}
				//mage
				if (spell.spellName == "Combustion") {
					status = "COMBUSTION";
					gainOrUseResources(spell.cost);
					cout << "Your critical strike chance has been increased by 100% for your next spell." << endl;
					return false;
				}
				//warrior
				if (spell.spellName == "Battle Shout") {
					status = "BATTLE SHOUT";
					gainOrUseResources(spell.cost);
					cout << "You shout viciously, gaining 25 Rage." << endl;
				}
			}

			enterCombat();
			this_thread::sleep_for(chrono::milliseconds(wait1));

			if (notEnoughResources(spell.cost) || spell.spellName == "Battle Shout") {
				totalDamage = *primary + 10;
				if (getClass() == "Warrior") gainOrUseResources((int)round(totalDamage / 2));
				overkill = totalDamage > monster.getHealth();

				if (notEnoughResources(spell.cost)) {
					cout << endl << "You don't have enough resources to use that ability" << endl;
					cout << "You melee swing the " << monster.getName() << " instead for . . ." << endl;
					cout << totalDamage << " damage!";
				}
				else if (spell.spellName == "Battle Shout") {
					cout << "You melee swing the " << monster.getName() << " for . . ." << endl;
					cout << totalDamage << " damage!";
				}
			}
			else {
				cout << endl << "Rolling dice.." << endl << endl;
				this_thread::sleep_for(chrono::milliseconds(wait2));
				cout << "Your " << spell.spellName << " hits the " << monster.getName() << " for . . . Rolling dice . . . " << endl;
				this_thread::sleep_for(chrono::milliseconds(wait2));

				modifier = (int)round(spell.modifier * (double)*primary);
				damage = rand() % spell.highDamage + spell.lowDamage;
				critRoll = rand() % 100 + 1;//roll between 1-100

				if (critRoll < getCritChance()) {//crit
					totalDamage = ((modifier + damage) * critDamage) / 100;
					overkill = totalDamage > monster.getHealth();
					cout << totalDamage << " CRITICAL damage!";
				}
				else {//non-crit
					totalDamage = (modifier + damage);
					overkill = totalDamage > monster.getHealth();
					cout << totalDamage << " damage!";
				}
			}

			if (overkill) {
				cout << " (" << totalDamage - monster.getHealth() << " OVERKILL)";
			}
			cout << endl;
			monster.takeDamage(totalDamage);
			if (getClass() == "Warrior") gainOrUseResources((int)round(totalDamage / 2));
			gainOrUseResources(spell.cost);
			return false;
		case 2://runaway
			runAwayRoll = rand() % 5 + 1;
			if (runAwayRoll >= 3) {
				cout << "You ran away from the " << monster.getName() << endl;
				return true;
			}
			else if (runAwayRoll < 3) {
				cout << "You failed to run away from the " << monster.getName() << endl;
				return false;
			}
			else
				return true;
		case 3://enemy stats
			cout << "Enemy " << monster.getName() << ":" << endl;
			cout << "Current HP : " << monster.getHealth() << endl;
			cout << "Level: " << monster.getLevel() << endl;
			continue;
		case 4://player stats
			getStats();
			continue;
		default://else
			cout << "Invalid option" << endl;
			continue;
		}
	}
	return false;
}
void Player::takeDamage(int damage) {
	healthPoints -= damage;
}

void Player::enterCombat(){
	inCombat = true;
}

void Player::leaveCombat() {
	inCombat = false;
}

void Player::rest() {
	cout << "Resting uses 1 move. Your HP has been restored to full." << endl;
	setHealth(maxHealthPoints);
}

bool Player::isDead() {
	return healthPoints <= 0;
}

void Player::victory(Monster& monster) {
	cout << "You won the battle!" << endl;
	cout << "You gained " << monster.getEXP() << " experience points." << endl;
	cout << "You looted " << monster.getGold() << " Gold pieces." << endl << endl;
	experience += monster.getEXP();
	playerGold += monster.getGold();
}

void Player::levelUp() {
	if (experience >= nextLevelExp) {
		cout << "Congrats! You have gained a Level!" << endl << endl;
		cout << "Your health has been restored to full" << endl;
		cout << "Your stats have also been increased" << endl << endl;

		experience = experience - nextLevelExp;
		nextLevelExp = nextLevelExp + (int)((double)nextLevelExp * 0.40);
		++level;

		int modA = 0; int modS = 0; int modI = 0; int modHP = 0;

		//inc all stats by 1, health by 1
		if (this->getClass() == "Rogue") {
			modA = 2;
			modI += 1;
			modS += 1;
			modHP += 10;
		}
		if (this->getClass() == "Mage") {
			modA = 1;
			modI += 2;
			modS += 0;
			modHP += 10;
		}
		if (this->getClass() == "Warrior") {
			modA = 1;
			modI += 0;
			modS += 2;
			modHP += 20;
		}

		agility += modA;
		intelligence += modI;
		strength += modS;
		maxHealthPoints += modHP;

		cout << "Your Agility has been increased by: " << modA << endl;
		cout << "Your Intelligence has been increased by: " << modI << endl;
		cout << "Your Strength has been increased by: " << modS << endl;
		cout << "Your Maximum Health Points have been increased by: " << modHP << endl;

		//restore health
		healthPoints = maxHealthPoints;
	}
	else if (experience < nextLevelExp) {
		cout << "You are " << nextLevelExp - experience << " experience points away from leveling up!" << endl;
	}
}

bool Player::gameOver() {
	cout << "You died in battle . . ." << endl << endl;
	cout << "=========================" << endl;
	cout << "========GAME OVER========" << endl;
	cout << "=========================" << endl;
	cout << "Press 0 to quit : " << endl;
	cout << "Press 1 to start over : " << endl;
	int input = -1;
	cin >> input;
	cout << endl;

	cout << "input: " << input << endl;
	switch(input) {
	case 0:
		return true;
	case 1:
		return false;
	default:
		return true;
	}
}

void Player::displayPlayerGold() {
	cout << "Player Gold: " << playerGold << endl;
}

void Player::displayEXPBar() {
	int step = 0;
	int displayNext = step;
	int percent = 0;

	cout << endl << "Level: " << level << endl;
	percent = (100 * (experience + 1)) / nextLevelExp;
	if (percent >= displayNext)
	{
		cout << "\r" << "[" << std::string(percent / 5, (char)254u) << string(100 / 5 - percent / 5, ' ') << "]";
		cout << "[ " << experience << " / " << nextLevelExp << " ] EXP" << endl;
		std::cout.flush();
		displayNext += step;
	}
	
	cout << endl;
}

void Player::useResources(int cost) {
	currentResourcePoints -= cost;
}

void Player::gainResources(int cost) {
	currentResourcePoints += cost;
}

void Player::gainOrUseResources(int cost) {

	bool debug = false;
	string grammer;
	if (cost > 0) grammer = "gain";
	else if (cost < 0) grammer = "used";

	if (debug) {
		if (getClass() == "Warrior") cout << "You " << grammer << " " << cost << " Rage." << endl;
		if (getClass() == "Rogue") cout << "You " << grammer << " " << cost << " Energy." << endl;
		if (getClass() == "Mage") cout << "You " << grammer << " " << cost << " Mana." << endl;
	}

	currentResourcePoints += cost;
}

bool Player::notEnoughResources(int cost) {
	return abs(cost) > currentResourcePoints;
}

void Player::initializePlayer() {
	if (getClass() == "Mage") {
		currentResourcePoints = maxResourcePoints;
	}
	else {
		currentResourcePoints = initResourcePoints;
	}
	status = "normal";
	turn = 0;
	leaveCombat();
}

void Player::roundOver() {
	if (getClass() == "Rogue") {
		currentResourcePoints += 20;
	}
	turn += 1;
}

bool Player::validInput() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input, try again" << endl;
		return false;
	}
	else {
		return true;
	}
}

void Player::visitShop() {

	bool shopping = true;
	int loopCounter = 0;
	int input;

	while (shopping) {
		if (loopCounter == 0) {
			cout << "You have arrived at the shop." << endl;
			cout << "This has cost you 5 moves." << endl;
		}
		input = -1;
		loopCounter++;
		system("pause");
		system("cls");
		displayPlayerGold();
		cout << "Each upgrade costs 10 Gold pieces." << endl;
		cout << endl << "Choose an attribute to permanently increase: " << endl;
		cout << "1. Agility" << endl;
		cout << "2. Intelligence" << endl;
		cout << "3. Strength" << endl;
		cout << "4. Exit the Shop" << endl;
		cin >> input;
		system("cls");
		if (!validInput()) continue;

		switch (input) {

		case 1://agility
			if (playerGold >= 10) {
				agility += 1;
				playerGold -= 10;
				system("cls");
				cout << "Your Agility has been increased by 1. You now have " << agility << " Agility." << endl;
				break;
			}
			else {
				cout << "Not enough Gold pieces." << endl;
				continue;
			}
		case 2://intelligence
			if (playerGold >= 10) {
				intelligence += 1;
				playerGold -= 10;
				system("cls");
				cout << "Your Intelligence has been increased by 1. You now have " << intelligence << " Intelligence." << endl;
				break;
			}
			else {
				cout << "Not enough Gold pieces." << endl;
				continue;
			}
		case 3://strength
			if (playerGold >= 10) {
				strength += 1;
				playerGold -= 10;
				system("cls");
				cout << "Your Strength has been increased by 1. You now have " << strength << " Strength." << endl;
				break;
			}
			else {
				cout << "Not enough Gold pieces." << endl;
				continue;
			}
		case 4://exit
			return;
		default://else
			cout << "Invalid option" << endl;
			continue;
		}
	}
}
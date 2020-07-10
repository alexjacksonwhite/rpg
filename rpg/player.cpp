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
	primary;
	experience = 0;
	nextLevelExp = 1000;
	level = 1;
	currentResourcePoints = 0;
	maxResourcePoints = 0;
	initResourcePoints = 0;
	critChance = 0;
	critDamage = 0;
	mSpells;
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
int Player::getHealthPoints() { return healthPoints; }
int Player::getCurrentResourcePoints() { return currentResourcePoints; }

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
	cout << left << setw(20) << "Strength: " << intelligence << endl;
	cout << left << setw(20) << "Crit Chance: " << critChance << "%" << endl;
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
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			cout << "Invalid input, try again" << endl;
			system("pause");
			system("cls");
			continue;
		}

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
			addSpell("Backstab", "ENERGY", 60, 13, 17, 1.3);
			addSpell("Stealth", "ENERGY", 0, 0, 0, 0);
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
			currentResourcePoints = 150;
			maxResourcePoints = 150;
			initResourcePoints = maxResourcePoints;
			experience = 0;
			nextLevelExp = 1000;
			level = 1;
			healthPoints = 100;
			maxHealthPoints = 100;
			addSpell("Fireball", "MANA", 20, 9, 11, 1.2);
			addSpell("Ice Armor", "MANA", 10, 0, 0, 0);
			classNotChosen = false;
			break;
		case 3: //Warrior
			this->c = "Warrior";
			resource = "RAGE";
			agility = 4;
			strength = 5;
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
			addSpell("Rend", "RAGE", -15, 6, 9, 1.4);
			addSpell("Battle Shout", "RAGE", 15, 0, 0, 0);
			classNotChosen = false;
			//addSpell("Execute", "RAGE", 30, ((1.5 * strength) + currentResourcePoints + 15));
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
	//mSpells.push_back({ spellName,resource,cost,lowDamage,highDamage,modifier });
}


bool Player::attackMonster(Monster& monster) {

	bool fastAnimations = false;
	bool combat = true;
	int damage, modifier, critRoll, totalDamage, runAwayRoll, spellCost, wait1, wait2 = 0;
	int input;
	string spell;

	if (!fastAnimations) {
		wait1 = 400;
		wait2 = 1000;
	}

	while (combat) {
		system("pause");
		system("cls");
		cout << "A(n) " << monster.getName() << " is attacking you! What do you do?" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Run" << endl;
		cout << "3. View Resources" << endl;
		input = -1;
		cin >> input;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again" << endl;
			continue;
		}

		switch (input) {
		case 1://attack
			this_thread::sleep_for(chrono::milliseconds(wait1));
			spellCost = mSpells.at(0).cost;
			if (notEnoughResources(spellCost)) {
				cout << endl << "You don't have enough resources to use that ability . . ." << endl;
				cout << "You melee swing the monster instead for " << *primary+10 << endl;
				monster.takeDamage(*primary+10);
				return false;
			}

			spell = mSpells.at(0).spellName;
			cout << endl << "Rolling dice.." << endl << endl;
			this_thread::sleep_for(chrono::milliseconds(wait2));
			cout << "Your " << spell << " hits the  " << monster.getName() << "  for . . . Rolling dice . . . " << endl;
			this_thread::sleep_for(chrono::milliseconds(wait2));

			modifier = (int)round(mSpells.at(0).modifier * (double)*primary);
			damage = rand() % mSpells.at(0).highDamage + mSpells.at(0).lowDamage;
			critRoll = rand() % 100 + 1;//roll between 1-100

			if (critRoll < critChance) {//crit
				totalDamage = ((modifier + damage) * critDamage) / 100;
				bool overkill = totalDamage > monster.getHealth();
				cout << totalDamage << " CRITICAL damage!";
				if (overkill)
					cout << " (" << totalDamage - monster.getHealth() << " OVERKILL) ";
				cout << endl;
			}
			else {//non-crit
				totalDamage = (modifier + damage);
				bool overkill = totalDamage > monster.getHealth();
				cout << totalDamage << " damage!";
				if (overkill)
					cout << " (" << totalDamage - monster.getHealth() << " OVERKILL) ";
				cout << endl;
			}
			monster.takeDamage(totalDamage);
			useResources(spellCost);
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
		case 3://stats
			cout << "Your current HP:  " << getHealthPoints() << endl;
			cout << "Current resources:  " << getCurrentResourcePoints() << endl;
			cout << endl << "Enemy " << monster.getName() << " current HP: " << monster.getHealth() << endl;
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

void Player::rest() {
	cout << "Resting. HP restored to full." << endl;
	setHealth(maxHealthPoints);
}

bool Player::isDead() {
	return healthPoints <= 0;
}

void Player::victory(int xp) {
	cout << "You won the battle!" << endl;
	cout << "You win " << xp << " experience points!" << endl << endl;
	experience += xp;
}

void Player::levelUp() {
	if (experience >= nextLevelExp) {
		cout << "Congrats! You have gained a Level!" << endl << endl;
		cout << "Your health has been restored to full" << endl;
		cout << "Your stats have also been increased" << endl << endl;

		nextLevelExp = nextLevelExp + (int)((double)nextLevelExp * 0.40);
		++level;
		experience = 0;

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

void Player::displayEXP() {

}

void Player::useResources(int cost) {
	currentResourcePoints -= cost;
}

bool Player::notEnoughResources(int cost) {
	return cost > currentResourcePoints;
}

void Player::initializeResourcePoints() {
	if (getClass() == "Mage") {
		currentResourcePoints = maxResourcePoints;
	}
	else {
		currentResourcePoints = initResourcePoints;
	}
}

void Player::roundOver() {
	if (getClass() == "Rogue") {
		currentResourcePoints += 20;
	}
}
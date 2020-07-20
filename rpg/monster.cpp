#include <iostream>
#include <string>
#include "monster.h"
#include "player.h"
#include <thread>

using namespace std;

Monster::Monster(const std::string& name, int hp, int exp, int level, int armor, int lowDamage, int highDamage) {
	mName = name;
	mHp = hp;
	mExp = exp;
	mArmor = armor;
	mLevel = level;
	mLowDamage = lowDamage;
	mHighDamage = highDamage;
	mGold = generateGold(level);
}

int	Monster::generateGold(int level) {
	return rand() % (5 + level) + 4;//roll between 4-5 and add for each level
}

bool Monster::isDead() {
	return mHp <= 0;
}

int Monster::getEXP() {
	return mExp;
}

int Monster::getArmor() {
	return mArmor;
}

int Monster::getHealth() {
	return mHp;
}

int Monster::getGold() {
	return mGold;
}

int Monster::getLevel() {
	return mLevel;
}

std::string Monster::getName() {
	return mName;
}

void Monster::attackPlayer(Player& player) {

	bool fastAnimations = false;
	int wait1 = 0;
	int damage = rand() % mLowDamage + mHighDamage;

	if (!fastAnimations) wait1 = 1000;

	if (player.getStatus() == "STEALTHED") {
		cout << "The " << mName << " was unable to find you in stealth." << endl;
		damage = 0;
	}
	else {
		cout << "The " << mName << " attacks you for . . . Rolling dice . . ." << endl;
		this_thread::sleep_for(std::chrono::milliseconds(wait1));
		cout << damage << " damage!" << endl;
	}
	player.takeDamage(damage);
	if (player.getClass() == "Warrior") player.gainOrUseResources((int)round(damage / 2));
}

void Monster::takeDamage(int damage) {
	mHp -= damage;
}

void Monster::displayHealth() {
	std::cout << mName << "'s hitpoints: " << getHealth() << std::endl;
}


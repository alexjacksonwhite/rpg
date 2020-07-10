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

std::string Monster::getName() {
	return mName;
}

void Monster::attackPlayer(Player& player) {

	bool fastAnimations = false;
	int wait1 = 0;
	int damage = rand() % mLowDamage + mHighDamage;
	if (!fastAnimations) wait1 = 1000;

	cout << "The " << mName << " attacks you for . . . Rolling dice . . ." << endl;
	this_thread::sleep_for(std::chrono::milliseconds(wait1));
	cout << damage << " damage!" << endl;
	player.takeDamage(mLowDamage);
}

void Monster::takeDamage(int damage) {
	mHp -= damage;
}

void Monster::displayHealth() {
	std::cout << mName << "'s hitpoints: " << getHealth() << std::endl;
}


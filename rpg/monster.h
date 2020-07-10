#pragma once
#include "player.h"
#include <string>

class Player;

class Monster {
public:
	Monster(const std::string& name, int hp, int exp, int level, int armor, int lowDamage, int highDamage);

	bool	isDead();

	int		getEXP();
	std::string	getName();
	int		getArmor();
	int		getHealth();

	void	attackPlayer(Player& player);
	void	takeDamage(int damage);
	void	displayHealth();

private:
	std::string	mName;
	int		mHp;
	int		mExp;
	int		mArmor;
	int		mLevel;
	int		mLowDamage;
	int		mHighDamage;
};
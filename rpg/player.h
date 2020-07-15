#pragma once
#include <string>
#include <vector>
#include "monster.h"

class Monster;

class Player {

public:

	//constructor
	Player();

	//setters
	void	setName(std::string name);
	void	setClass(std::string c);
	void	setHealth(int hp);

	//getters
	std::string	getName();
	std::string	getClass();
	int		getHealthPoints();
	void	getStats();
	int		getCurrentResourcePoints();

	//biggers
	void	createCharacter();
	void	addSpell(std::string spellName, std::string resource, int cost, int lowDamage, int highDamage, double modifier);
	bool	attackMonster(Monster& monster);
	void	takeDamage(int damage);
	void	rest();
	bool	isDead();
	bool	notEnoughResources(int cost);
	void	victory(Monster& monster);
	void	levelUp();
	bool	gameOver();
	void	displayEXPBar();
	void	useResources(int cost);
	void	roundOver();
	void	initializeResourcePoints();
	void	displayPlayerGold();
	void	visitShop();

private:
	std::string	name;
	std::string	c;
	std::string	resource;
	int		critChance;
	int		critDamage;
	int		*primary;
	int		currentResourcePoints;
	int		maxResourcePoints;
	int		initResourcePoints;
	int		healthPoints;
	int		maxHealthPoints;
	int		stamina;
	int		agility;
	int		strength;
	int		intelligence;
	int		experience;
	int		level;
	int		nextLevelExp;
	int		playerGold;

	struct spells {
		std::string spellName;
		std::string	resource;
		int		cost;
		int		lowDamage;
		int		highDamage;
		double	modifier;
	};

	std::vector<spells> mSpells;
};
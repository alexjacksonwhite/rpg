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
	std::string getStatus();
	bool	getInCombat();
	int		getHealthPoints();
	void	getStats();
	int		getCurrentResourcePoints();
	int		getCritChance();

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
	void	gainResources(int cost);
	void	gainOrUseResources(int cost);
	void	roundOver();
	void	initializePlayer();
	void	displayPlayerGold();
	void	visitShop();
	bool	validInput();
	void	enterCombat();
	void	leaveCombat();

private:
	std::string	name;
	std::string	c;
	std::string	resource;
	std::string status;
	bool	inCombat;
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
	int		turn;
	int		castTime;

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
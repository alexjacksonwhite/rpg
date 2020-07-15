#pragma once
#include <string>
#include "monster.h"

class Game {
public:

	//constructor
	Game();

	// getters
	int			getX();
	int			getY();
	int			getRemainingMoves();

	// doers
	void		initGame();
	void		movePlayer();
	Monster*	randomizeMonster();

	// logic
	bool		noMovesLeft();
	void		deductMoves(int moves);
	void		rewardMoves(int moves);

	// printers
	void		printPlayerPos();
	void		printRemainingMoves();
	void		printGameStats();
	void		intro();

private:
	int			mPlayerX;
	int			mPlayerY;
	int			remainingMoves;
};
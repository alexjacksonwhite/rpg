#include "player.h"
#include "game.h"
#include <string>
#include <iostream>
#include <ctime>

//http://www.cplusplus.com/forum/beginner/127189/

using namespace std;


int main(){

    srand(time(NULL));
    Game game;
    Player player;
    game.intro();
    player.createCharacter();
    player.getStats();
    bool gameOver = false;

    while (!gameOver) {

        if (game.noMovesLeft()) gameOver = true;

        int input = -1;
        Monster* monster = 0;
        system("pause");
        system("cls");
        game.printGameStats();
        player.displayEXPBar();

        cout << "Waiting on player input" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Move" << endl;
        cout << "2. Rest" << endl;
        cout << "3. Stats" << endl;
        cout << "4. Choose another Class (Only for Testing)" << endl;
        cin >> input;
        system("cls");

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again" << endl;
            continue;
        }

        switch (input) {
        case 0://quit
            return 0;
        case 1://move
            game.movePlayer();
            monster = game.randomizeMonster();
            if (monster != 0) {
                while (true) {
                    bool runAway = player.attackMonster(*monster);
                    if (runAway) {
                        player.initializeResourcePoints();
                        break;
                    }
                    if (monster->isDead()) {
                        player.victory(monster->getEXP());
                        player.levelUp();
                        player.initializeResourcePoints();
                        break;
                    }
                    monster->attackPlayer(player);
                    if (player.isDead()) {
                        gameOver = player.gameOver();
                        if (!gameOver) {
                            game.initGame();
                            game.intro();
                            player.createCharacter();
                            player.getStats();
                        }
                        break;
                    }
                    player.roundOver();
                }
                delete monster;
                monster = 0;
            }
            break;
        case 2://rest
            player.rest();
            break;
        case 3://stats
            player.getStats();
            break;
        case 4://class
            player.createCharacter();
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }//switch
    }//while
    return 0;
}//main
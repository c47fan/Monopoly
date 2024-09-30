#include <string> 
#include <iostream> 
#include <sstream> 
#include <time.h>
#include <memory>
#include "board.h"
#include "game.h"
#include "player.h"
#include "boardDisplay.h"

using namespace std;

int main(int argc, char *argv[]) {

    string command; 
    string fileName = "";
    bool testingOn = false; // testing mode indicator
    bool loadedGame = false; // using saved game indicator 

    // Process command line arguments 
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            command = argv[i];

            if (command == "-load") { // -load file command
                loadedGame = true; 
                fileName = argv[i + 1];
                cout << "ATTENTION: CONTINUING SAVED GAME" << endl;
            }

            else if (command == "-testing") { // -testing command
                testingOn = true;
                cout << "ATTENTION: ENTERING TESTING MODE" << endl;
            }
        }
    }

    // Initialize game and board
    Game g;
    Board b;

    g.setBoard(&b); 
    BoardDisplay bd{&b};
    b.createBoard();
    g.initGame(testingOn, loadedGame, fileName); 
    b.notifyObservers();
    g.runGame(testingOn);
}

#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "board.h"
#include <vector>
#include <memory>

class Game {
    Board* board;
    std::vector<std::shared_ptr<Player>> players;
    int curPlayer;

    bool doubleRoll;
    int doubles;
    int rolls;


public: 
    Game(bool doubleRoll = false, int doubles = 0, int rolls = 0);
    ~Game();
    void addPlayer(std::shared_ptr<Player> newPlayer);
    void removePlayer(std::shared_ptr<Player> player);
    void nextPlayer();

    std::shared_ptr<Player> getCurrentPlayer() const;
    void setCurrentPlayer();
    void setBoard(Board* board);
    std::shared_ptr<Player> findPlayer(std::string name) const;

    void loadGame(std::string fileName);
    void initGame(bool testingOn, bool loadedGame, std::string fileName);
    void runGame(bool testingOn);
    bool oweMoney(std::shared_ptr<Player> player, std::shared_ptr<Player> owePlayer);
    bool gameOver();

    int rollDice(bool testingOn);
    std::shared_ptr<Buildings> findBuilding(std::string name);

    // Commands
    void printCommands();
    bool rollCommand(bool testingOn); 
    void nextCommand();
    void improveCommand();
    void allCommand();
    void mortgageCommand();
    void unMortgageCommand();
    void tradeCommand();
    void saveCommand();

    // Trade Helper
    bool validTrade(std::string name, std::string give, std::string receive, std::shared_ptr<Player> otherPlayer);

    // Mortgage Helpers
    bool validMortgageCheck(std::string propertyName);
    bool validUnMortgageCheck(std::string proeprtyName);

    // DC Tim's Line
    void leaveDCLine();

    // declare bankruptcy
    bool declareBankruptcy(std::shared_ptr<Player> player, std::shared_ptr<Player> owePlayer);
};

#endif

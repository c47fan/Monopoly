#ifndef __SQUARES_H__
#define __SQUARES_H__
#include <vector>
#include <string>
#include <memory>
#include "player.h"

class Board;

class Squares {
    int position;
    std::string name;
    std::vector<char> onSquare;

    // Check for buildings or non-property
    bool isOwnable;
    
public:
    Squares(int position, std::string name, bool isOwnable = false);
    Squares();
    std::vector<char> hasPlayers();
    void placePlayer(std::shared_ptr<Player> player);
    void removePlayer(std::shared_ptr<Player> player);
    std::string getName();
    virtual ~Squares();
    virtual void action(std::string name, std::shared_ptr<Player> player, Board* board);

    bool getIsOwnable();
    int getPosition();
};

#endif

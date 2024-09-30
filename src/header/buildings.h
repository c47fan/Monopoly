#ifndef __BUILDINGS_H__
#define __BUILDINGS_H__
#include "player.h"
#include <memory> 
#include "squares.h"

class Buildings : public Squares {
    std::shared_ptr<Player> whoOwns;
    int cost;
    bool mortgaged;
    bool isOwned;
public:
    Buildings(int position, std::string name, int cost, bool mortgaged = false, bool isOwned = false);
    void setOwner(std::shared_ptr<Player> player);
    std::shared_ptr<Player> getOwner();
    int getCost();
    bool getIsOwned(); 
    void setIsOwned();
    void setMortgaged();
    void setUnMortgage();
    bool getIsMortgaged();
    virtual int getRent(int numTypeOwned, bool monopolyOwned) = 0;
};

#endif

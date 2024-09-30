#ifndef __NONPROPERTY_H__
#define __NONPROPERTY_H__

#include <string>
#include "squares.h"
#include "academicbuildings.h"


class Board; 

class NonProperty: public Squares {
    std::string description;
public: 
    NonProperty(int position, std::string name);
    void action(std::string name, std::shared_ptr<Player> player, Board* board) override;

    void collectOSAP(std::shared_ptr<Player> player);
    void dcTimsLine(std::shared_ptr<Player> player, Board* board);
    void goToTims(std::shared_ptr<Player> playerr, Board* board);
    void gooseNesting(std::shared_ptr<Player> playerayer);
    void tuition(std::shared_ptr<Player> player);
    void coopFee(std::shared_ptr<Player> player);
    void slc(std::shared_ptr<Player> player, Board* board);
    void needlesHall(std::shared_ptr<Player> player, Board* board);

};

#endif

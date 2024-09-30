#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <map>

#include "subject.h"
#include "player.h"
#include "squares.h"
#include "academicbuildings.h"
#include "gyms.h"
#include "residences.h"
#include "nonproperty.h"

class Board: public Subject {
    private:
        std::vector<std::shared_ptr<Squares>> squares;
        std::vector<std::shared_ptr<Buildings>> buildings;
        std::map<int, int> buildingMap;
        std::map<std::string, int> monopolies;
        int totalRollUpTheRimCups = 0;
        bool movedAgain = false;

    public:
        Board();
        virtual ~Board(); // For inherited destructors
        void createBoard();

        int getTotalRollUpTheRimCups();
        void addTotalRollUpTheRimCups(int cups);
        void subTotalRollUpTheRimCups();

        bool getMovedAgain();
        void setMovedAgain(bool moved);

        void movePlayer(std::shared_ptr<Player> player, int steps);
        int findDistance(std::shared_ptr<Player> player, int destinationPos);

        void takeAction(std::shared_ptr<Player> player, std::shared_ptr<Squares> square, std::vector<std::shared_ptr<Player>> listOfPlayers);
        void auction(std::shared_ptr<Buildings> buildingForSale, std::vector<std::shared_ptr<Player>> listOfPlayers);  
        // bool bankruptcy();
        void buyProperty(std::shared_ptr<Player> player, std::shared_ptr<Buildings> building, std::vector<std::shared_ptr<Player>> listOfPlayers);
        std::string checkTypeProperty(std::shared_ptr<Buildings> property);
        void payRent(std::shared_ptr<Player> player, std::shared_ptr<Buildings> building);
        void buyImprovement(std::shared_ptr<Player> player, std::shared_ptr<AcademicBuildings> property);
        void sellImprovement(std::shared_ptr<Player> player, std::shared_ptr<AcademicBuildings> property);

        void personalAssets(std::shared_ptr<Player> player);

        std::vector<std::shared_ptr<Squares>> getSquares();
        std::vector<std::shared_ptr<Buildings>> getBuildings();
        std::map<int, int> getBuildingMap();

        std::shared_ptr<Buildings> findBuilding(std::string name);
        void updateMonopolies(std::shared_ptr<Player> player, std::shared_ptr<Buildings> property);
        void decreaseMonopolies(std::shared_ptr<Player> player, std::shared_ptr<Buildings> property);
        bool isMonopolyOwned(std::shared_ptr<Player> player, std::shared_ptr<Buildings> property);
        void oweMoney(int amount);

        void trade();
        // Trade Helpers
        void doTrade(std::string name, std::string give, std::string receive, std::shared_ptr<Player> curPlayer, std::shared_ptr<Player> otherPlayer);
};

#endif

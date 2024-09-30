#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

class Buildings;

class Player {
    std::string name;
    char boardPiece;
    int money;
    int position;

    std::vector<std::shared_ptr<Buildings>> properties;
    int TimsCups;
    bool isBankrupt = false;

    int numResOwned = 0;
    int numGymsOwned = 0;
    std::map<std::string, int> monopolies;

    bool dcTimsLine;
    int numTurnsDC;

    bool owesMoney = false;
    int amountOwed;

    public:
        Player(const std::string name, char boardPiece, int TimsCups = 0, int money = 1500, int position = 0, int numTurnsDC = 0, bool dcTimsLine = false);
        void addProperty(std::shared_ptr<Buildings> building);
        void removeProperty(std::shared_ptr<Buildings> building);
        
        // dont know fucntion params yet?
        void trade();
        void mortgage();
        void unmortgage();

        // Do we need this function? Just subMoney from player based on where game is
        void payRent(int amount);
        void declareBankruptcy();
        int getRollUpTheRimCup();
        void addRollUpTheRimCup(int cup);
        void useRollUpTheRimCup();
        void buyImprovement();
        void sellImprovement();

        // protected: // maybe should be protected?
        std::string getName() const;
        char getSymbol() const;
        int getPosition() const;

        int getMoney() const;
        void subMoney(int cost);
        void addMoney(int amount);

        void setNewPosition(int steps);
        // bool ownsProperties(std::shared_ptr<Buildings> building);
        // bool canAfford(int amount);    

        int getNumRes();
        int getNumGyms();
        void setNumRes(std::string action); 
        void setNumGyms(std::string action);

        void setOwesMoney(bool owes);
        bool getOwesMoney();
        void setAmountOwed(int amount);
        int getAmountOwed();
        bool getIsBankrupt();

        void setDcTimsLine(bool inLine);
        bool getDcTimsLine();

        int getNumTurnsDC();
        void setNumTurnsDC(std::string action);


        std::map<std::string, int> getMonopolies();
        void addToMonopoly(std::string name); 
        void subFromMonopoly(std::string name);

        std::vector<std::shared_ptr<Buildings>> getProperties();
};

#endif


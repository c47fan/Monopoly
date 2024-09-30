#include "player.h"
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "buildings.h"

using namespace std;

Player::Player(const std::string name, char boardPiece, int TimsCups, int money, int position, int numTurnsDC, bool dcTimsLine) : 
                name{name}, boardPiece{boardPiece}, TimsCups{TimsCups}, money{money}, position{position}, numTurnsDC{numTurnsDC}, dcTimsLine{dcTimsLine} {
    monopolies.insert(make_pair("Arts1", 0));
    monopolies.insert(make_pair("Arts2", 0));
    monopolies.insert(make_pair("Eng", 0));
    monopolies.insert(make_pair("Health", 0));
    monopolies.insert(make_pair("Env", 0));
    monopolies.insert(make_pair("Sci1", 0));
    monopolies.insert(make_pair("Sci2", 0));
    monopolies.insert(make_pair("Math", 0));
}

std::string Player::getName() const {
    return name;
}
    
void Player::addProperty(shared_ptr<Buildings> building) {
    properties.emplace_back(building);
}

void Player::removeProperty(shared_ptr<Buildings> building) {
    
    properties.erase(remove(properties.begin(), properties.end(), building), properties.end());
}

char Player::getSymbol() const {
    return boardPiece;
}

int Player::getPosition() const {
    return position;
}

int Player::getMoney() const {
    return money;
}

void Player::subMoney(int cost) {
    if (money >= cost) {
        money -= cost;
        cout << "------------------------------------------" << endl;
        cout << "Credit: " << name << " has just spent $" << cost << "."<< endl;
        cout << name << " now has $" << money << "." << endl;
        cout << "------------------------------------------" << endl;
    }
    // need to add a check if not enough money
}

void Player::addMoney(int amount) {
    money += amount;
    cout << "------------------------------------------" << endl;
    cout << "Deposit: " << name << " has just earned $" << amount << "."<< endl;
    cout << name << " now has $" << money << "." << endl;
    cout << "------------------------------------------" << endl;
}


void Player::setNewPosition(int steps) {
    int newPos = position + steps;
    bool collectOSAP;

    if (newPos >= 40) {
        // Going to DC Tim's line? 
        if (position == 30 || dcTimsLine) {
            cout << "Player is sent to DC Tim's Line. Do not collect $200 in OSAP." << endl;
            collectOSAP = false;
        } else {
            collectOSAP = true;
        }

        position = newPos - 40;

        if (collectOSAP) {
            cout << name << " collected $200 from OSAP." << endl;
            addMoney(200);
        }
    } else if (newPos < 0) {
        position = 40 + newPos;
    } else {
        position = newPos;
    }
}

void Player::declareBankruptcy() {
    isBankrupt = true;
    cout << getName() << " has just declared bankruptcy." << endl;
}

bool Player::getIsBankrupt() {
    return isBankrupt;
}
vector<shared_ptr<Buildings>> Player::getProperties() {
    return properties;
}

int Player::getNumRes() {
    return numResOwned;
}

int Player::getNumGyms() {
    return numGymsOwned;
}

void Player::setNumRes(string action) {
    if (action == "increase") {
        numResOwned++;
    }
    else if (action == "decrease") {
        numResOwned--;
    }
}

void Player::setNumGyms(string action) {
    if (action == "increase") {
        numGymsOwned++;
    }
    else if (action == "decrease") {
        numGymsOwned--;
    }
}

map<string, int> Player::getMonopolies() {
    return monopolies;
}

void Player::addToMonopoly(string name) {
    monopolies.find(name)->second++;  
}

void Player::subFromMonopoly(std::string name) {
    monopolies.find(name)->second--;
}

void Player::setOwesMoney(bool owes) {
    owesMoney = owes;
}

bool Player::getOwesMoney() {
    return owesMoney;
}

void Player::setAmountOwed(int amount) {
    amountOwed = amount;
}

int Player::getAmountOwed() {
    return amountOwed;
}

int Player::getRollUpTheRimCup() {
    return TimsCups;
}

void Player::addRollUpTheRimCup(int cup) {
    TimsCups += cup;
}

void Player::useRollUpTheRimCup() {
    TimsCups -= 1;
}

void Player::setDcTimsLine(bool inLine) {
    dcTimsLine = inLine;
}

bool Player::getDcTimsLine() {
    return dcTimsLine;
}

int Player::getNumTurnsDC() {
    return numTurnsDC;
}

void Player::setNumTurnsDC(string action) {
    if (action == "add") {
        numTurnsDC++;
    }
    else if (action == "reset") {
        numTurnsDC = 0;
    }
}


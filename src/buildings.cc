#include "buildings.h"

using namespace std;

Buildings::Buildings(int position, string name, int cost, bool mortgaged, bool isOwned) : Squares{position, name, true}, cost{cost}, mortgaged{mortgaged}, isOwned{isOwned} {}

void Buildings::setOwner(shared_ptr<Player>player) {
    whoOwns = player;
}

shared_ptr<Player> Buildings::getOwner() {
    return whoOwns;
}

int Buildings::getCost() {
    return cost;
}

bool Buildings::getIsOwned() {
    return isOwned;
}

void Buildings::setIsOwned() {
    isOwned = true;
}

bool Buildings::getIsMortgaged() {
    return mortgaged;
}

void Buildings::setMortgaged() {
    mortgaged = true;
}

void Buildings::setUnMortgage() {
    mortgaged = false;
}

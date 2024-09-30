#include "squares.h"
#include <algorithm>
#include "board.h"

using namespace std;

Squares::Squares(int position, string name, bool isOwnable) : position{position}, name{name}, isOwnable{isOwnable} {}

Squares::Squares() {}

Squares::~Squares() {}

vector<char> Squares::hasPlayers() {
    return onSquare;
}

void Squares::placePlayer(shared_ptr<Player> player) {
    char piece = player->getSymbol();
    onSquare.emplace_back(piece);
}

void Squares::removePlayer(shared_ptr<Player> player) {
    char piece = player->getSymbol(); 
    onSquare.erase(remove(onSquare.begin(), onSquare.end(), piece), onSquare.end());
}

string Squares::getName() {
    return name;
}

bool Squares::getIsOwnable() {
    return isOwnable;
}

void Squares::action(string name, shared_ptr<Player> player, Board* board) {
    
}

int Squares::getPosition() {
    return position;
}

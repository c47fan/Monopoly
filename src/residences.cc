#include "residences.h"

using namespace std;

Residences::Residences(int position, string name, int cost): Buildings{position, name, cost} {}

int Residences::getRent(int numResOwned, bool monopolyOwned) {
    if (numResOwned == 1) {
        return 25;
    }
    else if (numResOwned == 2) {
        return 50;
    }
    else if (numResOwned == 3) {
        return 100;
    }
    else if (numResOwned == 4) {
        return 200;
    }
}

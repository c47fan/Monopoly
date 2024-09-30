#include "gyms.h"

using namespace std;

Gyms::Gyms(int position, string name, int cost): Buildings{position, name, cost} {}

int rollDice() {
    int roll1; 
    int roll2; 

    srand(time(NULL)); // Seed random num generator with current time
    roll1 = rand() % 6 + 1;

    srand(roll1); // Seed random num generator with current time
    roll2 = rand() % 6 + 1; 

    int sum = roll1 + roll2;
    return sum; // return the sum of a random dice roll 
}

int Gyms::getRent(int numGymsOwned, bool monopolyOwned) {
    int dice = rollDice();
    cout << "Result of dice roll to calculate gym usage fee is " << dice << "." << endl;

    if (numGymsOwned == 1) {
        return 4 * dice;
    }
    else if (numGymsOwned == 2) {
        return 10 * dice;
    }
}

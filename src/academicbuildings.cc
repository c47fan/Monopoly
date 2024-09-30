#include "academicbuildings.h"

using namespace std;

AcademicBuildings::AcademicBuildings(int position, string name, int cost, string monopolyBlock, int impCost, vector<int> tuition, int numImp) : Buildings{position, name, cost}, monopolyBlock{monopolyBlock}, impCost{impCost}, tuition{tuition}, numImp{numImp} {}

int AcademicBuildings::getNumImp() {
    return numImp;
}

int AcademicBuildings::getRent(int numTypeOwned, bool monopolyOwned) {
    // tuition is doubled for each building that has no improvements when the monopoly is owned 
    if (monopolyOwned == true && numImp == 0) {
        cout << "This building has no improvements and the monopoly is owned. Tuition is doubled." << endl;
        return tuition[numImp] * 2;
    }
    return tuition[numImp];
}

void AcademicBuildings::setImprovement(string action) {
    if (action == "buy") {
        numImp++;
    }
    else if (action == "sell") {
        numImp--;
    }
}

int AcademicBuildings::getImpCost() {
    return impCost;
}

string AcademicBuildings::getMonopolyBlock()  {
    return monopolyBlock;
}



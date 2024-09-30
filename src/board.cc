#include "board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <map>
#include <iomanip>

using namespace std;

Board::Board() {}

Board::~Board() {} 

void Board::createBoard() {
    squares.emplace_back(make_shared<NonProperty> (0, "Collect OSAP"));
    squares.emplace_back(make_shared<AcademicBuildings> (1, "AL", 40, "Arts1", 50, vector<int>{2, 10, 30, 90, 160, 250}, 0));
    squares.emplace_back(make_shared<NonProperty> (2, "SLC"));
    squares.emplace_back(make_shared<AcademicBuildings> (3, "ML", 60, "Arts1", 50 , vector<int>{4, 20, 60, 180, 320, 450}, 0));
    squares.emplace_back(make_shared<NonProperty> (4, "TUITION"));
    squares.emplace_back(make_shared<Residences> (5, "MKV", 200));
    squares.emplace_back(make_shared<AcademicBuildings> (6, "ECH", 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}, 0));
    squares.emplace_back(make_shared<NonProperty> (7, "NEEDLES HALL"));
    squares.emplace_back(make_shared<AcademicBuildings> (8, "PAS", 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (9, "HH", 120, "Arts2", 50, vector<int>{8, 40, 100, 300, 450, 600}, 0));
    squares.emplace_back(make_shared<NonProperty> (10, "DC Tims Line"));
    squares.emplace_back(make_shared<AcademicBuildings> (11, "RCH", 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}, 0));
    squares.emplace_back(make_shared<Gyms> (12, "PAC", 150));
    squares.emplace_back(make_shared<AcademicBuildings> (13, "DWE", 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (14, "CPH", 160, "Eng", 100, vector<int>{12, 60, 180, 500, 700, 900}, 0));
    squares.emplace_back(make_shared<Residences> (15, "UWP", 200));
    squares.emplace_back(make_shared<AcademicBuildings> (16, "LHI", 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}, 0));
    squares.emplace_back(make_shared<NonProperty> (17, "SLC"));
    squares.emplace_back(make_shared<AcademicBuildings> (18, "BMH", 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (19, "OPT", 200, "Health", 100, vector<int>{16, 80, 220, 600, 800, 1000}, 0));
    squares.emplace_back(make_shared<NonProperty> (20, "Goose Nesting"));
    squares.emplace_back(make_shared<AcademicBuildings> (21, "EV1", 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}, 0));
    squares.emplace_back(make_shared<NonProperty> (22, "NEEDLES HALL"));
    squares.emplace_back(make_shared<AcademicBuildings> (23, "EV2", 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (24, "EV3", 240, "Env", 150, vector<int>{20, 100, 300, 750, 925, 1100}, 0));
    squares.emplace_back(make_shared<Residences> (25, "V1", 200));
    squares.emplace_back(make_shared<AcademicBuildings> (26, "PHYS", 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (27, "B1", 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}, 0));
    squares.emplace_back(make_shared<Gyms> (28, "CIF", 150));
    squares.emplace_back(make_shared<AcademicBuildings> (29, "B2", 280, "Sci1", 150, vector<int>{24, 120, 360, 850, 1025, 1200}, 0));
    squares.emplace_back(make_shared<NonProperty> (30, "Go To Tims"));
    squares.emplace_back(make_shared<AcademicBuildings> (31, "EIT", 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}, 0));
    squares.emplace_back(make_shared<AcademicBuildings> (32, "ESC", 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}, 0));
    squares.emplace_back(make_shared<NonProperty> (33, "SLC"));
    squares.emplace_back(make_shared<AcademicBuildings> (34, "C2", 320, "Sci2", 200, vector<int>{28, 150, 450, 1000, 1200, 1400}, 0));
    squares.emplace_back(make_shared<Residences> (35, "REV", 200));
    squares.emplace_back(make_shared<NonProperty> (36, "NEEDLES HALL"));
    squares.emplace_back(make_shared<AcademicBuildings> (37, "MC", 350, "Math", 200, vector<int>{35, 175, 500, 1100, 1300, 1500}, 0));
    squares.emplace_back(make_shared<NonProperty> (38, "COOP FEE"));
    squares.emplace_back(make_shared<AcademicBuildings> (39, "DC", 400, "Math", 200, vector<int>{50, 200, 600, 1400, 1700, 2000}, 0));

    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[1]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[3]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[5]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[6]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[8]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[9]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[11]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[12]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[13]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[14]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[15]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[16]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[18]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[19]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[21]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[23]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[24]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[25]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[26]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[27]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[28]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[29]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[31]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[32]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[34]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[35]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[37]));
    buildings.emplace_back(dynamic_pointer_cast<Buildings> (squares[39]));

    // (Index In <Squares>, Index in <Buildings>)
    buildingMap.insert(make_pair(1,0));
    buildingMap.insert(make_pair(3,1));
    buildingMap.insert(make_pair(5,2));
    buildingMap.insert(make_pair(6,3));
    buildingMap.insert(make_pair(8,4));
    buildingMap.insert(make_pair(9,5));
    buildingMap.insert(make_pair(11,6));
    buildingMap.insert(make_pair(12,7));
    buildingMap.insert(make_pair(13,8));
    buildingMap.insert(make_pair(14,9));
    buildingMap.insert(make_pair(15,10));
    buildingMap.insert(make_pair(16,11));
    buildingMap.insert(make_pair(18,12));
    buildingMap.insert(make_pair(19,13));
    buildingMap.insert(make_pair(21,14));
    buildingMap.insert(make_pair(23,15));
    buildingMap.insert(make_pair(24,16));
    buildingMap.insert(make_pair(25,17));
    buildingMap.insert(make_pair(26,18));
    buildingMap.insert(make_pair(27,19));
    buildingMap.insert(make_pair(28,20));
    buildingMap.insert(make_pair(29,21));
    buildingMap.insert(make_pair(31,22));
    buildingMap.insert(make_pair(32,23));
    buildingMap.insert(make_pair(34,24));
    buildingMap.insert(make_pair(35,25));
    buildingMap.insert(make_pair(37,26));
    buildingMap.insert(make_pair(39,27));

    // (Monopoly name, number of buildings in the monopoly)
    monopolies.insert(make_pair("Arts1", 2));
    monopolies.insert(make_pair("Arts2", 3));
    monopolies.insert(make_pair("Eng", 3));
    monopolies.insert(make_pair("Health", 3));
    monopolies.insert(make_pair("Env", 3));
    monopolies.insert(make_pair("Sci1", 3));
    monopolies.insert(make_pair("Sci2", 3));
    monopolies.insert(make_pair("Math", 2));

    notifyObservers();
}

int Board::getTotalRollUpTheRimCups() {
    return totalRollUpTheRimCups;
}

void Board::addTotalRollUpTheRimCups(int cups) {
    totalRollUpTheRimCups += cups;
}

void Board::subTotalRollUpTheRimCups() {
    totalRollUpTheRimCups--;
}

bool Board::getMovedAgain() {
    return movedAgain;
}

void Board::setMovedAgain(bool moved) {
    movedAgain = moved;
}


void Board::movePlayer(shared_ptr<Player> player, int steps) {
    player->setNewPosition(steps);
    int i = player->getPosition();

    // Update the current players on the square it moved to 
    squares[i]->placePlayer(player);
    notifyObservers();
}

int Board::findDistance(shared_ptr<Player> player, int destinationPos) {
    int distance = destinationPos - player->getPosition();
    return distance;
}

// Controls flow after a player arrives at a square
void Board::takeAction(shared_ptr<Player> player, shared_ptr<Squares> square, vector<shared_ptr<Player>> listOfPlayers) { 
    int position = player->getPosition(); 
    // cout << "take action is gonna get called" << endl;
    // If the square is a non-property, call the action method for the non-property 
    if (!square->getIsOwnable()) {
        // cout << "square action is gonna get called" << endl;
        square->action(square->getName(), player, this);
        if (movedAgain) {
            movedAgain = false;
            takeAction(player, squares[player->getPosition()], listOfPlayers);
        }
    } 
    // If the square is a property
    else if (square->getIsOwnable()) {
        shared_ptr<Buildings> currBuilding = buildings.at(buildingMap.find(position)->second); 
        // Building is not owned
        if (currBuilding->getIsOwned() == false) {
            buyProperty(player, currBuilding, listOfPlayers); 
        } 
        // Building is owned
        else if (currBuilding->getIsOwned() == true) {
            // You own the property
            if (currBuilding->getOwner() == player) {
                cout << "You own this property!" << endl;
            }
            else {
                payRent(player, currBuilding); 
            }
        }
    }
}


// Helper for buyProperty to determine the type of building
string Board::checkTypeProperty(shared_ptr<Buildings> property) {
    if (dynamic_pointer_cast<Residences>(property)) {
        return "Residences";
    }
    else if (dynamic_pointer_cast<Gyms>(property)) {
        return "Gyms";
    }
    else if (dynamic_pointer_cast<AcademicBuildings>(property)) {
        return "AcademicBuildings";
    } else {
        return "Something emssed up for checkTypeProperty";
    }
}

// Helper for buyProperty that increases building count in monopolies
void Board::updateMonopolies(shared_ptr<Player> player, shared_ptr<Buildings> property) {
    shared_ptr<AcademicBuildings> building = dynamic_pointer_cast<AcademicBuildings>(property);
    string monopolyName = building->getMonopolyBlock();
    player->addToMonopoly(monopolyName); 
}

// Helper for buyProperty that decreases building count in monopolies
void Board::decreaseMonopolies(shared_ptr<Player> player, shared_ptr<Buildings> property) {
    shared_ptr<AcademicBuildings> building = dynamic_pointer_cast<AcademicBuildings>(property);
    string monopolyName = building->getMonopolyBlock();
    player->subFromMonopoly(monopolyName); 
}

// Checks if the player owns all the properties in the monopoly
bool Board::isMonopolyOwned(shared_ptr<Player> player, shared_ptr<Buildings> property) {
    shared_ptr<AcademicBuildings> building = dynamic_pointer_cast<AcademicBuildings>(property);
    string monopolyName = building->getMonopolyBlock();

    // Compare the values in Board::monopoly and Player::monopoly
    if (monopolies.find(monopolyName)->second == player->getMonopolies().find(monopolyName)->second) {
        return true; // player has all the buildings in the monopoly
    } 
    return false;
}


void Board::buyProperty(shared_ptr<Player> player, shared_ptr<Buildings> property, vector<shared_ptr<Player>> listOfPlayers) {
    int price = property->getCost();
    cout << "Would you like to buy the property: " << property->getName() << " for $" << price << "?" << endl;
    cout << "Please enter either 'yes' or 'no': ";
    cout << endl;
    string input;

    while (1) {
        cin >> input;

        if (input == "yes") {
            // Check if almost bankrupt
            int playerBalance = player->getMoney() - price;

            if (playerBalance < 0) {
                cout << "Sorry you don't have enough to buy this property." << endl;
                auction(property, listOfPlayers);
                break;
            } 
            else { 
                // Successfully purchase the building
                cout << "Congratulations! You just purchased " << property->getName() << "!" << endl;
                player->subMoney(price); // decrease money
                property->setOwner(player);
                property->setIsOwned();

                // Check if the building is a residence, gym, academic building 
                if (checkTypeProperty(property) == "Residences") {
                    player->setNumRes("increase"); // increase residences owned
                }
                else if (checkTypeProperty(property) == "Gyms") {
                    player->setNumGyms("increase"); // increase gyms owned
                }
                else if (checkTypeProperty(property) == "AcademicBuildings") {
                    updateMonopolies(player, property); // increase monopoly count
                }
        
                player->addProperty(property);
                break;
            } 
        }

        else if (input == "no") {
            auction(property, listOfPlayers);
            break;
        } 
        
        else {
            cout << "Sorry that is invalid. Please enter either \"yes\" or \"no\"." << endl;
        }
    }
}

void Board::payRent(shared_ptr<Player> player, shared_ptr<Buildings> property) {
    shared_ptr<Player> owner = property->getOwner();

    int numTypeOwned = 0;
    bool monopolyOwned = false;

    // Check if the property is mortgaged or not
    if (property->getIsMortgaged()) {
        cout << property->getName() << " is mortagaged. No rent tuition will be paid" << endl;
        return;
    }

    // Check if the building is a residence, gym, or academic building
    if (checkTypeProperty(property) == "Residences") {
        numTypeOwned = owner->getNumRes();
    }
    else if (checkTypeProperty(property) == "Gyms") {
        numTypeOwned = owner->getNumGyms();
    }
    else if (checkTypeProperty(property) == "AcademicBuildings") {
        if (isMonopolyOwned(owner, property)){
            monopolyOwned = true;
        }
    }

    int amount = property->getRent(numTypeOwned, monopolyOwned);

    cout << "This property is owned by " << owner->getName() << "." << endl;
    cout << "The tuition/rent for this property is $" << amount << "." << endl;

    // *** ADD CHECK IF THE PLAYER CAN AFFORD RENT/TUITION ***'
    if (player->getMoney() < amount) {
        cout << "You do not have enough money to pay rent/tuition" << endl;
        player->setOwesMoney(true);
        player->setAmountOwed(amount);
    } else {
        player->subMoney(amount); 
        owner->addMoney(amount);
    }
}

void Board::auction(shared_ptr<Buildings> buildingForSale, vector<shared_ptr<Player>> listOfPlayers) {
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "ATTENTION: "<< buildingForSale->getName() << " is now up for auction! The regular value is $" << buildingForSale->getCost() << "." << endl;
    cout << "Get ready to place your bets!" << endl;
    
    int minBid = 0;
    vector<shared_ptr<Player>> remainingPlayers = listOfPlayers;
    int numRemainingPlayers = remainingPlayers.size();
    vector<bool> checkWithdrew;
    int indexPlayer = 0;
    int indexWinner = 0;
    for (long unsigned int i = 0; i < listOfPlayers.size(); i++) {
        checkWithdrew.emplace_back(false);
    }

    // Do not let a bankrupt player into the auction
    for (long unsigned int i = 0; i < listOfPlayers.size(); i++) {
        if (listOfPlayers[i]->getIsBankrupt()) {
            cout << "This player is bankrupt";
            checkWithdrew[i] = true;
        }
    }

    int bid;
    string input;
    do {
        if (checkWithdrew[indexPlayer] == false) {
            cout << remainingPlayers[indexPlayer]->getName() << ", please enter a bid greater than $" << minBid << endl;
            cout << "Type \"withdraw\" to withdraw from the auction" << endl;
            cin >> input;
            istringstream iss {input};
            if (iss >> bid) {
                cout << endl;
                cout << endl;
                cout << setfill('_') << setw(50) << "";
                cout << endl;
                cout << endl;
                if (bid > minBid) {
                    if (remainingPlayers.at(indexPlayer)->getMoney() - bid < 0) {
                        cout << "You do not have enough money for this bid. Either bid again or enter \"withdraw\"" << endl;
                        cout << endl;
                        cout << endl;
                    } else {
                        minBid = bid;
                        cout << "SUCCESS: " << remainingPlayers.at(indexPlayer)->getName() << " just set the minimum bid of $" << minBid << endl;
                        cout << endl;
                        cout << endl;
                        if (indexPlayer == remainingPlayers.size() - 1) {
                            indexPlayer = 0;
                        } else {
                            indexPlayer += 1;
                        }
                    }   
                } else {
                    cout << "FAIL: This bid is not enough." << endl;
                    cout << endl;
                    cout << endl;
                }
            } else if (input == "withdraw") {
                cout << endl;
                cout << endl;
                cout << setfill('_') << setw(50) << "";
                cout << endl;
                cout << endl;
                cout << remainingPlayers.at(indexPlayer)->getName() << " has withdrawn from the bid." << endl;
                numRemainingPlayers -= 1;
                cout << endl;
                cout << endl;
                checkWithdrew.at(indexPlayer) = true;
            } else {
                cout << endl;
                cout << endl;
                cout << setfill('_') << setw(50) << "";
                cout << endl;
                cout << endl;
                cout << "Please enter a valid bid." << endl;
                cout << endl;
                cout << endl;
                cin.clear();
                cin.ignore();
            }
        } else {
            if (indexPlayer == remainingPlayers.size() - 1) {
                indexPlayer = 0;
            } else {
                indexPlayer += 1;
            }
        }
    } while(numRemainingPlayers > 1);

    for (long unsigned int i = 0; i < remainingPlayers.size(); i++) {
        if (checkWithdrew[i] == false) {
            indexWinner = i;
            break;
        }
    }

    cout << "Congratulations " << remainingPlayers[indexWinner]->getName() << " you have won the bid!" << endl;
    remainingPlayers[indexWinner]->subMoney(minBid);
    remainingPlayers[indexWinner]->addProperty(buildingForSale);
    buildingForSale->setOwner(remainingPlayers[indexWinner]);
    buildingForSale->setIsOwned();

    
    // Check if the building is a residence, gym, academic building 
    if (checkTypeProperty(buildingForSale) == "Residences") {
        remainingPlayers[indexWinner]->setNumRes("increase"); // increase residences owned
    }
    else if (checkTypeProperty(buildingForSale) == "Gyms") {
        remainingPlayers[indexWinner]->setNumGyms("increase"); // increase gyms owned
    }
    else if (checkTypeProperty(buildingForSale) == "AcademicBuildings") {
        updateMonopolies(remainingPlayers[indexWinner], buildingForSale); // increase monopoly count
    }
}


void Board::buyImprovement(shared_ptr<Player> player, shared_ptr<AcademicBuildings> property) {
    int impCost = property->getImpCost();
    int playerBalance = player->getMoney() - impCost;

    if (!isMonopolyOwned(player, property)) { // Check if the player owns the whole monopoly 
        cout << "You do not own the whole monopoly, improvements cannot be made." << endl;
        return; 
    }

    if (playerBalance < 0) { // Check the player can afford improvement 
        cout << "Sorry you don't have enough money to buy this improvement." << endl;
        return;
    } 

    else if (property->getNumImp() == 5) { // Check if max improvements
        cout << "Maximum of 5 improvements on this building reached!" << endl;
        return;
    }

    else if (property->getNumImp() < 4) { // Build a bathroom
        cout << "Successfully built a bathroom in " << property->getName() << "!" << endl;
        property->setImprovement("buy");
        player->subMoney(impCost);
    }

    else if (property->getNumImp() == 4) { // Build a cafeteria 
        cout << "Successfully built a cafeteria in " << property->getName() << "!" << endl;
        property->setImprovement("buy");
        player->subMoney(impCost);
    }
}

void Board::sellImprovement(shared_ptr<Player> player, shared_ptr<AcademicBuildings> property) {
    // Check that there are improvements to sell
    if (property->getNumImp() == 0) {
        cout << "There are no improvements in this building to sell." << endl;
        return;
    }

    int impCost = property->getImpCost();
    int returnAmount = impCost / 2; // Sell for half the cost of the improvement
    cout << "Successfully sold an improvement in " << property->getName() << "!" << endl;
    property->setImprovement("sell");
    player->addMoney(returnAmount);
}

void Board::doTrade(string name, string give, string receive, shared_ptr<Player> curPlayer, shared_ptr<Player> otherPlayer) {
    shared_ptr<Buildings> propertyToTransfer = nullptr;
    shared_ptr<Buildings> propertyToTransfer1 = nullptr;
    shared_ptr<Buildings> propertyToTransfer2 = nullptr;

    stringstream giveSS;
    stringstream receiveSS;
    giveSS << give;
    receiveSS << receive;
    int giveInt;
    int receiveInt;
    if (giveSS >> giveInt) { // Trade money for property
        string propertyToTransferName = receive;
        for (unsigned int i = 0; i < getSquares().size(); i++) {
            if (propertyToTransferName == getSquares().at(i)->getName()) {
                propertyToTransfer = dynamic_pointer_cast<Buildings>(getSquares().at(i));
                
            }
        }

        curPlayer->addProperty(propertyToTransfer);
        propertyToTransfer->setOwner(curPlayer);
        curPlayer->subMoney(giveInt);
        otherPlayer->addMoney(giveInt);
        otherPlayer->removeProperty(propertyToTransfer);

        // Check if the building is a residence, gym, academic building 
        if (checkTypeProperty(propertyToTransfer) == "Residences") {
            curPlayer->setNumRes("increase"); // increase residences owned
            otherPlayer->setNumRes("decrease");
        }
        else if (checkTypeProperty(propertyToTransfer) == "Gyms") {
            curPlayer->setNumGyms("increase"); // increase gyms owned
            otherPlayer->setNumGyms("decrease");
        }
        else if (checkTypeProperty(propertyToTransfer) == "AcademicBuildings") {
            updateMonopolies(curPlayer, propertyToTransfer); // increase monopoly count
            decreaseMonopolies(otherPlayer, propertyToTransfer);
        }

        cout << "The trade was successful!" << endl;
        cout << propertyToTransfer->getName() << " is now owned by " << curPlayer->getName() << endl;
        cout << endl;
        cout << endl;
    } else {
        if (receiveSS >> receiveInt) { // Trade property for money
            string propertyToTransferName = give;

            for (unsigned int i = 0; i < getSquares().size(); i++) {
                if (propertyToTransferName == getSquares().at(i)->getName()) {
                    propertyToTransfer = dynamic_pointer_cast<Buildings>(getSquares().at(i));
                }
            }

            otherPlayer->addProperty(propertyToTransfer);
            propertyToTransfer->setOwner(otherPlayer);
            otherPlayer->subMoney(receiveInt);
            curPlayer->addMoney(receiveInt);
            curPlayer->removeProperty(propertyToTransfer);

            // Check if the building is a residence, gym, academic building 
            if (checkTypeProperty(propertyToTransfer) == "Residences") {
                otherPlayer->setNumRes("increase"); // increase residences owned
                curPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer) == "Gyms") {
                otherPlayer->setNumGyms("increase"); // increase gyms owned
                curPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer) == "AcademicBuildings") {
                updateMonopolies(otherPlayer, propertyToTransfer); // increase monopoly count
                decreaseMonopolies(curPlayer, propertyToTransfer);
            }
            cout << "The trade was successful!" << endl;
            cout << endl;
            cout << endl;
            cout << propertyToTransfer->getName() << " is now owned by " << otherPlayer->getName() << endl;
        } else { // Trade property for property
            string propertyToTransferName1 = give;
            string propertyToTransferName2 = receive;

            for (unsigned int i = 0; i < getSquares().size(); i++) {
                if (propertyToTransferName1 == getSquares().at(i)->getName()) {
                    propertyToTransfer1 = dynamic_pointer_cast<Buildings>(getSquares().at(i));
                }
                if (propertyToTransferName2 == getSquares().at(i)->getName()) {
                    propertyToTransfer2 = dynamic_pointer_cast<Buildings>(getSquares().at(i));
                }
            }

            otherPlayer->addProperty(propertyToTransfer1);
            curPlayer->addProperty(propertyToTransfer2);
            propertyToTransfer1->setOwner(otherPlayer);
            propertyToTransfer2->setOwner(curPlayer);
            otherPlayer->removeProperty(propertyToTransfer2);
            curPlayer->removeProperty(propertyToTransfer1);
            // Check if the building is a residence, gym, academic building 
            if (checkTypeProperty(propertyToTransfer2) == "Residences") {
                curPlayer->setNumRes("increase"); // increase residences owned
                otherPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer2) == "Gyms") {
                curPlayer->setNumGyms("increase"); // increase gyms owned
                otherPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer2) == "AcademicBuildings") {
                updateMonopolies(curPlayer, propertyToTransfer2); // increase monopoly count
                decreaseMonopolies(otherPlayer, propertyToTransfer2);
            }

            // Check if the building is a residence, gym, academic building 
            if (checkTypeProperty(propertyToTransfer1) == "Residences") {
                curPlayer->setNumRes("increase"); // increase residences owned
                otherPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer1) == "Gyms") {
                curPlayer->setNumGyms("increase"); // increase gyms owned
                otherPlayer->setNumRes("decrease");
            }
            else if (checkTypeProperty(propertyToTransfer1) == "AcademicBuildings") {
                updateMonopolies(curPlayer, propertyToTransfer1); // increase monopoly count
                decreaseMonopolies(otherPlayer, propertyToTransfer1);
            }

            cout << "The trade was successful!" << endl;
            cout << endl;
            cout << endl;
            cout << propertyToTransfer1->getName() << " is now owned by " << otherPlayer->getName() << endl;
            cout << propertyToTransfer2->getName() << " is now owned by " << curPlayer->getName() << endl;
            cout << endl;
            cout << endl;
        }
    }
}


vector<shared_ptr<Squares>> Board::getSquares() {
    return squares;
}

vector<shared_ptr<Buildings>> Board::getBuildings() {
    return buildings;
}

std::map<int, int> Board::getBuildingMap() {
    return buildingMap;
}

void Board::personalAssets(shared_ptr<Player> player) {

    cout << setfill('_') << setw(50) << "" << endl;
    cout << endl;
    cout << "List of " << player->getName() << "'s assets" << endl;
    cout << setfill('_') << setw(50) << "" << endl;
    cout << endl;
    cout << "Cash: " << player->getMoney() << endl;
    cout << endl;
    cout << "Roll Up The Rim Cups owned: " << player->getRollUpTheRimCup() << endl;
    cout << endl;
    cout << "Properties: " << endl;
    cout << endl;
    vector<shared_ptr<Buildings>> ownedBuildings = player->getProperties();

    for (unsigned int i = 0; i < ownedBuildings.size(); i++) {
        cout << "    " << ownedBuildings[i]->getName() << ": $" << ownedBuildings[i]->getCost() << endl;
        shared_ptr<AcademicBuildings> academicBuilding = dynamic_pointer_cast<AcademicBuildings> (ownedBuildings[i]);

        if (academicBuilding) {
            cout << "    " << "Number of Improvements: " << academicBuilding->getNumImp() <<endl;
            cout << endl;
        }
        else {
            cout << endl;
        }
    }
}


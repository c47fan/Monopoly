#include "game.h"
#include <string> 
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std; 

Game::Game(bool doubleRoll, int doubles, int rolls) : doubleRoll{doubleRoll}, doubles{doubles}, rolls{rolls} {}

Game::~Game() {
    for (int i = 0; i < players.size(); i++) {
        int size = players[i]->getProperties().size();

        
        for (int j = 0; j < size; j++) {
            
            players[i]->removeProperty(players[i]->getProperties()[0]);
        }
    }
}

void Game::addPlayer(shared_ptr<Player> newPlayer) { 
    players.emplace_back(newPlayer);
}

void Game::removePlayer(shared_ptr<Player> player) { // pass the player to be removed 
    players.erase(remove(players.begin(), players.end(), player), players.end());
}

void Game::nextPlayer() {
    if (curPlayer == players.size() - 1) {
        curPlayer = 0;
    }
    else {
        curPlayer++;
    }
    rolls = 0; // reset roll count
    doubles = 0; // reset doubles count
}

shared_ptr<Player> Game::getCurrentPlayer() const {
    return players[curPlayer];
}

void Game::setBoard(Board* b) {
    board = b; 
}

// Helper for initGame, prints pieces 
void printVec(vector<char> pieces) {
    for(auto it : pieces) {
        cout << " " << it;
    }
    cout << '\n';
}

// Helper for initGame, removes piece 
void removePiece(vector<char>& pieces, char piece) { 
    pieces.erase(remove(pieces.begin(), pieces.end(), piece), pieces.end());
}

// Helper for initGame, checks piece 
bool checkPiece(vector<char> pieces, char piece) {
    for(auto it : pieces) {
        if (it == piece) {
            return true;
        }
    }
    cout << "This piece is not available. Choose another." << endl;
    return false;
}


// Returns the player when given their name
shared_ptr<Player> Game::findPlayer(string name) const {
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i]->getName() == name) {
            shared_ptr<Player> player = players[i];
            return player;
        }
    }
}

void Game::loadGame(string fileName) {
    ifstream inFile(fileName.c_str());
    string line;

    int i = 0;
    int numPlayers = 0;

    while (getline(inFile, line)) {
        stringstream ss; // Initialize the ss

        // Get the number of players 
        if (i == 0) {
            numPlayers = stoi(line);
            cout << "Number of players: " << numPlayers << endl;
        }

        // If parsing through players 
        else if (i <= numPlayers) {

            // Variables to store the player values  
            string name;
            char piece; 
            int TimsCups;
            int money; 
            int position; 
            int numTurnsDC = 0;
            bool inDcLine = false;

            // Create string stream and parse the player line 
            string playerInfo;
            ss << line;
            int j = 0;

            while (ss >> playerInfo) { 
                if (j == 0) { // name 
                    name = playerInfo;
                    cout << name << " is using piece ";
                }
                else if (j == 1) { // piece
                    piece = playerInfo[0];
                    cout << piece << ". "; 
                }
                else if (j == 2) { // TimsCups
                    if (board->getTotalRollUpTheRimCups() + stoi(playerInfo) > 4) {
                        cout << "Surpassed maximum Tims Cups." << endl;
                        continue;
                    }
                    TimsCups = stoi(playerInfo);
                    board->addTotalRollUpTheRimCups(TimsCups);
                }
                else if (j == 3) { // money
                    money = stoi(playerInfo);
                }
                else if (j == 4) { // position
                    if (stoi(playerInfo) != 30 ) {
                        position = stoi(playerInfo);
                        cout << "Currently at " << board->getSquares()[position]->getName() << "." << endl;
                    }
                }
                else if (j == 5) { // inDcLine
                    if (stoi(playerInfo) == 1) {
                        inDcLine = true;
                    }
                }
                else if (j == 6) { // numTurnsDC
                    numTurnsDC = stoi(playerInfo);
                }
                j++;
            }
    
            shared_ptr<Player> newPlayer = make_shared<Player>(name, piece, TimsCups, money, position, numTurnsDC, inDcLine);
            addPlayer(newPlayer); // Add player to game
            board->getSquares()[position]->placePlayer(newPlayer); // Add the new player to the board
        }

        // If parsing through the buildings 
        else {
            // Create string stream and parse the building line
            string buildingInfo;
            ss << line;
            int j = 0;

            string name; 
            int improvements;
            shared_ptr<Player> owner;
            shared_ptr<Buildings> building;

            while (ss >> buildingInfo) {
                if (j == 0) { // building name
                    name = buildingInfo; 
                }

                else if (j == 1) { 
                    building = findBuilding(name);

                    if (buildingInfo != "BANK") {
                        owner = findPlayer(buildingInfo);// find owner 
                        building->setOwner(owner); // set owner 
                        building->setIsOwned(); // set owned bool 
                        owner->addProperty(building); // add property for owner 

                        // Check if the building is a residence, gym, or academic building 
                        if (board->checkTypeProperty(building) == "Residences") {
                            owner->setNumRes("increase"); // increase residences owned
                        }
                        else if (board->checkTypeProperty(building) == "Gyms") {
                            owner->setNumGyms("increase"); // increase gyms owned
                        }
                        else if (board->checkTypeProperty(building) == "AcademicBuildings") {
                            board->updateMonopolies(owner, building); // increase monopoly count
                        }
                    }
                }

                else if (j == 2) { // improvements 
                    if (stoi(buildingInfo) == -1) { // building is mortgaged 
                        building->setMortgaged(); 
                        continue;
                    }

                    shared_ptr<AcademicBuildings> academicBuilding = dynamic_pointer_cast<AcademicBuildings> (building);
            
                    if (academicBuilding && academicBuilding->getIsOwned()) { // if it is an owned academic building 
                        for (int n = 0; n < stoi(buildingInfo); n++) { // set the num imp
                            academicBuilding->setImprovement("buy");
                        }
                    }
                }
                j++;
            }
        }
        i++;
    }
}


void Game::initGame(bool testingOn, bool loadedGame, string fileName) {
    // Initalize using the saved game
    if (loadedGame) {
        loadGame(fileName);
    }

    // Initialize a new game 
    else if (!loadedGame) { 
        // Create players and pieces 
        vector<shared_ptr<Player>> p;
        players = p;
        
        vector<char> pieces = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};

        cout << "*** Welcome to Watopoly! ***" << endl;
        cout << "Enter the number of players (max 7):" << endl; 

        int numPlayers;

        // Accept input until number of players is valid 
        while (cin >> numPlayers) {
            if (cin.eof()) return;

            if (numPlayers <= 7 && numPlayers > 1) {
                break;
            }
            else {
                cout << "Invalid number of players. Re-enter:" << endl;
                cin.clear();
           
            }
        }

        // Input the player and pieces 
        cout << "List all players and their board pieces in the form <player> <piece>." << endl; 

        string name; 
        char piece; 

        for (int i = 0; i < numPlayers; i++) {
            if (cin.eof()) return;
            
            // Print the available pieces 
            cout << "Available pieces are:"; 
            printVec(pieces);
            
            cin >> name; 
            cin >> piece; 

            while (1) {
                bool badName = false;
                for (unsigned int i = 0; i < players.size(); i++) {
                    const string& playerName = players[i]->getName();
                    if (playerName == name) {
                        badName = true;
                    }
                }

                if (badName) {
                    cout << "Sorry that name is already taken. Please provide another name." << endl;
                    cin >> name;
                } else {
                    break;
                }
            }

            // Check if piece is available 
            if (!checkPiece(pieces, piece)) {
                i--;
                continue;
            }

            // Initialize new player and add to players 
            shared_ptr<Player> newPlayer = make_shared<Player>(name, piece);
            addPlayer(newPlayer); 

            // Add the new player to the board
            board->getSquares()[0]->placePlayer(newPlayer);

            // Remove the piece from available options 
            removePiece(pieces, piece);
        }
    }
    // Set the first player's turn
    curPlayer = 0;
}

void Game::printCommands() {
	cout << "------------------------------------------" << endl;
	cout << "roll" << endl;
	cout << "next" << endl;
	cout << "trade <name> <give> <receive>" << endl;
	cout << "improve <property> buy/sell" << endl;
    cout << "mortgage <property> buy/sell" << endl;
    cout << "unmortgage <property>" << endl;
    cout << "bankrupt" << endl; 
    cout << "assets" << endl; 
    cout << "all" << endl;
    cout << "save <filename>" << endl;
	cout << "------------------------------------------" << endl;
}

void Game::allCommand() {
    for (unsigned int i = 0; i < players.size(); i++) {
        board->personalAssets(players[i]);
        cout << setfill('_') << setw(50) << "" << endl;
        cout << endl;
    }
}

void Game::runGame(bool testingOn) {
    cout << "Starting game. Enter <c> for a list of commands." << endl;
    string command;
    // Read in values from input 
	while (cin >> command) {
        if (cin.eof()) {
            break;
        }

        
        else if (command == "c") { // c command
            printCommands(); 
        }

        else if (command == "roll") { // roll command
           if(!rollCommand(testingOn)) {
                if (gameOver()) { // check if game is over
                    break;
                }
                continue; // player cannot roll
           }

        }

        else if (command == "next") { // next command
           nextCommand();
           leaveDCLine();
        }

        else if (command == "trade") { // trade command
            tradeCommand();
        }

        else if (command == "improve") { // improve command 
            improveCommand();
        }
 
        else if (command == "mortgage") { // mortgage command
            mortgageCommand();
        }
 
        else if (command == "unmortgage") { // unmortgage command 
            unMortgageCommand();
        }

        else if (command == "bankrupt") { // bankrupt command 
            if (!(players[curPlayer]->getOwesMoney())) {
                cout << "You are not in debt currently. You cannot declare bankruptcy." << endl;
            }
        }

        else if (command == "assets") { // assets command
            if (!(players[curPlayer]->getPosition() == 4)) {
                board->personalAssets(players[curPlayer]);
            } else {
                cout << "You cannot use this command while on TUITION!" <<endl;
                continue;
            }
        }

        else if (command == "all") { // all command
            if (!(players[curPlayer]->getPosition() == 4)) {
                allCommand();
            } else {
                cout << "You cannot use this command while on TUITION!" <<endl;
                continue;
            }
        }
        
        else if (command == "save") { // save game
            cout << "Saving the current game." << endl;
            saveCommand();
        }

        else { // invalid command
            cout << "Invalid command. Retry or enter <c> for a list of commands." << endl; 
            cin.clear();
        }

        if (gameOver()) { // check if game is over
            break;
        }
    }
}

int Game::rollDice(bool testingOn) {
    int roll1; 
    int roll2; 
    // In testing mode 
    if (testingOn) {
        cin >> roll1; 
        cin >> roll2;
        cin.ignore(1000, '\n');
    }
    // In normal game
    else {
        srand(time(NULL)); // Seed random num generator with current time
        roll1 = rand() % 6 + 1;

        srand(roll1); // Seed random num generator with current time
        roll2 = rand() % 6 + 1; 
    }

    if (roll1 == roll2) { // Check if the roll was a double
        doubleRoll = true; 
       ++doubles;
    }
    else { // Reset double rolls 
        doubleRoll = false;
    }

    rolls++;
    int sum = roll1 + roll2;
    return sum; // return the sum of a random dice roll 
}

void Game::leaveDCLine() {
    // If the player is in DC Tim's Line
    if (players[curPlayer]->getDcTimsLine()) {
        string response = "no"; 
        cout << "You are in the DC Tim's line." << endl;
        if (players[curPlayer]->getRollUpTheRimCup() > 0) { // player has rollup the rim cup to use 
            cout << "You have " << players[curPlayer]->getRollUpTheRimCup() << " roll up the rim cups. Use one to get out of DC Tim's line? Enter 'yes' or 'no': " << endl;
            cin >> response; 

            if (response == "yes") {
                players[curPlayer]->useRollUpTheRimCup(); 
                board->subTotalRollUpTheRimCups();
                players[curPlayer]->setDcTimsLine(false);
                players[curPlayer]->setNumTurnsDC("reset");
                cout << "You have escaped the DC Tim's Line!" << endl;
            }
        }

        if (response == "no") { // ask player if they would like to pay $50 
            cout << "Pay $50 to escape the DC Tim's Line? Enter 'yes' or 'no': " << endl;
            cin >> response; 

            if (response == "yes") {

                if (players[curPlayer]->getMoney() < 50) {
                    cout << "You do not have enough funds to pay $50 to leave the DC Tim's Line!" << endl;
                    cout << "You will only leave if you roll a double." << endl;
                    cout << endl;

                } else {
                    players[curPlayer]->subMoney(50);
                    players[curPlayer]->setDcTimsLine(false);
                    players[curPlayer]->setNumTurnsDC("reset");
                    cout << "You have escaped the DC Tim's Line!" << endl;
                }
            }
        }

        if (response == "no") {
            cout << "You will only leave if you roll a double." << endl;
        }
    }
}


// Returns true if the player can move after this action
bool Game::rollCommand(bool testingOn) {
    if ((doubleRoll == false && rolls > 0) || doubles == 3) { // current player cannot roll again
        cout << "Cannot re-roll." << endl;
        return false;
    }

    // Calculate the amount of steps to move 
    int move = rollDice(testingOn);


    // Player escapes DC Tim's line
    if (doubleRoll) {
        cout << "It's a double!" << endl;

        if (players[curPlayer]->getDcTimsLine()) {
            players[curPlayer]->setDcTimsLine(false);
            players[curPlayer]->setNumTurnsDC("reset");
            cout << "You have escaped the DC Tim's Line!" << endl;
        }
    }

    // Player still in DC Tim's Line
    if (!doubleRoll & players[curPlayer]->getDcTimsLine()) {
        string response = "no";
        if (players[curPlayer]->getNumTurnsDC() == 2) { // Player must leave 
            cout << "You have spent 3 turns in the DC Tim's Line. The workers have asked you to leave!" << endl;

            if (players[curPlayer]->getRollUpTheRimCup() > 0) { // player has rollup the rim cup to use 
            cout << "You have " << players[curPlayer]->getRollUpTheRimCup() << " roll up the rim cups. Use one to get out of DC Tim's line, otherwise pay $50. Enter 'yes' or 'no': " << endl;
            cin >> response; 

                if (response == "yes") {
                    players[curPlayer]->useRollUpTheRimCup(); 
                    board->subTotalRollUpTheRimCups();
                    players[curPlayer]->setDcTimsLine(false);
                    players[curPlayer]->setNumTurnsDC("reset");
                    cout << "You have escaped the DC Tim's Line!" << endl;
                }
            }

            if (response == "no") {

                if (players[curPlayer]->getMoney() < 50) {
                    cout << "You do not have enough funds to pay $50 to leave the DC Tim's Line!" << endl;
                    // call owe money on them
                    players[curPlayer]->setOwesMoney(true);
                    players[curPlayer]->setAmountOwed(50);
                    bool didBankrupt = oweMoney(players[curPlayer], nullptr);
                    if (didBankrupt) { // since player got removed, players is one less now 
                        curPlayer--;
                        return false;
                    }

                } else {
                    cout << "You paid $50 to leave the DC Tim's Line." << endl;
                    players[curPlayer]->setDcTimsLine(false);
                    players[curPlayer]->setNumTurnsDC("reset");
                    players[curPlayer]->subMoney(50);
                }
            }

        }
        else {
            players[curPlayer]->setNumTurnsDC("add"); // player still stuck in dc tim's line
            cout << "You did not roll a double. Still stuck in DC Tim's line." << endl;
            return false;
        }
    }

    // Check if player rolled 3 doubles 
    if (doubles == 3) {
        move = board->findDistance(players[curPlayer], 10);
        board->movePlayer(players[curPlayer], move); // move to new square
        cout << players[curPlayer]->getName() << " goes to DC Tim's Line for rolling 3 doubles in a row." << endl;
        players[curPlayer]->setDcTimsLine(true);
        
        return false;
    }
    
    // Update the player's postion 
    board->getSquares()[players[curPlayer]->getPosition()]->removePlayer(players[curPlayer]); // remove from the square
    board->movePlayer(players[curPlayer], move); // move to new square


    cout << players[curPlayer]->getName() << " rolled a " << move;
    cout << " and moves to " << board->getSquares()[players[curPlayer]->getPosition()]->getName() << "!" << endl;
    cout << endl;
    
    // Player actions on the new square
    board->takeAction(players[curPlayer], board->getSquares()[players[curPlayer]->getPosition()], players);
    
    if (players[curPlayer]->getOwesMoney()) {
        // figure out if problem was with paying rent (hence owe money to a player)
        shared_ptr<Squares> onSquare = board->getSquares()[players[curPlayer]->getPosition()];
        shared_ptr<Player> owePlayer = nullptr;
        if (onSquare->getIsOwnable()) {
            shared_ptr<Buildings> onBuilding = dynamic_pointer_cast<Buildings>(onSquare);
            if (onBuilding->getIsOwned()) {
                owePlayer = onBuilding->getOwner();
            }
        }

        bool didBankrupt = oweMoney(players[curPlayer], owePlayer);
        if (didBankrupt) {
            curPlayer--; // since player got removed, players is one less now 
            return false;
        }
    }

    return true;
}

// Switches turn to the next player 
void Game::nextCommand() {
    if (doubleRoll && doubles < 3) { // Current player rolled a double, still their turn
        cout << "It is still " << players[curPlayer]->getName() << "'s turn." << endl;
    } else if (rolls == 0) {
        cout << players[curPlayer]->getName() << " still has to roll" << endl;
    } 

    else { // Move to next player's turn 
        nextPlayer();
        cout << players[curPlayer]->getName() << "'s turn." << endl;
    }
}

// Helper for improveCommand, checks if the property is owned by the player
bool checkPlayerProperties(shared_ptr<Player> player, string name) {
    for (unsigned int i = 0; i < player->getProperties().size(); i++) {
        if (player->getProperties()[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

// Returns the building when given its name
shared_ptr<Buildings> Game::findBuilding(string name) {
    for (unsigned int i = 0; i < board->getSquares().size(); i++) {
        if (board->getSquares()[i]->getName() == name) {
            int sqrPos = board->getSquares()[i]->getPosition();
            int buildingPos = board->getBuildingMap().find(sqrPos)->second;
            shared_ptr<Buildings> currBuilding = board->getBuildings()[buildingPos];
            return currBuilding;
        }
    }
}

void Game::improveCommand() {
    string property; 
    string action; 
    cin >> property; 
    cin >> action; 

    shared_ptr<AcademicBuildings> academicBuilding = dynamic_pointer_cast<AcademicBuildings> (findBuilding(property));

    // Check that the property is an academic building
    if (!academicBuilding) {
        cout << "Only academic buildings be improved." << endl;
        return;
    }

    // Check that the player owns the property
    else if (!checkPlayerProperties(players[curPlayer], property)) {
        cout << "You do not own " << property << "." << endl;
        return;
    }

    else if (action == "buy") { // buy an improvement
        board->buyImprovement(players[curPlayer], academicBuilding); 
    }
    
    else if (action == "sell") { // sell an improvement 
        board->sellImprovement(players[curPlayer], academicBuilding);
    }
}

bool Game::validTrade(string name, string give, string receive, shared_ptr<Player> otherPlayer) {

    // Check if the name is valid
    bool nameFound = false;
    for (unsigned int i = 0; i < players.size(); i++) {
        const string& playerName = players[i]->getName();
        if (playerName == name && name != players[curPlayer]->getName()) {
            nameFound = true;
            otherPlayer = players[i]; 
        } else if (name == players[curPlayer]->getName()) {
            cout << "Sorry you can't trade with yourself." << endl;
            return false;
        }
    }

    if (!nameFound) {
        cout << name << " is not a player. Please enter a valid name to trade with" << endl;
        return false;
    }

    // Check for "give" value being either cash or a propertty
    stringstream ss; 
    ss << give; 
    int n; 
    ss >> n; 

    if (ss) { // giving cash

        int giveCash = n;
        if (players[curPlayer]->getMoney() - giveCash < 0) {
            cout << players[curPlayer]->getName() << " , you don't have enough for this trade. Please try again" << endl;
            return false;
        }
        stringstream ssIntCheck;
        ssIntCheck << receive; 
        ssIntCheck >> n;
        if (ssIntCheck) { // receive cash
            cout << "Invalid trade. You can't trade money for money. Please try again" << endl;
            return false; 
        }
    } else { // giving property
        string property1 = give; 

        // Check if property1 Exists
        bool property1Found = false;
        shared_ptr<Buildings> property1Building = nullptr;

        for (unsigned int i = 0; i < (board->getSquares()).size(); i++) {
            if (property1 == board->getSquares().at(i)->getName()) {
                shared_ptr<Buildings> checkOwner = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));

                if (checkOwner) { // Check if the player owns this property
                    if (checkOwner->getOwner() != players[curPlayer]) {
                        cout << "The building you want to give is not owned by you" << endl;
                        return false;
                    } 
                }

                property1Found = true;
                shared_ptr<Buildings> isValidBuilding = checkOwner;
                if (isValidBuilding) {
                    property1Building = isValidBuilding;
                    break;
                }
            }
        }

        if (property1Found) {
            shared_ptr<AcademicBuildings> prop1AcaBuild = dynamic_pointer_cast<AcademicBuildings>(property1Building);
                // Check if property has improvements, if yes return false
            if (prop1AcaBuild) {
                if (prop1AcaBuild->getNumImp() > 0) {
                    cout << "There exists improvements in your \"give\" building." << endl;
                    cout << "Please sell the improvements and try again." << endl;
                    return false;
                }

                // Check if monopoly has improvements, if yes return false
                for (unsigned int i = 0; i < (board->getSquares().size()); i++) {
                    shared_ptr<AcademicBuildings> monopolyCheck = dynamic_pointer_cast<AcademicBuildings>(board->getSquares().at(i));
                    if (monopolyCheck) {
                        if (monopolyCheck->getMonopolyBlock() == prop1AcaBuild->getMonopolyBlock()) {
                            if (monopolyCheck->getNumImp() > 0) {
                                cout << "There exists improvements in the monopoly of your \"give\" building." << endl;
                                cout << "Please sell the improvements and try again." << endl;
                                return false;
                            }
                        }
                    }
                }
            }

            if (otherPlayer->getMoney() - property1Building->getCost()*0.6 < 0 && property1Building->getIsMortgaged()) {
                cout << otherPlayer->getName() << " can't afford to unmortgage the \"give\" property." << endl;
                return false;
            }

        } else {
            cout << "Sorry the \"give\" property you entered was not found. Please try again." << endl;
            return false;
        }
    }

    // Check if receive is either an int or a property
    stringstream ss2;
    int n2;
    ss2 << receive; 
    ss2 >> n2;
    bool property2Found = false;
    shared_ptr<Buildings> property2Building = nullptr;

    if (!ss2) { // receive is a property 
        string property2 = receive;
        // Check if property2 Exists
        for (unsigned int i = 0; i < (board->getSquares()).size(); i++) {
            if (property2 == board->getSquares().at(i)->getName()) {
                shared_ptr<Buildings> checkOwner2 = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));
                if (checkOwner2) { // Check if the player owns this property
                    if (checkOwner2->getOwner() != otherPlayer) {
                        cout << "The receiving player does not own the property you wish to trade for." << endl;
                        return false;
                    }
                }
                
                property2Building = checkOwner2;
                property2Found = true;
                // Check if the building is academic for later
                shared_ptr<Buildings> isValidAcademicBuilding = checkOwner2;
                if (isValidAcademicBuilding) {
                    property2Building = checkOwner2;
                    break;
                }
            }
        }

        if (property2Found) {
            // Check if building has any improvements
            shared_ptr<AcademicBuildings> prop2AcaBuild = dynamic_pointer_cast<AcademicBuildings>(property2Building);
            if (prop2AcaBuild) {
                if (prop2AcaBuild->getNumImp() > 0) {
                    cout << "There exists improvements in your \"receive\" building." << endl;
                    cout << "Please sell the improvements and try again." << endl;
                    return false;
                }
                // Check if monopoly has an improvements
                for (unsigned int i = 0; i < (board->getSquares().size()); i++) {
                    shared_ptr<AcademicBuildings> monopolyCheck = dynamic_pointer_cast<AcademicBuildings>(board->getSquares().at(i));
                    if (monopolyCheck) {
                        if (monopolyCheck->getMonopolyBlock() == prop2AcaBuild->getMonopolyBlock()) {
                            if (monopolyCheck->getNumImp() > 0) {
                                cout << "There exists buildings in the \"receive\" monopoly that have improvements." << endl;
                                cout << "Please sell the improvements and try again." << endl;
                                return false;
                            }
                        }
                    }
                }
            }

            if (players[curPlayer]->getMoney() - property2Building->getCost()*0.6 < 0 && property2Building->getIsMortgaged()) {
                cout << players[curPlayer]->getName() << " can't afford to unmortgage the \"receive\" property." << endl;
                return false;
            }

        } else {
            cout << "Sorry the \"receive\" property you entered was not found. Please try again." << endl;
            return false;
        }

    } else { // receive is an int
        int receiveCash = n2;
        if (otherPlayer->getMoney() - receiveCash < 0) {
            cout << otherPlayer->getName() << " does not have enough money for this trade. Please try again." << endl;
            return false;
        }
    }

    cout << name << " please enter \"accept\" or \"reject\":" << endl;
    string response;
    while (1) {
        cin >> response;
        if (response == "reject") {
            cout << "Trade rejected." << endl;
            return false;
        } else if (response == "accept") {
            break;
        } else {
            cout << "Please enter either \"accept\" or \"reject\":" << endl;
        }
    }
    
    return true;
}

void Game::tradeCommand() {
    string name;
    string give;
    string receive;

    cin >> name; 
    cin >> give;
    cin >> receive; 
    // It is a valid trade
    shared_ptr<Player> otherPlayer = nullptr;

    if (validTrade(name, give, receive, otherPlayer)) {
        for (int i = 0; i < players.size(); i++) {
            if (name == players.at(i)->getName()) {
                otherPlayer = players.at(i);
            }
        }
        board->doTrade(name, give, receive, players[curPlayer], otherPlayer);
    }
}

bool Game::validMortgageCheck(string propertyName) {
    shared_ptr<Buildings> theProperty = nullptr;

    // Check the property is owned by the player
    for (unsigned int i = 0; i < board->getSquares().size(); i++) {
        if (propertyName == board->getSquares().at(i)->getName()) {
            theProperty = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));

            if (theProperty) { // Check if the player owns this property
                if (theProperty->getOwner() != players[curPlayer]) {
                    cout << "You can't mortgage a building you don't own." << endl;
                    return false;
                } 
            }
        }
    }

    if (theProperty == nullptr) {
        cout << "The property does not exist." << endl;
        return false;
    }

    // Check if the property is mortgagable
    if (theProperty->getIsMortgaged()) {
        cout << "This building is already mortgaged." << endl;
        return false;
    }

    // Check if the property has any improvements
    shared_ptr<AcademicBuildings>theAcademicProperty = dynamic_pointer_cast<AcademicBuildings>(theProperty);
    if (theAcademicProperty) {
        if (theAcademicProperty->getNumImp() > 0) {
            cout << theProperty->getName() << " has improvements. Please sell all improvements to mortgage this property." << endl;
            return false;
        }
    }
    

    return true;
}

bool Game::validUnMortgageCheck(string propertyName) {
    shared_ptr<Buildings> theProperty = nullptr;

    // Check the property is owned by the player
    for (unsigned int i = 0; i < board->getSquares().size(); i++) {
        if (propertyName == board->getSquares().at(i)->getName()) {
            theProperty = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));

            if (theProperty) { // Check if the player owns this property
                if (theProperty->getOwner() != players[curPlayer]) {
                    cout << "You can't unmortgage a building you don't own" << endl;
                    return false;
                } 
            }
        }
    }

    // Property does not exist
    if (theProperty == nullptr) {
        cout << "The property does not exist." << endl;
        return false;
    }

    // Check if the property is mortgagable
    if (!theProperty->getIsMortgaged()) {
        cout << "This building is already unmortgaged." << endl;
        return false;
    }

    // Not enough money to unmortgage building
    if (players[curPlayer]->getMoney() - (theProperty->getCost() * 0.6) < 0) {
        cout << "You don't have enough money to unmortgage this building." << endl;
        return false;
    }

    return true;
}

void Game::mortgageCommand() {
    string propertyName; 
    cin >> propertyName; 

    shared_ptr<Buildings>property = nullptr;
    if (validMortgageCheck(propertyName)) {
        for (unsigned int i = 0; i < board->getSquares().size(); i++) {
            if (propertyName == board->getSquares().at(i)->getName()) {
                property = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));
                break;
            }
        }

        cout << players[curPlayer]->getName() << " will receive $" << property->getCost() / 2 << " for mortgaging the property" << endl;
        players[curPlayer]->addMoney(property->getCost() / 2);
        property->setMortgaged();
    }
}

void Game::unMortgageCommand() {
    string propertyName; 
    cin >> propertyName;
    shared_ptr<Buildings>property = nullptr;
    
    if (validUnMortgageCheck(propertyName)) {
        for (unsigned int i = 0; i < board->getSquares().size(); i++) {
            if (propertyName == board->getSquares().at(i)->getName()) {
                property = dynamic_pointer_cast<Buildings>(board->getSquares().at(i));
                break;
            }
        }

        cout << players[curPlayer]->getName() << " will pay $" << property->getCost() / 2 << " + $" << property->getCost() * 0.1 <<"( +10\% of the cost)." << endl;
        players[curPlayer]->subMoney(property->getCost() *0.6);
        property->setUnMortgage();
    }
}

// raise money or declare banckrupty if player owes money
bool Game::oweMoney(shared_ptr<Player> player, shared_ptr<Player> owePlayer) {
    int oweAmount = player->getAmountOwed();
    int playerBalance = player->getMoney();

    if (owePlayer) {
        cout << "You owe " << owePlayer->getName() << " $" << oweAmount << ". " ;
        cout << "You only have $" << playerBalance<< " in savings" << endl;
        cout << endl;
    } else {
        cout << "You owe the Bank $" << oweAmount << ". " ;
        cout << "You only have $" << playerBalance << " in savings" << endl;
    }

    cout << "You have the option to either drop out by declaring bankruptcy "
         << "or attemp to trade, sell improvements, and mortgage your properties " 
         << "to gather the required money" << endl;
    cout << "You can enter <c> for a list of commands." << endl;
    
    while (oweAmount > player->getMoney()) {
        // give player option to improve/mortage and trade
        string choice;
        cin >> choice;
        if (choice == "bankrupt") {
            declareBankruptcy(player, owePlayer);
            return true;
        } else if (choice == "trade") {
            tradeCommand();
            cout << endl;
        } else if (choice == "improve") {
            improveCommand();            
            cout << endl;         
        } else if (choice == "mortgage") {
            mortgageCommand();
            cout << endl;
        } else if (choice == "assets") { // assets command
            // add check if player is on tuition squarea
            if (!(player->getPosition() == 4)) {
                board->personalAssets(players[curPlayer]);
            } else {
                cout << "You cannot use this command while on TUITION!" <<endl;
                continue;
            }
        } else if (choice == "all") { // all command
            // add check is player is on tuition square
            if (!(player->getPosition() == 4)) {
                allCommand();
            } else {
                cout << "You cannot use this command while on TUITION!" <<endl;
                continue;
            }
        } else if (choice == "c") {
            printCommands();
        } else {
            cout << "Invalid choice. Please choose the appropriate command." << endl;
            continue;
        }
    }

    // once break out of loop , tell them they have enough money to pay the debt
    cout << endl;
    cout << "You now have enough funds to pay the amount you owe!" << endl;
    player->subMoney(oweAmount);
    player->setOwesMoney(false);
    player->setAmountOwed(0);
    if (owePlayer) {
        owePlayer->addMoney(oweAmount);
    }
    return false;
}

bool Game::declareBankruptcy(shared_ptr<Player> player, shared_ptr<Player> owePlayer) {
    if (player->getMoney() >= player->getAmountOwed()) {
        cout << "You have enough money to pay your debt. You cannot declare bankruptcy." << endl;
        return false;
    } else {
        player->declareBankruptcy(); // add statement that says player is now bankrupt
        // get owned buildings
        vector<shared_ptr<Buildings>> propertiesOwned = player->getProperties();
        // get necessary player info
        string playerName = player->getName();
        int playerMoney = player->getMoney();
        int playerCups = player->getRollUpTheRimCup();

        // clear the player's properties 
        int size = player->getProperties().size();
        for (int i = 0; i < size; i++) {
            player->removeProperty(player->getProperties()[0]);
        }

        // delete cups, update total in board
        for (int i = 0; i < playerCups; ++i) board->subTotalRollUpTheRimCups();

        board->getSquares()[players[curPlayer]->getPosition()]->removePlayer(players[curPlayer]); // remove from the square
        removePlayer(player); // remove player
    

        if (players.size() == 1) return true; // only one player left, game is over 
        
        if (owePlayer) {
            cout << owePlayer->getName() << " will now receive all of " << playerName << "'s assets." << endl;
            cout << endl;
            cout << endl;
            
            if (playerMoney) owePlayer->addMoney(playerMoney); // recieve money
            if (playerCups) {
                cout << owePlayer->getName() << " receives " << playerCups << " Roll Up The Rim Cup(s)" << endl;
                owePlayer->addRollUpTheRimCup(playerCups); // get cups
                cout << endl;
            }

            // give the properties
            for (const auto& property : propertiesOwned) {
                cout << owePlayer->getName() << " is receiving " << property->getName() << "." << endl;
                cout << endl;

                // if property is mortgaged, follow procedure
                if (property->getIsMortgaged()) {
                    cout << property->getName() << " is mortgaged. You must pay 10 percent of the building cost to receive it." << endl;
                    int payCost = property->getCost() / 10;
                    
                    // pay amount to recieve property
                    if (owePlayer->getMoney() < payCost) {
                        cout << "You do not have enough funds to pay 10 percent of the building cost!" << endl;
                        cout << "You do not receive the building. It is returned to open market." << endl;
                        // return building
                        if (board->checkTypeProperty(property) == "AcademicBuildings") {
                            shared_ptr<AcademicBuildings> academic = dynamic_pointer_cast<AcademicBuildings>(property);
                            for (int i = 0; i < academic->getNumImp(); ++i) academic->setImprovement("sell");
                        }
                        board->auction(property, players);      
                        cout << endl;
                    } else {
                        owePlayer->subMoney(payCost);
                        cout << "You can choose to unmortgage the building NOW by paying 50 percent of the cost" << endl;
                        cout << "Or leave the building mortgaged but pay 60 percent of the cost when unmortaging LATER." << endl; 
                        cout << "Enter 1 to unmortgage now, 2 to leave it mortgaged: ";
                        int choice;
                        cin >> choice;
                        if (choice == 1) {
                            int unmortgageCost = property->getCost() / 2;
                            if (owePlayer->getMoney() < unmortgageCost) {
                                cout << "You do not have enough funds to unmortgage the building now!" << endl;
                            } else {
                                owePlayer->subMoney(unmortgageCost);
                                property->setUnMortgage();
                            }
                        }
                        cout << endl;
                    }
                }

                property->setOwner(owePlayer);
                // Check if the building is a residence, gym, academic building 
                if (board->checkTypeProperty(property) == "Residences") {
                    owePlayer->setNumRes("increase"); // increase residences owned
                }
                else if (board->checkTypeProperty(property) == "Gyms") {
                    owePlayer->setNumGyms("increase"); // increase gyms owned
                }
                else if (board->checkTypeProperty(property) == "AcademicBuildings") {
                    board->updateMonopolies(owePlayer, property); // increase monopoly count
                }
                owePlayer->addProperty(property); // improvements get transferred automatically
            }

        } else {
            // owes to bank

            if (!propertiesOwned.empty()) cout << playerName << "'s properties are now returned to the open market." << endl;
            
            // buildings they owe are auctioned (remove all improvements before doing that)
            for (const auto& property : propertiesOwned) {
                if (board->checkTypeProperty(property) == "AcademicBuildings") {
                    shared_ptr<AcademicBuildings> academic = dynamic_pointer_cast<AcademicBuildings>(property);
                    for (int i = 0; i < academic->getNumImp(); ++i) academic->setImprovement("sell");
                }
                board->auction(property, players);
                cout << endl;
            }
        }
    }

    board->notifyObservers();
    return true;
}

// Checks if game is over 
bool Game::gameOver() {
    if (players.size() == 1) { // there is one player left 
        cout << "*** GAME OVER : " << players[0]->getName() << " IS THE WINNER ***" << endl;
        return true; 
    }
    return false; 
}

// Saves the current state of the game
void Game::saveCommand() {
    string filename; 
    cin >> filename; 

    ofstream outFile(filename.c_str());
    string line;

    int i = 0;
    int numPlayers;

    int b = 0;

    while (1) {
        // Insert number of players 
        if (i == 0) {
            numPlayers = players.size();
            line = to_string(players.size());
            outFile << line << endl;
        }

        // Insert the players 
        else if (i <= numPlayers) {
            // For each player, add their information
            line = players[i - 1]->getName(); // name

            line = line + " " + players[i - 1]->getSymbol(); // piece

            line = line + " " + to_string(players[i - 1]->getRollUpTheRimCup()); // num cups 

            line = line + " " + to_string(players[i - 1]->getMoney());  // money 

            line = line + " " + to_string(players[i - 1]->getPosition());  // position 

            if (players[i - 1]->getPosition() == 10) { // in DC line
                if (players[i - 1]->getDcTimsLine() == true) {
                    line = line + " " + "1";
                }
                else if (players[i - 1]->getDcTimsLine() == false) {
                    line = line + " " + "0";
                }
            }

            if (players[i - 1]->getDcTimsLine() == true) { // number of turns in the DC line
                line = line + " " + to_string(players[i - 1]->getNumTurnsDC()); 
            }

            outFile << line << endl;
        }

        // Insert the buildings
        else {
            if (b == 28) {
                break; // looped through all the buildings already 
            }

            line = board->getBuildings()[b]->getName(); // name of building

            if (board->getBuildings()[b]->getIsOwned()) {
                line = line + " " + board->getBuildings()[b]->getOwner()->getName(); // name of owner
            }
            else {
                line = line + " " + "BANK"; // not owned
            }

            if (board->getBuildings()[b]->getIsMortgaged()) { // building is mortgaged
                line = line + " " + "-1"; // set to -1
                continue;
            } 

            shared_ptr<AcademicBuildings> academicBuilding = dynamic_pointer_cast<AcademicBuildings> (board->getBuildings()[b]);
            if (academicBuilding) { // building is not mortgaged and is an academic building 
                line = line + " " + to_string(academicBuilding->getNumImp());
            }
            else { // building is not mortgaged and is a residence or gym
                line = line + " " + "0";
            }

            outFile << line << endl;

            b++;
        }
        i++;
    }
}


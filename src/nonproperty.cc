#include "nonproperty.h"
#include <string>
#include "board.h"

using namespace std;

NonProperty::NonProperty(int position, string name) : Squares{position, name} {}

void NonProperty::action(string name, shared_ptr<Player> player, Board* board) {

    if (name == "Collect OSAP") {
        collectOSAP(player);
    } else if (name == "DC Tims Line") {
        dcTimsLine(player, board);
    } else if (name == "Go To Tims") {
        goToTims(player, board);
    } else if (name == "Goose Nesting") {
        gooseNesting(player);
    } else if (name == "TUITION") {
        tuition(player);
    } else if (name == "COOP FEE") {
        coopFee(player);
    } else if (name == "SLC") {
        slc(player, board);
    } else if (name == "NEEDLES HALL") {
        needlesHall(player, board);
    }
}

void NonProperty::collectOSAP(shared_ptr<Player> player) {
    player->addMoney(200);
}

void NonProperty::dcTimsLine(shared_ptr<Player> player, Board* board) {
    if (player->getDcTimsLine() == false) { // player landed on the square
        cout << player->getName() << " is just visiting DC Tim's Line" << endl;
    } 
}

void NonProperty::goToTims(shared_ptr<Player> player, Board* board) {

    cout << "You will now be sent to DC Tim's Line!" << endl;
    cout << endl;
    board->getSquares()[player->getPosition()]->removePlayer(player);
    board->movePlayer(player, board->findDistance(player, 10));
    board->setMovedAgain(true);
    // set player feild dc tims line
    player->setDcTimsLine(true);
    
}

void NonProperty::gooseNesting(shared_ptr<Player> player) {
    cout << "You are being attacked by a flock of geese!! RUN!!!" << endl;
}

void NonProperty::tuition(shared_ptr<Player> player) {
    int playerWorth = 0;
    playerWorth += player->getMoney(); // player savings

    vector<shared_ptr<Buildings>> owned = player->getProperties();
    for (const auto& ptr : owned) {
        playerWorth += ptr->getCost(); //player owned buildings cost
        shared_ptr<AcademicBuildings> academic = dynamic_pointer_cast<AcademicBuildings>(ptr);
        if (academic) {
            playerWorth += (academic->getImpCost() * academic->getNumImp());
        }
    }

    cout << "Please choose between paying $300 tuition (1) or 10 percent of your total worth (2)." << endl;
    cout << "1. Pay $300." << endl;
    cout << "2. Pay 10 percent of yout total worth" << endl;
    cout << "Total worth is $" << playerWorth << "." << endl;
    string command;
    while (cin >> command) {
        if (command == "1") {
            if (player->getMoney() < 300) {
                cout << "You do not have enough funds to pay $300 tuition" << endl;
                player->setOwesMoney(true);
                player->setAmountOwed(300);
            } else {
                player->subMoney(300);
                cout << "Thank you for paying tuition!" << endl;
            }
            break;
        } else if (command == "2") {
            int percent = playerWorth / 10;
            if (player->getMoney() < percent) {
                cout << "You do not have enough funds to pay 10 percent of your total worth" << endl;
                player->setOwesMoney(true);
                player->setAmountOwed(percent);
            } else {
                player->subMoney(percent);
                cout << "Thank you for paying!" << endl;
            }
            break;
        } else {
            cout << "Invalid choice. Please enter 1 to Pay $300 or 2 to Pay 10 percent of yout total worth" << endl; 
            cin.clear();
            cin.ignore();
        }
    }

}


void NonProperty::coopFee(shared_ptr<Player> player) {
    if (player->getMoney() < 150) {
        cout << "You do not have enough funds to pay $150 Coop Fee" << endl;
        player->setOwesMoney(true);
        player->setAmountOwed(150);
    } else {
        cout << "You will pay $150 Coop Fee" << endl;
        player->subMoney(150);
    }
}

void NonProperty::slc(shared_ptr<Player> player, Board* board) {
    srand(time(NULL)); // Seed random num generator with current time
    int random_move;
    random_move = rand()%100 + 1;
     
    if (random_move == 1) {
        if (board->getTotalRollUpTheRimCups() < 4) {
            cout << "Congratuations! You won a Roll up the Rim Cup!" << endl;
            board->addTotalRollUpTheRimCups(1);
            player->addRollUpTheRimCup(1);
            return;
        }
    }
    
    random_move = rand()%24 + 1;

    if (random_move >= 1 && random_move <= 3) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, -3);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved back 3 steps. You are moved to " << onSquare->getName() << "." << endl;
        board->setMovedAgain(true);

    } else if (random_move >= 4 && random_move <= 7) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, -2);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved back 2 steps. You are moved to " << onSquare->getName() << endl;
        if (!(player->getPosition() == 0)) board->setMovedAgain(true);

    } else if (random_move >= 8 && random_move <= 11) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, -1);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved back 1 steps. You are moved to " << onSquare->getName() << endl;
        board->setMovedAgain(true);
        
    } else if (random_move >=12 && random_move <= 14) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, 1);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved forward 1 steps. You are moved to " << onSquare->getName() << endl;
        board->setMovedAgain(true);
        
    } else if (random_move >= 15 && random_move <= 18) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, 2);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved forward 2 steps. You are moved to " << onSquare->getName() << endl;
        board->setMovedAgain(true);
        
    } else if (random_move >= 19 && random_move <= 22) {
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, 3);
        shared_ptr<Squares> onSquare = board->getSquares()[player->getPosition()];
        cout << "You moved forward 3 steps. You are moved to " << onSquare->getName() << endl;
        board->setMovedAgain(true);
        
    } else if (random_move == 23) {
        // moving to dc tims line, set player feild to true
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, board->findDistance(player, 10));
        cout << "You moved to DC Tims Line." << endl;
        board->setMovedAgain(true);
        // set player feild dc tims line
        player->setDcTimsLine(true);

    } else {
        // moving to osap
        board->getSquares()[player->getPosition()]->removePlayer(player);
        board->movePlayer(player, board->findDistance(player, 0));
        cout << "You moved to Collect OSAP." << endl;
        board->setMovedAgain(true);
    }
}

void NonProperty::needlesHall(shared_ptr<Player> player, Board* board) {
    srand(time(NULL)); // Seed random num generator with current time
    int random_move;
    random_move = rand()%100 + 1;

    if (random_move == 1) {
        if (board->getTotalRollUpTheRimCups() < 4) {
            cout << "Congratuations! You won a Roll up the Rim Cup!" << endl;
            board->addTotalRollUpTheRimCups(1);
            player->addRollUpTheRimCup(1);
            return;
        }
    }

    random_move = rand()%18 + 1;

    if (random_move <= 1) {
        cout << "You will loose $200." << endl;
        if (player->getMoney() < 200) {
                cout << "You do not have enough funds!" << endl;
                player->setOwesMoney(true);
                player->setAmountOwed(200);
            } else {
                player->subMoney(200);
            }
    } else if (random_move >= 2 && random_move <=3) {
        cout << "You will loose $100." << endl;
        if (player->getMoney() < 100) {
                cout << "You do not have enough funds!" << endl;
                player->setOwesMoney(true);
                player->setAmountOwed(100);
            } else {
                player->subMoney(100);
            }
    } else if (random_move >=4 && random_move <=6) {
        cout << "You will loose $50." << endl;
        if (player->getMoney() < 50) {
                cout << "You do not have enough funds!" << endl;
                player->setOwesMoney(true);
                player->setAmountOwed(50);
            } else {
                player->subMoney(50);
            }
    } else if (random_move >= 7 && random_move <=12) {
        cout << "You will gain $20." << endl;
        player->addMoney(20);
    } else if (random_move >= 13 && random_move <= 15) {
        cout << "You will gain $50." << endl;
        player->addMoney(50);
    } else if (random_move >= 16 && random_move <=17) {
        cout << "You will gain $100." << endl;
        player->addMoney(100);
    } else {
        cout << "You will gain $200." << endl;
        player->addMoney(200);
    }
}

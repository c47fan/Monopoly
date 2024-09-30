#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include "boardDisplay.h"

using namespace std;

BoardDisplay::BoardDisplay(Board* board) : board{board} { board->attach(this); }

void BoardDisplay::drawPlayers(int location, vector<shared_ptr<Squares>> currentSquare) {
    int fill = 0;
    vector<char> playersOnSquare = currentSquare.at(location)->hasPlayers();
    for (unsigned int i = 0 ; i < playersOnSquare.size(); i++) {
        cout << playersOnSquare[i];
        fill += 1;
    }
    // cout << "git";
    for (int i = fill; i < 7; ++i) {
        cout << " ";
        fill += 1;
    }
}

void BoardDisplay::drawProperty(int position, vector<shared_ptr<Squares>> square) {
    int numOfImprovements = dynamic_pointer_cast<AcademicBuildings>(square[position])->getNumImp();
    for (int i = 0; i < 7; ++i) {
        if (i < numOfImprovements) {
            cout << "I";
        } else {
            cout << "-";
        }
    }
}

void BoardDisplay::drawBoard() {
    // Line 1
    cout << "_________________________________________________________________________________________" << endl;
    
    // Line 2
    cout << "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |" << endl;
    
    // Line 3
    cout << "|Nesting|";
    // EV1 Property
    drawProperty(21, board->getSquares());
    cout << "|HALL   |";
    // EV2 Property
    drawProperty(23, board->getSquares());
    cout << "|";
    // EV3
    drawProperty(24, board->getSquares());
    cout << "|       |";
    // PHYS Property
    drawProperty(26, board->getSquares());
    cout << "|";
    // B1 Property
    drawProperty(27, board->getSquares());
    cout << "|       |";
    // B2 Property
    drawProperty(29, board->getSquares());
    cout << "|TIMS   |" << endl;
    
    // Line 4
    cout << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << endl;

    // Line 5: Print the (possible) players into their spots
    for (int i = 20; i < 31; ++i) {
        cout << "|";
        drawPlayers(i, board->getSquares());
    }
    cout << "|" << endl;

    // Line 6
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;

    // Line 7
    cout << "|       |                                                                       |       |" << endl;

    // Line 8
    cout << "|";
    // OPT property
    drawProperty(19, board->getSquares());
    cout << "|                                                                       |";
    // EIT Property
    drawProperty(31, board->getSquares());
    cout << "|" << endl;

    // Line 9
    cout << "|OPT    |                                                                       |EIT    |" << endl;

    // Line 10
    cout << "|";
    // OPT Players
    drawPlayers(19, board->getSquares());
    cout << "|                                                                       |";
    // EIT Players
    drawPlayers(31, board->getSquares());
    cout << "|" << endl;

    // Line 11
    cout << "|_______|                                                                       |_______|" << endl;
    // Line 12
    cout << "|       |                                                                       |       |" << endl;

    // Line 13
    cout << "|";
    // BMH Property
    drawProperty(13, board->getSquares());
    cout << "|                                                                       |";
    // ESC Property
    drawProperty(32, board->getSquares());
    cout << "|" << endl;

    // Line 14
    cout << "|BMH    |                                                                       |ESC    |" << endl;

    // Line 15
    cout << "|";
    // BMH Players
    drawPlayers(18, board->getSquares());
    cout << "|                                                                       |";
    // ESC Players
    drawPlayers(32, board->getSquares());
    cout << "|" << endl;
    
    // Line 16
    cout << "|_______|                                                                       |_______|" << endl;

    // Line 17
    cout << "|SLC    |                                                                       |SLC    |" << endl;

    // Line 18
    cout << "|";
    // SLC_1 Players
    drawPlayers(17, board->getSquares());
    cout << "|                                                                       |";
    // SLC_2 Players
    drawPlayers(33, board->getSquares());
    cout << "|" << endl;

    // Line 19
    cout << "|       |                                                                       |       |" << endl;
    // Line 20
    cout << "|       |                                                                       |       |" << endl;
    // Line 21
    cout << "|_______|                                                                       |_______|" << endl;
    // Line 22
    cout << "|       |                                                                       |       |" << endl;
    
    // Line 23
    cout << "|";
    // LHI Property
    drawProperty(16, board->getSquares());
    cout << "|                                                                       |";
    // C2 Property
    drawProperty(34, board->getSquares());
    cout << "|" << endl;

    // Line 24
    cout << "|LHI    |                                                                       |C2     |" << endl;
    
    // Line 25
    cout << "|";
    // LHI Players
    drawPlayers(16, board->getSquares());
    cout << "|             _____________________________________________             |";
    // C2 Players
    drawPlayers(34, board->getSquares());
    cout << "|" << endl;

    // Line 26
    cout << "|_______|            |                                             |            |_______|" << endl;

    // Line 27
    cout << "|UWP    |            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV    |" << endl;

    // Line 28
    cout << "|";
    // UWP Players
    drawPlayers(15, board->getSquares());
    cout << "|            | #   # #  #   #   #   # #  # #   # #   #   # |            |";
    // REV Players
    drawPlayers(35, board->getSquares());
    cout << "|" << endl;

    // Line 29
    cout << "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |" << endl;

    // Line 30
    cout << "|       |            | # # # #  #   #   #   # #    #   # #     #   |            |       |" << endl;

    // Line 31
    cout << "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|" << endl;

    // Line 32
    cout << "|       |            |_____________________________________________|            |NEEDLES|" << endl;

    // Line 33
    cout << "|";
    // CPH Property
    drawProperty(14, board->getSquares());
    cout << "|                                                                       |HALL   |" << endl;

    // Line 34
    cout << "|CPH    |                                                                       |";
    // NeedlesHall_3 Players
    drawPlayers(36, board->getSquares());
    cout << "|" << endl;

    // Line 35
    cout << "|";
    // CPH Players
    drawPlayers(14, board->getSquares());
    cout << "|                                                                       |       |" << endl;
    
    // Line 36
    cout << "|_______|                                                                       |_______|" << endl;

    // Line 37
    cout << "|       |                                                                       |       |" << endl;

    // Line 38
    cout << "|";
    // DWE Property
    drawProperty(13, board->getSquares());
    cout << "|                                                                       |";
    // MC Property
    drawProperty(37, board->getSquares());
    cout << "|" << endl;

    // Line 39
    cout << "|DWE    |                                                                       |MC     |" << endl;

    // Line 40
    cout << "|";
    // DWE Players
    drawPlayers(13, board->getSquares());
    cout << "|                                                                       |";
    // MC Players
    drawPlayers(37, board->getSquares());
    cout << "|" << endl;

    // Line 41
    cout << "|_______|                                                                       |_______|" << endl;;

    // Line 42
    cout << "|PAC    |                                                                       |COOP   |" << endl;

    // Line 43
    // PAC Players
    cout << "|";
    drawPlayers(12, board->getSquares());
    cout  << "|                                                                       |FEE    |" << endl;

    // Line 44
    cout << "|       |                                                                       |";
    drawPlayers(38, board->getSquares());
    cout << "|" << endl;

    // Line 45
    cout << "|       |                                                                       |       |" << endl;

    // Line 46
    cout << "|_______|                                                                       |_______|" << endl;

    // Line 47
    cout << "|       |                                                                       |       |" << endl;

    // Line 48
    cout << "|";
    // RCH Property
    drawProperty(11, board->getSquares());
    cout << "|                                                                       |";
    // DC Property
    drawProperty(39, board->getSquares());
    cout << "|" << endl;;
    
    // Line 49
    cout << "|RCH    |                                                                       |DC     |" << endl;

    // Line 50
    cout << "|";
    // RCH Players
    drawPlayers(11, board->getSquares());
    cout << "|                                                                       |";
    // DC Players
    drawPlayers(39, board->getSquares());
    cout << "|" << endl;

    // Line 51
    cout << "|_______|_______________________________________________________________________|_______|" << endl;

    // Line 52
    cout << "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|" << endl;

    // Line 53
    cout << "|Line   |";
    // HH Property
    drawProperty(9, board->getSquares());
    cout << "|";
    // PAS Property
    drawProperty(8, board->getSquares());
    cout << "|HALL   |";
    // ECH Property
    drawProperty(6, board->getSquares());
    cout << "|       |       |";
    // ML Property
    drawProperty(3, board->getSquares());
    cout << "|       |";
    drawProperty(1, board->getSquares());
    cout << "|OSAP   |" << endl;
    // Line 54
    cout << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |";
    drawPlayers(0, board->getSquares());
    cout << "|" << endl;
    // Line 55
    for (int i = 10; i >= 1; --i) {
        cout << "|";
        drawPlayers(i, board->getSquares());
    }
    cout << "|       |" << endl;
    
    // 56
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << endl;
}

void BoardDisplay::notify() {
    drawBoard();
}

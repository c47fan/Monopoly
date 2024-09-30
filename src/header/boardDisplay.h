#ifndef __BOARDDISPLAY_H__
#define __BOARDDISPLAY_H__

#include "observer.h"
#include "board.h"
#include "player.h"
#include "squares.h"
#include <memory>

class BoardDisplay : public Observer {
    private:
        Board* board;
        void drawProperty(int location, std::vector<std::shared_ptr<Squares>> square);
        void drawPlayers(int location, std::vector<std::shared_ptr<Squares>> currentSquare);
    public:
        BoardDisplay(Board* board);
        void drawBoard();
        void notify() override;
};


#endif

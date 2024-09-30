#ifndef __RESIDENCES_H__
#define __RESIDENCES_H__
#include "buildings.h"
#include <memory>

class Residences: public Buildings {
public:
    Residences(int position, std::string name, int cost);
    int getRent(int numTypeOwned, bool monopolyOwned) override;
};

#endif

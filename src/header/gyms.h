#ifndef __GYMS_H__
#define __GYMS_H__
#include "buildings.h"
#include <string>

class Gyms: public Buildings {
public: 
    Gyms(int position, std::string name, int cost);
    int getRent(int numTypeOwned, bool monopolyOwned) override;
};

#endif

#ifndef __ACADEMICBUILDINGS_H__
#define __ACADEMICBUILDINGS_H__
#include "buildings.h"
#include <string>
#include <vector> 
#include <memory>

class AcademicBuildings : public Buildings {
    std::string monopolyBlock;
    int impCost;
    std::vector<int> tuition;
    int numImp; 
public: 
    AcademicBuildings(int position, std::string name, int cost, std::string monopolyBlock, int impCost, std::vector<int> tuition, int numImp = 0);
    int getNumImp();
    int getRent(int numTypeOwned, bool monopolyOwned) override;
    void setImprovement(std::string action);
    int getImpCost();
    std::string getMonopolyBlock();

};

#endif

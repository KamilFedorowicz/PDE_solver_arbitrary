#pragma once
#include "Grid.h"
#include "BCTypes.h"


class Multigrid
{
public:
    Multigrid();
    void addGrid(Grid& grid);
    void displayWalls();
    void registerNewGrid(const Grid grid);
    void wallGridConnectionInfo();
    std::map<wall, std::vector<Grid*>> wallConnectedWithGrids; // we have a map where each wall has info about grid that connect it
    
private:
    std::vector<Grid> subgrids{};
    std::vector<wall> commonWalls{};
    std::vector<wall> separateWalls{};
    
    std::map<wall, int> wallSizesMap{};
    std::map<wall, BCType> wallBCsMap{};
    
    
};

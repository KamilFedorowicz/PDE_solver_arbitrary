#include "Grid.h"

using wall = std::tuple<double, double, double, double>;

class Multigrid
{
public:
    Multigrid();
    void addGrid(Grid& grid);
    void displayWalls();
    
private:
    std::vector<Grid> subgrids{};
    std::vector<wall> commonWalls{};
    std::vector<wall> separateWalls{};
    
    std::map<wall, int> wallSizesMap{};
    
    
    
};

#include "Grid.h"

class Multigrid
{
public:
    Multigrid();
    void addGrid(Grid& grid);
    void displayWalls();
    
private:
    std::vector<Grid> subgrids{};
    std::vector<std::tuple<double, double, double, double>> commonWalls{};
    std::vector<std::tuple<double, double, double, double>> separateWalls{};
    
};

#include "Multigrid.h"

Multigrid::Multigrid(){}

void Multigrid::addGrid(Grid& grid)
{
    subgrids.push_back(grid);
    const std::vector<std::tuple<double, double, double, double>> walls = grid.returnWalls();
    int newConnectedWalls = 0;
    size_t initialNumberOfSeparateWalls = separateWalls.size(); // initially this will be zero
    
    for(const auto& wall: walls)
    {
        auto it = std::find(separateWalls.begin(), separateWalls.end(), wall);
        std::cout << "Is vertical wall: " << isVerticalWall(wall) << std::endl;
        
        if(it==separateWalls.end())
        {
            separateWalls.push_back(wall);
            std::cout << "Separate wall\n";
        }
        else
        {
            separateWalls.erase(it);
            commonWalls.push_back(wall);
            newConnectedWalls++;
            std::cout << "Common wall \n";
        }
        
    }
    
    // we want to new grid to connect with exactly one other wall
    // when initialNumberOfSeparateWalls=0, then none of the wall is connected and it is fine
    if(newConnectedWalls!=1 && initialNumberOfSeparateWalls!=0)
    {
        throw std::runtime_error("Incorrectly defined grid connection! Aborting!!");
    }
    else
    {
        std::cout << "Correctly defined grid connection! \n";
    }
    
}

void Multigrid::displayWalls()
{
    std::cout << "Separate walls: \n";
    for (auto& [x1, y1, x2, y2] : separateWalls)
    {
        std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
    std::cout << "Common walls: \n";
    for (auto& [x1, y1, x2, y2] : commonWalls)
    {
        std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
}

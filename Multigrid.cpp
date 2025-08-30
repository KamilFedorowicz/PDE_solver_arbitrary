#include "Multigrid.h"

Multigrid::Multigrid(){}

void print(wall wallElem)
{
    std::cout << "Wall: " << std::get<0>(wallElem) << " " << std::get<1>(wallElem) << " " << std::get<2>(wallElem) << " " << std::get<3>(wallElem) << " ";
}


void Multigrid::addGrid(Grid& grid)
{
    registerNewGrid(grid);
    
    const std::vector<wall> walls = grid.returnWalls();
    for(const auto& singleWall: walls)
    {
        auto it = wallConnectedWithGrids.find(singleWall);
        if (it == wallConnectedWithGrids.end())
        {
            // if the wall has no associated grid with it
            wallConnectedWithGrids[singleWall] = {&grid};
        } else
        {
            // if the wall has an associated grid, add another grid
            it->second.push_back(&grid);
        }
    }
}

void Multigrid::wallGridConnectionInfo()
{
    for(auto singleWall: wallConnectedWithGrids)
    {
        print(singleWall.first);
        for(int i=0; i<(singleWall.second).size(); i++){
            Grid* tempGrid = (singleWall.second)[i];
            tempGrid->getGridInfo();
        }
        std::cout << std::endl;
    }
}

// when we add a new grid, this function goes through all the walls, checks if the neighbouring walls are of the right number of elements
// then it adds walls to either map of common walls or separate walls
void Multigrid::registerNewGrid(const Grid grid)
{
    subgrids.push_back(grid);
    const std::vector<wall> walls = grid.returnWalls();
    
    
    int newConnectedWalls = 0;
    size_t initialNumberOfSeparateWalls = separateWalls.size(); // initially this will be zero
    
    for(const auto& singleWall: walls)
    {
        // filling the map with wall sizes
        int wallSize;
        if(isVerticalWall(singleWall)==1)
        {
            wallSize = grid.get_ny();
        }else
        {
            wallSize = grid.get_nx();
        }
        
        auto itWall = wallSizesMap.find(singleWall);
        if (itWall != wallSizesMap.end())
        {
            if(wallSizesMap[singleWall]==wallSize)
            {
                // correct mesh connection. don need to do anything
            }
            else
            {
                throw std::runtime_error("Incorrectly defined grid connection - different numbers of cells of connected walls. Aborting!!");
            }
        }
        else
        {
            wallSizesMap[singleWall] = wallSize;
        }
        // filling vectors with separate/connected walls
        auto it = std::find(separateWalls.begin(), separateWalls.end(), singleWall);
        if(it==separateWalls.end())
        {
            separateWalls.push_back(singleWall);
            //std::cout << "Separate wall\n";
        }
        else
        {
            separateWalls.erase(it);
            commonWalls.push_back(singleWall);
            newConnectedWalls++;
            //std::cout << "Common wall \n";
        }
    }
    
    // we want to new grid to connect with at lease one other wall
    // when initialNumberOfSeparateWalls=0, then none of the wall is connected and it is fine
    if(newConnectedWalls<1 && initialNumberOfSeparateWalls!=0)
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
    
    std::cout << "Wall cell count: " << std::endl;
    for(auto& singleWall: wallSizesMap)
    {
        wall wallElem = singleWall.first;
        std::cout << "Wall: " << std::get<0>(wallElem) << " " << std::get<1>(wallElem) << " " << std::get<2>(wallElem) << " " << std::get<3>(wallElem) << " ";
        std::cout << "cells num: " << singleWall.second << std::endl;
    }
    
}

#include "Grid.h"

Grid::Grid(double start_x, double start_y, double end_x, double end_y, int nx, int ny)
    :start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y), nx(nx), ny(ny)
{
    double step_x = (end_x - start_x) / (nx - 1);
    double step_y = (end_y - start_y) / (ny - 1);

    for (int i = 0; i < nx; ++i)
    {
        x.push_back(start_x + i * step_x);
    }
    
    for (int i = 0; i < ny; ++i)
    {
        y.push_back(start_y + i * step_y);
    }
    
    wallCoords.push_back(std::make_tuple(start_x, start_y, start_x, end_y)); // left vertical
    wallCoords.push_back(std::make_tuple(start_x, end_y, end_x, end_y)); // upper horizontal
    wallCoords.push_back(std::make_tuple(end_x, start_y, end_x, end_y)); // right vertical
    wallCoords.push_back(std::make_tuple(start_x, start_y, end_x, start_y)); // lower horizontal
}

// the first constant means that we cannot modify the return vector
// the second constant means that we cannot modify the object that is calling the function
const std::vector<std::tuple<double, double, double, double>>& Grid::returnWalls() const
{
    return wallCoords;
}

void Grid::getGridInfo()
{
    std::cout << "start_x: " << start_x << ", start_y: " << start_y << ", end_x: " << end_x << ", end_y: " << end_y << "; ";
}

void Grid::displayWalls()
{
    for (auto& [x1, y1, x2, y2] : wallCoords)
    {
        std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
}

// getting wall coordinates
wall Grid::getNorthWall() const {
    return wall{start_x, end_y, end_x, end_y};
}

wall Grid::getSouthWall() const {
    return wall{start_x, start_y, end_x, start_y};
}

wall Grid::getWestWall() const {
    return wall{start_x, start_y, start_x, end_y};
}

wall Grid::getEastWall() const {
    return wall{end_x, start_y, end_x, end_y};
}



double Grid::get_x(int i) const {
    assert(i>=0 && i<=nx);
    if (nx > 1) {
        return x[i];
    }
    else {
        return (start_x+end_x)/2;
    }
}

double Grid::get_y(int i) const {
    assert(i>=0 && i<=ny);
    if (ny > 1) {
        return y[i];
    }
    else {
        return (start_y+end_y)/2;
    }
    
}

const double Grid::get_x_lim(int i) const {
    assert(i==0 || i==1);
    if(i==0){
        return start_x;
    } else if(i==1){
        return end_x;
    }
    
    return 0; // this should never happen
}

const double Grid::get_y_lim(int i) const {
    assert(i==0 || i==1);
    if(i==0){
        return start_y;
    } else if(i==1){
        return end_y;
    }
    
    return 0; // this should never happen
}

const int Grid::get_nx() const {
    return nx;
}
const int Grid::get_ny() const {
    return ny;
}

// this is not in the grid class
bool isVerticalWall(std::tuple<double, double, double, double> wall)
{
    // if start and end x of the wall are the same, then it is a vertical wall
    if(std::get<0>(wall)==std::get<2>(wall))
    {
        return true;
    }
    
    return false;
    
}

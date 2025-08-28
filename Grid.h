#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>   // For std::ofstream
#include <string>    // For std::string
#include <cassert> // for assert
#include <tuple>
#include <map>

class Grid {
public:
    
    Grid(double start_x, double start_y, double end_x, double end_y, int nx, int ny);
    double get_x(int i) const ;
    double get_y(int i) const ;
    const double get_x_lim(int i) const ;
    const double get_y_lim(int i) const ;
    const int get_nx() const ;
    const int get_ny() const ;

    void displayWalls();

    

    const std::vector<std::tuple<double, double, double, double>>& returnWalls() const;
    
private:
    const int nx, ny;
    std::vector<double> x, y;
    double start_x = 0, start_y = 0;
    double end_x = 1, end_y = 1;

    // walls go from south to north or west to east
    // first two coords correspond to x and y of the south/west coord, second correspond to x and y of the north/east coord
    std::vector<std::tuple<double, double, double, double>> wallCoords{};

};

// this is defined outside of the class
bool isVerticalWall(std::tuple<double, double, double, double> wall);

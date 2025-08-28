#pragma once
#include "BoundaryCondition.h"
#include "Grid.h"
#include <vector>
#include "FieldTypes.h"

class MyBoundaryCondition : public BoundaryCondition
{
public:
    MyBoundaryCondition() = default;

    // === Apply wall and obstacle BCs for a scalar field
    void apply(scalarField& field, const Grid& grid) const {
        applyWallBCs(field, grid);
    }
    
    // === Wall BC type setters - independent of scalar/vector ===
    void setEastType(BCType type) { eastType = type; }
    void setWestType(BCType type) { westType = type; }
    void setNorthType(BCType type) { northType = type; }
    void setSouthType(BCType type) { southType = type; }
    
    // === Wall BC setters for scalars===
    void setEastValue(double val) { east_value_scalar = val; }
    void setWestValue(double val) { west_value_scalar = val; }
    void setNorthValue(double val) { north_value_scalar = val; }
    void setSouthValue(double val) { south_value_scalar = val; }



    
    

private:
    
    // === Wall BC parameters ===
    double east_value_scalar = 0.0, west_value_scalar = 0.0, north_value_scalar = 0.0, south_value_scalar = 0.0;

    BCType eastType = BCType::FixedValue;
    BCType westType = BCType::FixedValue;
    BCType northType = BCType::FixedValue;
    BCType southType = BCType::FixedValue;


    // === Apply wall BCs for a scalar field
void applyWallBCs(scalarField& field, const Grid& grid) const {
    int nx = grid.get_nx();
    int ny = grid.get_ny();

    double dx = (nx > 1) ? (grid.get_x(1) - grid.get_x(0)) : 1.0;
    double dy = (ny > 1) ? (grid.get_y(1) - grid.get_y(0)) : 1.0;

    if (nx > 1) {
        // WEST
        for (int i = 0; i < ny; ++i) {
            if (westType == BCType::FixedValue) {
                field[i][0] = west_value_scalar;
            }
            else { // ZeroGradient
                field[i][0] = field[i][1];
            }
        }
        // EAST
        for (int i = 0; i < ny; ++i) {
            if (eastType == BCType::FixedValue) {
                field[i][nx - 1] = east_value_scalar;
            }
            else { // ZeroGradient
                field[i][nx - 1] = field[i][nx - 2];
            }
        }
    }

    if (ny > 1) {
        // SOUTH
        for (int j = 0; j < nx; ++j) {
            if (southType == BCType::FixedValue) {
                field[0][j] = south_value_scalar;
            }
            else { // ZeroGradient
                field[0][j] = field[1][j];
            }
        }
        // NORTH
        for (int j = 0; j < nx; ++j) {
            if (northType == BCType::FixedValue) {
                field[ny - 1][j] = north_value_scalar;
            }
            else { // ZeroGradient
                field[ny - 1][j] = field[ny - 2][j];
            }
        }
    }
}

    



    

    
    
    
    
};

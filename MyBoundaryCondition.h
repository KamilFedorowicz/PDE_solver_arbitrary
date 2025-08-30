#pragma once
#include "BoundaryCondition.h"
#include "Grid.h"
#include <vector>
#include "FieldTypes.h"
#include "Multigrid.h"

class MyBoundaryCondition : public BoundaryCondition
{
public:
    MyBoundaryCondition(Multigrid _multigrid, std::vector<EquationBase*> _equationsInGrids): multigrid(_multigrid), equationsInGrids(_equationsInGrids){}

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
    
    void printBCType(BCType bc_type)
    {
        if(bc_type == BCType::Interface)
        {
            std::cout << "interface" << std::endl;
        } else if(bc_type == BCType::FixedValue)
        {
            std::cout << "fixed value" << std::endl;
        }else
        {
            std::cout << "fixed gradient" << std::endl;
        }
    }
    
    void printWallsBCs()
    {
        std::cout << "East type: ";
        printBCType(eastType);
        std::cout << "West type: ";
        printBCType(westType);
        std::cout << "North type: ";
        printBCType(northType);
        std::cout << "South type: ";
        printBCType(southType);
    }

private:
    
    std::vector<EquationBase*> equationsInGrids{};
    Multigrid multigrid;
    // === Wall BC parameters ===
    double east_value_scalar = 0.0, west_value_scalar = 0.0, north_value_scalar = 0.0, south_value_scalar = 0.0;

    // set the interface BC by default
    BCType eastType = BCType::Interface;
    BCType westType = BCType::Interface;
    BCType northType = BCType::Interface;
    BCType southType = BCType::Interface;


    // === Apply wall BCs for a scalar field
void applyWallBCs(scalarField& field, const Grid& grid) const {
    int nx = grid.get_nx();
    int ny = grid.get_ny();

    // double dx = (nx > 1) ? (grid.get_x(1) - grid.get_x(0)) : 1.0;
    // double dy = (ny > 1) ? (grid.get_y(1) - grid.get_y(0)) : 1.0;

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
        for (int j = 0; j < nx; ++j)
        {
            if (northType == BCType::FixedValue) {
                field[ny - 1][j] = north_value_scalar;
            }
            else if (northType == BCType::Interface)
            {
                wall northWall = grid.getNorthWall();
                
                // Find which grids share this wall
                auto it = multigrid.wallConnectedWithGrids.find(northWall);
                if (it != multigrid.wallConnectedWithGrids.end())
                {
                    const auto& connectedGrids = it->second;

                    for (Grid* neighbor : connectedGrids) {
                        if (neighbor == &grid) continue; // skip myself

                        // Find the EquationBase corresponding to this neighbor grid
                        EquationBase* neighborEq = nullptr;
                        for (auto* eq : equationsInGrids)
                        {
                            if (&(eq->getGrid()) == neighbor)
                            {
                                neighborEq = eq;
                                break;
                            }
                        }

                        if (neighborEq)
                        {
                            // Get the neighbor's SOUTH boundary values
                            std::vector<double> southVals = neighborEq->returnSouthValue("temperature");
                            // you can generalize the name later

                            // Impose them directly on my NORTH boundary
                            for (int jj = 0; jj < nx && jj < (int)southVals.size(); ++jj) {
                                field[ny - 1][jj] = southVals[jj];
                            }
                        }
                    }
                }
        
        
                
                
                
                
                
                // ZeroGradient
                //field[ny - 1][j] = field[ny - 2][j];
                //std::cout << "We are in the interface! Do nothing" << std::endl;

            } else {
                field[ny - 1][j] = field[ny - 2][j];
            }
        }
    }
}

    



    

    
    
    
    
};

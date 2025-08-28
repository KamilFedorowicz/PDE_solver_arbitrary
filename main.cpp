#include <iostream>
#include "Grid.h"
#include "Multigrid.h"
#include "EquationBase.h"
#include "Equation01.h"
#include "Solver.h"
#include "MyBoundaryCondition.h"

int main(int argc, const char * argv[]) {
    // to do: check if the number of cells is the same
    // use multigrid and within it solve for each grid?
    
    int nx = 20;
    int ny = 20;
    Grid grid1(0, 0, 1, 1, nx, ny);
    Grid grid2(0, 1, 1, 2, nx, ny-1); // above grid 1
    //Grid grid3(0, 2, 1, 3, nx-1, ny); // above grid 2
    
    Multigrid multigrid;
    multigrid.addGrid(grid1);
    multigrid.addGrid(grid2);
    //multigrid.addGrid(grid3);
    multigrid.displayWalls();
    
    
    
    
    
    
    std::map<std::string, double> constantsMap;
    constantsMap["D_temperature"] = 0.1;
    
    Equation01 eq(grid1, constantsMap);
    scalarField initialField(ny, std::vector<double>(nx, 0.0));
    eq.initialiseField("temperature", initialField);
    
    Solver solver(eq, grid1);
    
    MyBoundaryCondition bc_temperature;
    bc_temperature.setNorthType(BCType::FixedValue);
    bc_temperature.setSouthType(BCType::FixedValue);
    bc_temperature.setWestType(BCType::FixedValue);
    bc_temperature.setEastType(BCType::FixedValue);
    bc_temperature.setNorthValue(1);
    bc_temperature.setSouthValue(1);
    bc_temperature.setWestValue(0);
    bc_temperature.setEastValue(0);

    std::map<std::string, const BoundaryCondition*> scalar_bcs;
    scalar_bcs["temperature"] = &bc_temperature;
    //solver.solve(10, 0.001, scalar_bcs);
    
    
    
    return 0;
}

#include <iostream>
#include "Grid.h"
#include "Multigrid.h"
#include "EquationBase.h"
#include "Equation01.h"
#include "Solver.h"
#include "MyBoundaryCondition.h"
#include "VTKExporter.h"

int main(int argc, const char * argv[]) {
    // to do: when solving an equation, go grid by grid and in BC check the interface type
    // tomorrow: 1) understand the code; 2) make it work for all boundaries; 3) plot multiple squares; 4) solve for multiple squares at the same time
    
    int nx1 = 20;
    int ny1 = 20;
    int nx2 = 20;
    int ny2 = 19;
    Grid grid1(0, 0, 1, 1, nx1, ny1);
    Grid grid2(0, 1, 1, 2, nx2, ny2); // above grid 1
    
    Multigrid multigrid;
    multigrid.addGrid(grid1);
    multigrid.addGrid(grid2);
    multigrid.displayWalls();
    
    multigrid.wallGridConnectionInfo();
    
    std::map<std::string, double> constantsMap;
    constantsMap["D_temperature"] = 0.1;
    
    std::vector<EquationBase*> equationsInGrids{};
    
    // initialise equation solver on field 1
    Equation01 eq1(grid1, constantsMap);
    scalarField initialFiel1(ny1, std::vector<double>(nx1, 0.0));
    eq1.initialiseField("temperature", initialFiel1);
    Solver solver1(eq1, grid1);
    equationsInGrids.push_back(&eq1);
    
    // initialise equation solver on field 2
    Equation01 eq2(grid2, constantsMap);
    scalarField initialFiel2(ny2, std::vector<double>(nx2, 4.0));
    eq2.initialiseField("temperature", initialFiel2);
    equationsInGrids.push_back(&eq2);
    
    
    MyBoundaryCondition bc1_temperature(multigrid, equationsInGrids);
    bc1_temperature.setSouthType(BCType::FixedValue);
    bc1_temperature.setWestType(BCType::FixedValue);
    bc1_temperature.setEastType(BCType::FixedValue);
    bc1_temperature.setSouthValue(1);
    bc1_temperature.setWestValue(1);
    bc1_temperature.setEastValue(0);
    
    MyBoundaryCondition bc2_temperature(multigrid, equationsInGrids);
    bc2_temperature.setNorthType(BCType::FixedValue);
    bc2_temperature.setWestType(BCType::FixedValue);
    bc2_temperature.setEastType(BCType::FixedValue);
    bc2_temperature.setNorthValue(1);
    bc2_temperature.setWestValue(1);
    bc2_temperature.setEastValue(0);
    
    

    std::map<std::string, const BoundaryCondition*> scalar_bcs1;
    scalar_bcs1["temperature"] = &bc1_temperature;
    solver1.solve(1000, 0.001, scalar_bcs1);
    
    std::string pathName = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_arbitrary/PDE_solver_arbitrary/temp_vtk.vtk";
    VTKExporter::saveScalarField(grid1, eq1.getScalarField("temperature"), pathName, "temperature");
    
    return 0;
}

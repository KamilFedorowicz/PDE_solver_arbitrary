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
    // 3) solve for multiple squares at the same time; 4) plot multiple squares - automate;
    
    int nx1 = 20;
    int ny1 = 20;
    int nx2 = 19;
    int ny2 = 20;
    Grid grid1(0, 0, 1, 1, nx1, ny1);
    Grid grid2(1, 0, 2, 1, nx2, ny2);
    
    Multigrid multigrid;
    multigrid.addGrid(grid1);
    multigrid.addGrid(grid2);
    multigrid.displayWalls();
    
    multigrid.wallGridConnectionInfo();
    
    std::map<std::string, double> constantsMap;
    constantsMap["D_temperature"] = 0.1;
    
    std::vector<EquationBase*> equationsInGrids{};
    
    std::string fieldName = "temperature";
    // initialise equation solver on field 1
    Equation01 eq1(grid1, constantsMap);
    scalarField initialFiel1(ny1, std::vector<double>(nx1, 0.0));
    eq1.initialiseField(fieldName, initialFiel1);
    Solver solver1(eq1, grid1);
    equationsInGrids.push_back(&eq1);
    
    // initialise equation solver on field 2
    Equation01 eq2(grid2, constantsMap);
    scalarField initialFiel2(ny2, std::vector<double>(nx2, 4.0));
    eq2.initialiseField(fieldName, initialFiel2);
    equationsInGrids.push_back(&eq2);
    
    
    MyBoundaryCondition bc1_temperature(multigrid, equationsInGrids, fieldName);
    bc1_temperature.setNorthType(BCType::FixedValue);
    bc1_temperature.setWestType(BCType::FixedValue);
    bc1_temperature.setSouthType(BCType::FixedValue);
    bc1_temperature.setNorthValue(1);
    bc1_temperature.setWestValue(1);
    bc1_temperature.setSouthValue(0);
    
    
    MyBoundaryCondition bc2_temperature(multigrid, equationsInGrids, fieldName);
    bc2_temperature.setSouthType(BCType::FixedValue);
    bc2_temperature.setNorthType(BCType::FixedValue);
    bc2_temperature.setEastType(BCType::FixedValue);
    bc2_temperature.setSouthValue(1);
    bc2_temperature.setNorthValue(1);
    bc2_temperature.setEastValue(0);
    
    
    
    std::map<std::string, const BoundaryCondition*> scalar_bcs1;
    scalar_bcs1[fieldName] = &bc1_temperature;
    solver1.solve(1000, 0.001, scalar_bcs1);
    
    std::string pathName1 = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_arbitrary/PDE_solver_arbitrary/temp_vtk1.vtk";
    VTKExporter::saveScalarField(grid1, eq1.getScalarField(fieldName), pathName1, fieldName);
    std::string pathName2 = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_arbitrary/PDE_solver_arbitrary/temp_vtk2.vtk";
    VTKExporter::saveScalarField(grid2, eq2.getScalarField(fieldName), pathName2, fieldName);
    
    std::vector<GridWithField> gridsWithField{};
    
    gridsWithField.push_back(GridWithField(&grid1, &eq1.getScalarField(fieldName))); // GridWithField(&grid1, &eq1.getScalarField(fieldName)) - initialise an element
    gridsWithField.push_back(GridWithField(&grid2, &eq2.getScalarField(fieldName)));

    
    std::string fileNameTotal = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_arbitrary/PDE_solver_arbitrary/temp_total.vtk";
    VTKExporter::saveMultipleGrids(gridsWithField, fileNameTotal, fieldName);
    
    return 0;
}



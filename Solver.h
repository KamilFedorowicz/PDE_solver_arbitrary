#pragma once
#include "EquationBase.h"
#include "BoundaryCondition.h"
#include "Grid.h"
#include <map>
#include "FieldTypes.h"

// take the solving process away from the equation

class Solver {
public:
    Solver(EquationBase& eq, Grid& grid) : equation(eq), grid(grid)
    {
    }

    void solve(int steps, double dt, std::map<std::string, const BoundaryCondition*>& scalar_bcs)
    {
        equation.checkIfAllVariablesAreInitialised();
        for (int i = 0; i < steps; ++i)
        {
            std::cout << "Step: " << i << std::endl;
            equation.step(scalar_bcs, dt);  // one time step. function defined in Equation01 etc
            updateFields(scalar_bcs, dt); // equation.step calculates d/dt, updateFields calculates values after the time step
            
        }
    }
    
    void updateFields(std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt)
    {
        for (auto it = equation.dScalarFields_dt.begin(); it != equation.dScalarFields_dt.end(); it++)
        {
            auto fieldName = it->first;
            auto dField = it->second; // pointer to derivative
            
            scalarField oldField = *(equation.scalarFields[fieldName]);
            *(equation.scalarFields[fieldName]) = *(equation.scalarFields[fieldName]) + (*dField) * dt;

            // the first argument of apply is the field that will be updated
            scalar_bcs.at(fieldName)->apply(*(equation.scalarFields[fieldName]), grid);
            scalarField newField = *(equation.scalarFields[fieldName]);
            
            double error = computeRootMeanSquaredValueOfScalarField(newField - oldField); // calculate the error
            std::cout<< "Scalar field: " << fieldName << ", error: " << error << std::endl;
        }

    }
    
private:
    double dt;
    EquationBase& equation;
    std::vector<std::vector<double>> field;
    Grid& grid;

    
};



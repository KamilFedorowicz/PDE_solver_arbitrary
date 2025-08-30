#pragma once

#include <vector>
#include <map>
#include "Grid.h"
#include "Laplacian.h"
#include "BoundaryCondition.h"
#include "EquationBase.h"
#include "MathOperators.h"
#include "Multigrid.h"


class Equation01 : public EquationBase {
public:
    Equation01(
    Grid& grid,
    std::map<std::string, double> constantsMap
    );
    
    std::vector<std::string> getScalarVariableNames() const override;
    static std::vector<std::string> getConstantsNames();

    void step(std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt) override;

private:
    Grid& grid;

    double D_temperature;
    double dt;

    scalarField temperature;
    scalarField dTemperature_dt;
};

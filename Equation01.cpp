#include "Equation01.h"


Equation01::Equation01(
    Grid& grid,
    std::map<std::string, double> constantsMap
)
: grid(grid),
      EquationBase(grid)
{
    // read constants from the map
    D_temperature = constantsMap.at("D_temperature");
    // Declare fields that we solve for
    scalarFields["temperature"] = &temperature;
}


std::vector<std::string> Equation01::getScalarVariableNames() const {
    return {"temperature"};
}


std::vector<std::string> Equation01::getConstantsNames() {
    return {"D_temperature"};
}

void Equation01::step(std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt)
{
    // Computing scalar derivatives
    dTemperature_dt = D_temperature * Laplacian::compute(grid, temperature);


    dScalarFields_dt["temperature"] = &dTemperature_dt;

}



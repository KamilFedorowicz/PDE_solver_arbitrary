#include "EquationBaseMultigrid.h"



// Constructor
EquationBaseMultigrid::EquationBaseMultigrid(Multigrid& multigrid_) : multigrid(multigrid_) {}

// solve implementation
void EquationBaseMultigrid::solve(int steps,
                         std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt)
{
    for (int i = 0; i < steps; ++i) {
        step(scalar_bcs, dt);
    }
}

// initialise scalar field
void EquationBaseMultigrid::initialiseField(std::string name, const scalarField field)
{
    // later add a check if the name is correct
    auto it = scalarFields.find(name);
    *(it->second) = field;
}

// get scalar field with static fallback
const scalarField& EquationBaseMultigrid::getScalarField(std::string name) const
{
    // later add a check if the equation exists
    auto it = scalarFields.find(name);
    return *(it->second);

}

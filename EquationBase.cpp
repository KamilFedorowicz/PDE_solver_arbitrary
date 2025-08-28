#include "EquationBase.h"

EquationNames toEquationName(const std::string& str) {
    static const std::map<std::string, EquationNames> lookup = {
        {"Equation01", EquationNames::Equation01},
        {"Equation02", EquationNames::Equation02}
    };

    auto it = lookup.find(str);
    if (it != lookup.end()) {
        return it->second;
    }
    return EquationNames::Empty; // fallback
}

// Constructor
EquationBase::EquationBase(Grid& grid_) : grid(grid_) {}

// solve implementation
void EquationBase::solve(int steps,
                         std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt)
{
    for (int i = 0; i < steps; ++i) {
        step(scalar_bcs, dt);
    }
}

// initialise scalar field
void EquationBase::initialiseField(std::string name, const scalarField field) {
    auto it = scalarFields.find(name);

    if (it != scalarFields.end()) {
        if (field.size() != grid.get_ny() || field[0].size() != grid.get_nx()) {
            throw std::runtime_error("Scalar field size does not match grid dimensions.");
        }
        *(it->second) = field;
    } else {
        std::cout << "The name " << name << " is not the right name of a scalar field!" << std::endl;
    }
}


// check scalar fields
void EquationBase::checkIfScalarFieldsAreInitialised() {
    for (const auto& it : scalarFields) {
        const std::string& name = it.first;
        const auto* fieldPtr = it.second;

        if (!fieldPtr) {
            std::cout << "Field " << name << " is not initialised!" << std::endl;
            throw std::runtime_error("Field not initialised!.");
        }
        else if (fieldPtr->empty() || (*fieldPtr)[0].empty()) {
            std::cout << "Field " << name << " is empty!" << std::endl;
            throw std::runtime_error("Field is empty.");
        }
    }
}



// check all variables
void EquationBase::checkIfAllVariablesAreInitialised() {
    checkIfScalarFieldsAreInitialised();
}

// get scalar field with static fallback
const scalarField& EquationBase::getScalarField(std::string name) const
{
    auto it = scalarFields.find(name);
    if (it != scalarFields.end()) {
        return *(it->second);
    } else {
        static scalarField zeroField(grid.get_ny(), std::vector<double>(grid.get_nx(), 0.0));
        std::cout << "Incorrect name " << name << ", returning zero field!" << std::endl;
        return zeroField;
    }
}

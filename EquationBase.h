#pragma once
#include <vector>
#include <map>
#include <string>
#include "Grid.h"
#include "BoundaryCondition.h"
#include "FieldTypes.h"
#include <iostream>
#include <cmath>
#include <stdexcept>


enum class EquationNames {
    Equation02,
    Equation01,
    Empty
};

EquationNames toEquationName(const std::string& str);

namespace EquationUtils {
    inline std::string to_string(EquationNames eq) {
        switch (eq) {
            case EquationNames::Equation02: return "Equation02";
            case EquationNames::Equation01: return "Equation01";
            //case EquationNames::Empty:      return "Empty";
            default:                        return "Empty";
        }
    }
}
class EquationBase {
public:
    EquationBase(Grid& grid_);
    virtual ~EquationBase() = default;

    virtual void step(std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt) = 0;

    virtual void solve(int steps,
                       std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt);

    virtual std::vector<std::string> getScalarVariableNames() const {
        return {};
    }
    

    
    void initialiseField(std::string name, const scalarField field);


    void checkIfAllVariablesAreInitialised();
    void checkIfScalarFieldsAreInitialised();

    // Accessors for fields
    const scalarField& getScalarField(std::string name) const;

    scalarFieldMap scalarFields;
    scalarFieldMap dScalarFields_dt;
    scalarFieldMap scalarSourceTerms;

private:
    Grid& grid;
};

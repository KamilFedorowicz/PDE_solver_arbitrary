#pragma once
#include <vector>
#include <map>
#include <string>
#include "Multigrid.h"
#include "BoundaryCondition.h"
#include "FieldTypes.h"
#include <iostream>
#include <cmath>
#include <stdexcept>




class EquationBaseMultigrid {
public:
    EquationBaseMultigrid(Multigrid& multigrid_);
    virtual ~EquationBaseMultigrid() = default;

    virtual void step(std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt) = 0;

    virtual void solve(int steps, std::map<std::string, const BoundaryCondition*>& scalar_bcs, double dt);
    
    void initialiseField(std::string name, const scalarField field);


    // Accessors for fields
    const scalarField& getScalarField(std::string name) const;

    scalarFieldMap scalarFields;
    scalarFieldMap dScalarFields_dt;
    scalarFieldMap scalarSourceTerms;

private:
    Multigrid& multigrid;
};

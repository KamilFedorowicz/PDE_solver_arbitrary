#pragma once
#include <vector>
#include "Grid.h"
#include "FieldTypes.h"

enum class BoundarySide {
    North,
    South,
    East,
    West
};

class BoundaryCondition {
public:
    // Apply all BCs (entire field/grid)
    virtual void apply(scalarField& field, const Grid& grid, std::string fieldName) const = 0;
    virtual ~BoundaryCondition() {}
};

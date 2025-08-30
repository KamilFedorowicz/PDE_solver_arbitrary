#pragma once
#include <memory>
#include <vector>
#include "Grid.h"
#include "Multigrid.h"
#include "EquationBase.h"

class Laplacian{
public:
    
static const std::vector<std::vector<double>> compute(const Grid& grid,
                                                      const std::vector<std::vector<double>>& field) {
    std::vector<std::vector<double>> result(grid.get_ny(), std::vector<double>(grid.get_nx(), 0));

    double dx = (grid.get_nx() > 1) ? (grid.get_x(1) - grid.get_x(0)) : 1.0;
    double dy = (grid.get_ny() > 1) ? (grid.get_y(1) - grid.get_y(0)) : 1.0;

    for (int i = 0; i < grid.get_ny(); ++i) {
        for (int j = 0; j < grid.get_nx(); ++j) {

            double d2_dx2 = 0.0;
            double d2_dy2 = 0.0;

            // --- X direction ---
            if (grid.get_nx() > 1) {
                if (j == 0 && grid.get_nx() >= 4) {
                    // Forward one-sided (needs at least 4 points)
                    d2_dx2 = (2 * field[i][j] - 5 * field[i][j + 1] +
                              4 * field[i][j + 2] - field[i][j + 3]) / (dx * dx);
                } else if (j == grid.get_nx() - 1 && grid.get_nx() >= 4) {
                    // Backward one-sided
                    d2_dx2 = (2 * field[i][j] - 5 * field[i][j - 1] +
                              4 * field[i][j - 2] - field[i][j - 3]) / (dx * dx);
                } else if (j > 0 && j < grid.get_nx() - 1) {
                    // Central difference
                    d2_dx2 = (field[i][j + 1] - 2 * field[i][j] + field[i][j - 1]) / (dx * dx);
                }
                // else: grid too small for meaningful derivative leave as 0
            }

            // --- Y direction ---
            if (grid.get_ny() > 1) {
                if (i == 0 && grid.get_ny() >= 4) {
                    d2_dy2 = (2 * field[i][j] - 5 * field[i + 1][j] +
                              4 * field[i + 2][j] - field[i + 3][j]) / (dy * dy);
                } else if (i == grid.get_ny() - 1 && grid.get_ny() >= 4) // access the other mesh here
                {
                    d2_dy2 = (2 * field[i][j] - 5 * field[i - 1][j] +
                              4 * field[i - 2][j] - field[i - 3][j]) / (dy * dy);
                }
                else if (i > 0 && i < grid.get_ny() - 1) {
                    d2_dy2 = (field[i + 1][j] - 2 * field[i][j] + field[i - 1][j]) / (dy * dy);
                }
            }

            result[i][j] = d2_dx2 + d2_dy2;
        }
    }
    return result;
}

};

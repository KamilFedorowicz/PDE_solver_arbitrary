#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Grid.h"

struct GridWithField {
    Grid* grid;
    const std::vector<std::vector<double>>* data; // pointer to scalar field
};

class VTKExporter {
public:
    // Save scalar field (2D data)
    static void saveScalarField(const Grid& grid,
                                const std::vector<std::vector<double>>& data,
                                const std::string& filename,
                                const std::string& fieldName = "scalarField")
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        
        int nx = grid.get_nx();
        int ny = grid.get_ny();
        
        // VTK legacy header
        file << "# vtk DataFile Version 3.0\n";
        file << fieldName << "\n";
        file << "ASCII\n";
        file << "DATASET STRUCTURED_POINTS\n";
        file << "DIMENSIONS " << nx << " " << ny << " 1\n";
        file << "ORIGIN " << grid.get_x(0) << " " << grid.get_y(0) << " 0\n";
        file << "SPACING " << (grid.get_x(1) - grid.get_x(0)) << " "
        << (grid.get_y(1) - grid.get_y(0)) << " 1\n";
        file << "POINT_DATA " << nx * ny << "\n";
        file << "SCALARS " << fieldName << " double\n";
        file << "LOOKUP_TABLE default\n";
        
        // Write scalar values (VTK expects row-major ordering: y outer, x inner)
        for (int i = 0; i < ny; ++i) {
            for (int j = 0; j < nx; ++j) {
                file << data[i][j] << "\n";
            }
        }
        
        file.close();
    }
    
    static void saveMultipleGrids(const std::vector<GridWithField>& grids,
                                  const std::string& filename,
                                  const std::string& fieldName = "scalarField")
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        file << "# vtk DataFile Version 3.0\n";
        file << "Multiple grids (cell data)\n";
        file << "ASCII\n";
        file << "DATASET UNSTRUCTURED_GRID\n";

        // First, count total points and cells
        int totalPoints = 0;
        int totalCells = 0;
        for (const auto& g : grids) {
            int nx = g.grid->get_nx();
            int ny = g.grid->get_ny();
            totalPoints += nx * ny;
            totalCells += (nx - 1) * (ny - 1);
        }

        // Write all points
        file << "POINTS " << totalPoints << " double\n";
        for (const auto& g : grids) {
            int nx = g.grid->get_nx();
            int ny = g.grid->get_ny();
            for (int i = 0; i < ny; ++i) {
                for (int j = 0; j < nx; ++j) {
                    double x = g.grid->get_x(j);
                    double y = g.grid->get_y(i);
                    file << x << " " << y << " 0\n";
                }
            }
        }

        // Write cells as quads
        file << "CELLS " << totalCells << " " << totalCells * 5 << "\n"; // 4 points + 1 count
        int pointOffset = 0;
        for (const auto& g : grids) {
            int nx = g.grid->get_nx();
            int ny = g.grid->get_ny();
            for (int i = 0; i < ny - 1; ++i) {
                for (int j = 0; j < nx - 1; ++j) {
                    int p0 = pointOffset + i * nx + j;
                    int p1 = pointOffset + i * nx + (j + 1);
                    int p2 = pointOffset + (i + 1) * nx + (j + 1);
                    int p3 = pointOffset + (i + 1) * nx + j;
                    file << "4 " << p0 << " " << p1 << " " << p2 << " " << p3 << "\n";
                }
            }
            pointOffset += nx * ny;
        }

        // Write cell types (VTK_QUAD = 9)
        file << "CELL_TYPES " << totalCells << "\n";
        for (int c = 0; c < totalCells; ++c) {
            file << "9\n";
        }

        // Write cell data (instead of point data)
        file << "CELL_DATA " << totalCells << "\n";
        file << "SCALARS " << fieldName << " double\n";
        file << "LOOKUP_TABLE default\n";

        // For each cell, assign a value (average of 4 corners here)
        for (const auto& g : grids) {
            int nx = g.grid->get_nx();
            int ny = g.grid->get_ny();
            for (int i = 0; i < ny - 1; ++i) {
                for (int j = 0; j < nx - 1; ++j) {
                    double v = ((*g.data)[i][j] +
                                (*g.data)[i][j+1] +
                                (*g.data)[i+1][j] +
                                (*g.data)[i+1][j+1]) / 4.0;
                    file << v << "\n";
                }
            }
        }

        file.close();
    }
};

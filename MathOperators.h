#pragma once
#include <vector>
#include <stdexcept>
#include "FieldTypes.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <array>

// Multiply scalar * 2D vector
inline scalarField operator*(double scalar, const scalarField& field)
{
    scalarField result = field;

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j) {
            result[i][j] *= scalar;
        }
    }
    return result;
}

inline scalarField operator/(const scalarField& field, double scalar)
{
    scalarField result = field;

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j) {
            result[i][j] /= scalar;
        }
    }
    return result;
}

inline scalarField operator/(const scalarField& field, scalarField divider)
{
    scalarField result = field;

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j) {
            result[i][j] /= divider[i][j];
        }
    }
    return result;
}

inline scalarField operator*(
    const scalarField& field,
    double scalar)
{
    return scalar * field; // reuse the other overload
}



inline scalarField operator+(const scalarField& field1, const scalarField& field2)
{
    if (field1.size() != field2.size() || field1[0].size() != field2[0].size()) {
        throw std::invalid_argument("Matrix size mismatch in operator+");
    }

    scalarField result = field1;

    for (size_t i = 0; i < field1.size(); ++i) {
        for (size_t j = 0; j < field1[0].size(); ++j) {
            result[i][j] += field2[i][j];
        }
    }
    return result;
}

inline scalarField operator-(const scalarField& field1, const scalarField& field2)
{
    if (field1.size() != field2.size() || field1[0].size() != field2[0].size()) {
        throw std::invalid_argument("Matrix size mismatch in operator+");
    }

    scalarField result = field1;

    for (size_t i = 0; i < field1.size(); ++i) {
        for (size_t j = 0; j < field1[0].size(); ++j) {
            result[i][j] -= field2[i][j];
        }
    }
    return result;
}

inline scalarField operator-(const scalarField& field1, const double& val)
{
    scalarField result = field1;

    for (size_t i = 0; i < field1.size(); ++i) {
        for (size_t j = 0; j < field1[0].size(); ++j) {
            result[i][j] -= val;
        }
    }
    return result;
}

inline scalarField operator-(const double& val, const scalarField& field1)
{
    scalarField result = scalarField(field1.size(), std::vector<double>(field1[0].size(), 0.0));

    for (size_t i = 0; i < field1.size(); ++i) {
        for (size_t j = 0; j < field1[0].size(); ++j) {
            result[i][j] = val - field1[i][j];
        }
    }
    return result;
}

inline double computeRootMeanSquaredValueOfScalarField(const scalarField& scalField){
    double sumSquares = 0.0;

    const size_t ny = scalField.size();
    const size_t nx = scalField[0].size();

    for (size_t i = 0; i < ny; ++i) {
        for (size_t j = 0; j < nx; ++j) {
            sumSquares += std::pow(scalField[i][j], 2);
        }
    }

    return std::sqrt(sumSquares / static_cast<double>(ny * nx));
}



inline scalarField operator^(const scalarField& field, const double& n)
{
    scalarField result = scalarField(field.size(), std::vector<double>(field[0].size(), 1.0));

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j)
        {
            result[i][j] = std::pow(field[i][j], n);
        }
    }

    return result;
}

inline scalarField minField(const scalarField& field, double value)
{
    scalarField result(field.size(), std::vector<double>(field[0].size(), 0.0));

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            result[i][j] = std::min(field[i][j], value);
        }
    }

    return result;
}

inline scalarField maxField(const scalarField& field, double value)
{
    scalarField result(field.size(), std::vector<double>(field[0].size(), 0.0));

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            result[i][j] = std::max(field[i][j], value);
        }
    }

    return result;
}

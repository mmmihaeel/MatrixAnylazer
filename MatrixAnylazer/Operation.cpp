#include "Operation.h"

void Operation::setMatrix(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.size() != matrix[0].size()) {
        throw std::invalid_argument("Matrix must be non-empty and square.");
    }
    this->matrix = matrix;
}
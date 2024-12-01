#include "BelowSideDiagonalOperation.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>

template <typename T>
BelowSideDiagonalOperation<T>::BelowSideDiagonalOperation(const std::vector<std::vector<T>>& matrix)
{
    if (matrix.empty() || matrix.size() != matrix[0].size())
    {
        throw std::invalid_argument("Matrix must be non-empty and square.");
    }
    this->matrix = matrix;
}

template <typename T>
void BelowSideDiagonalOperation<T>::execute()
{
    if (matrix.empty() || matrix.size() != matrix[0].size())
    {
        throw std::runtime_error("Matrix is invalid or not square.");
    }

    int size = matrix.size();
    minVal = matrix[1][size - 1]; 
    maxVal = matrix[1][size - 1];

 
    std::cout << "Matrix size: " << size << "\n";
    std::cout << "Initial minVal = " << minVal << ", maxVal = " << maxVal << "\n";

    for (int i = 1; i < size; ++i)
    {
        for (int j = size - i; j < size; ++j)
        {
            minVal = std::min(minVal, matrix[i][j]);
            maxVal = std::max(maxVal, matrix[i][j]);

            std::cout << "Processing element at (" << i << "," << j << ") = " << matrix[i][j] << "\n";
        }
    }

    std::cout << "Final minVal = " << minVal << ", maxVal = " << maxVal << "\n";

    std::ostringstream oss;
    oss << "Below Side Diagonal: Min = " << minVal << ", Max = " << maxVal;

    result = oss.str();

    std::cout << "Result: " << result << "\n";
}

template <typename T>
T BelowSideDiagonalOperation<T>::getMinValue() const
{
    return minVal;
}

template <typename T>
T BelowSideDiagonalOperation<T>::getMaxValue() const
{
    return maxVal;
}

template <typename T>
void BelowSideDiagonalOperation<T>::setMinValue(T value)
{
    minVal = value;
}

template <typename T>
void BelowSideDiagonalOperation<T>::setMaxValue(T value)
{
    maxVal = value;
}

template <typename T>
std::string BelowSideDiagonalOperation<T>::getResult() const
{
    return result;
}

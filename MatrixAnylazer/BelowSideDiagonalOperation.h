#ifndef BELOW_SIDE_DIAGONAL_OPERATION_H
#define BELOW_SIDE_DIAGONAL_OPERATION_H

#include "Operation.h"
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <stdexcept>

template <typename T>
class BelowSideDiagonalOperation : public Operation
{
public:
    BelowSideDiagonalOperation() = default;

    explicit BelowSideDiagonalOperation(const std::vector<std::vector<T>>& matrix);

    void execute() override;

    T getMinValue() const;
    T getMaxValue() const;

    void setMinValue(T value);
    void setMaxValue(T value);

    std::string getResult() const;

private:
    std::vector<std::vector<T>> matrix;
    T minVal = std::numeric_limits<T>::max();
    T maxVal = std::numeric_limits<T>::min();
    std::string result;
};

#endif

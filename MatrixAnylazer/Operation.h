#ifndef OPERATION_H
#define OPERATION_H

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

class Operation {
protected:
    std::vector<std::vector<int>> matrix;
    std::string result;

public:
    Operation() = default;


    explicit Operation(const std::vector<std::vector<int>>& matrix) {
        setMatrix(matrix);
    }

    virtual ~Operation() = default;

    virtual void execute() = 0;

    void setMatrix(const std::vector<std::vector<int>>& matrix);

    std::string getResult() const { return result; }

    void clearResult() { result.clear(); }
};

#endif
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

template <typename T>
class Matrix
{
public:
    Matrix();

    void loadFromFile(const std::string &filename);
    void printToConsole() const;
    void printResultsToFile(const std::string &filename) const;

    const std::vector<std::vector<T>> &getData() const;
    int getSize() const;

private:
    int size;
    std::vector<std::vector<T>> data;

    bool hasTxtExtension(const std::string &filename) const;
};

#endif
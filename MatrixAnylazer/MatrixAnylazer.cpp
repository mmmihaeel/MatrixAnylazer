#include "Matrix.h"
#include "AboveMainDiagonalOperation.h"
#include "BelowMainDiagonalOperation.h"
#include "AboveSideDiagonalOperation.h"
#include "BelowSideDiagonalOperation.h"
#include "AboveMainDiagonalOperation.cpp"
#include "BelowMainDiagonalOperation.cpp"
#include "AboveSideDiagonalOperation.cpp"
#include "BelowSideDiagonalOperation.cpp"
#include <memory>
#include <iostream>
#include <vector>

template <typename T>
void processMatrix(const std::string& inputFilename, const std::string& outputFilename) {
    try {
        Matrix<T> matrix;
        matrix.loadFromFile(inputFilename);

        std::cout << "Matrix:\n";
        matrix.printToConsole();

  
        std::vector<std::unique_ptr<Operation>> operations;
        operations.push_back(std::make_unique<AboveMainDiagonalOperation<T>>(matrix.getData()));
        operations.push_back(std::make_unique<BelowMainDiagonalOperation<T>>(matrix.getData()));
        operations.push_back(std::make_unique<AboveSideDiagonalOperation<T>>(matrix.getData()));
        operations.push_back(std::make_unique<BelowSideDiagonalOperation<T>>(matrix.getData()));

        std::cout << "\nResults:\n";
        for (const auto& operation : operations) {
            operation->execute();
            std::cout << operation->getResult();
        }

        matrix.printResultsToFile(outputFilename);
        std::cout << "\nResults saved to " << outputFilename << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::string inputFilename, outputFilename;
    std::string typeChoice;

    std::cout << "Enter the matrix file name: ";
    std::cin >> inputFilename;

    std::cout << "Enter the output file name: ";
    std::cin >> outputFilename;

    std::cout << "Choose matrix type (int/double): ";
    std::cin >> typeChoice;

    if (typeChoice == "int") {
        processMatrix<int>(inputFilename, outputFilename);
    }
    else if (typeChoice == "double") {
        processMatrix<double>(inputFilename, outputFilename);
    }
    else {
        std::cerr << "Unsupported matrix type. Please choose 'int' or 'double'." << std::endl;
    }

    return 0;
}

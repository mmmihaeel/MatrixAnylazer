#include "gtest/gtest.h"
#include "Matrix.h"
#include "Matrix.cpp"
#include "AboveMainDiagonalOperation.h"
#include "BelowMainDiagonalOperation.h"
#include "AboveSideDiagonalOperation.h"
#include "BelowSideDiagonalOperation.h"
#include "AboveMainDiagonalOperation.cpp"
#include "BelowMainDiagonalOperation.cpp"
#include "AboveSideDiagonalOperation.cpp"
#include "BelowSideDiagonalOperation.cpp"
#include <algorithm>
#include <cctype>
#include <string>

std::string removeSpaces(const std::string& str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    ASSERT_TRUE(file.is_open());
    file << content;
    file.close();
}

TEST(MatrixTest, LoadValidMatrix) {
    createTestFile("matrix_valid.txt", "3\n1 2 3\n4 5 6\n7 8 9\n");

    Matrix<int> matrix;
    matrix.loadFromFile("matrix_valid.txt");
    EXPECT_EQ(matrix.getSize(), 3);
    EXPECT_EQ(matrix.getData()[0][0], 1);
    EXPECT_EQ(matrix.getData()[1][2], 6);
    EXPECT_EQ(matrix.getData()[2][2], 9);
}

TEST(MatrixTest, LoadValidDoubleMatrix) {
    createTestFile("matrix_valid_double.txt", "3\n1.1 2.2 3.3\n4.4 5.5 6.6\n7.7 8.8 9.9\n");

    Matrix<double> matrix;
    matrix.loadFromFile("matrix_valid_double.txt");
    EXPECT_EQ(matrix.getSize(), 3);
    EXPECT_DOUBLE_EQ(matrix.getData()[0][0], 1.1);
    EXPECT_DOUBLE_EQ(matrix.getData()[2][2], 9.9);
}

TEST(MatrixTest, LoadMatrixWithMissingRows) {
    createTestFile("matrix_missing_rows.txt", "3\n1 2 3\n4 5 6\n");

    Matrix<int> matrix;
    EXPECT_THROW(matrix.loadFromFile("matrix_missing_rows.txt"), std::runtime_error);
}

TEST(MatrixTest, LoadMatrixWithInvalidData) {
    createTestFile("matrix_invalid_data.txt", "3\n1 2 x\n4 5 6\n7 8 9\n");

    Matrix<int> matrix;
    EXPECT_THROW(matrix.loadFromFile("matrix_invalid_data.txt"), std::runtime_error);
}

TEST(MatrixTest, LoadMatrixWithNonSquareData) {
    createTestFile("matrix_non_square.txt", "3\n1 2\n4 5 6\n7 8 9\n");

    Matrix<int> matrix;
    EXPECT_THROW(matrix.loadFromFile("matrix_non_square.txt"), std::runtime_error);
}

std::string removeExtraSpaces(const std::string& input) {
    std::string result;
    bool inSpace = false;

    for (char c : input) {
        if (std::isspace(c)) {
            if (!inSpace && !result.empty()) {
                result += ' ';
            }
            inSpace = true;
        }
        else {
            result += c;
            inSpace = false;
        }
    }

    if (!result.empty() && std::isspace(result.back())) {
        result.pop_back();
    }

    return result;
}

TEST(MatrixTest, SaveMatrixToFile) {
    createTestFile("matrix_valid.txt", "3\n1 2 3\n4 5 6\n7 8 9\n");

    Matrix<int> matrix;
    matrix.loadFromFile("matrix_valid.txt");
    matrix.printResultsToFile("matrix_output.txt");

    std::ifstream file("matrix_output.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;

    std::getline(file, line);
    EXPECT_EQ(removeExtraSpaces(line), "Matrix:");

    std::getline(file, line);
    EXPECT_EQ(removeExtraSpaces(line), "1 2 3");

    std::getline(file, line);
    EXPECT_EQ(removeExtraSpaces(line), "4 5 6");

    std::getline(file, line);
    EXPECT_EQ(removeExtraSpaces(line), "7 8 9");

 
    file.close();
}

TEST(OperationTest, AboveMainDiagonal) {
    std::vector<std::vector<int>> data = { {1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9} };
    AboveMainDiagonalOperation<int> op(data);
    op.execute();
    EXPECT_EQ(op.getMinValue(), 2);
    EXPECT_EQ(op.getMaxValue(), 6);
}

TEST(OperationTest, BelowMainDiagonal) {
    std::vector<std::vector<int>> data = { {1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9} };
    BelowMainDiagonalOperation<int> op(data);
    op.execute();
    EXPECT_EQ(op.getMinValue(), 4);
    EXPECT_EQ(op.getMaxValue(), 8);
}

TEST(OperationTest, AboveSideDiagonal) {
    std::vector<std::vector<int>> data = { {1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9} };
    AboveSideDiagonalOperation<int> op(data);
    op.execute();
    EXPECT_EQ(op.getMinValue(), 3);
    EXPECT_EQ(op.getMaxValue(), 9);
}

TEST(OperationTest, BelowSideDiagonal) {
    std::vector<std::vector<int>> data = { {1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9} };
    BelowSideDiagonalOperation<int> op(data);
    op.execute();
    EXPECT_EQ(op.getMinValue(), 6);
    EXPECT_EQ(op.getMaxValue(), 9);
}

TEST(IntegrationTest, CreateAndValidateMatrixFile) {
    createTestFile("integration_matrix.txt", "3\n1 2 3\n4 5 6\n7 8 9\n");

    Matrix<int> matrix;
    ASSERT_NO_THROW(matrix.loadFromFile("integration_matrix.txt"));

    ASSERT_NO_THROW(matrix.printResultsToFile("integration_output.txt"));

    std::ifstream resultFile("integration_output.txt");
    ASSERT_TRUE(resultFile.is_open());

    std::string line;

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Matrix:"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("1 2 3"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("4 5 6"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("7 8 9"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces(""));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Results:"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Above Main Diagonal: Min = 2, Max = 6"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Below Main Diagonal: Min = 4, Max = 8"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Above Side Diagonal: Min = 1, Max = 4"));

    std::getline(resultFile, line);
    EXPECT_EQ(removeSpaces(line), removeSpaces("Below Side Diagonal: Min = 6, Max = 9"));

    resultFile.close();
}
# Matrix Analyzer

A C++ program to analyze square matrices loaded from a file. This program performs operations above and below both the main diagonal and the side diagonal of the matrix. It calculates the minimum and maximum values in these regions and saves the results to an output file.

## Features
- Load square matrices (integers or doubles) from a `.txt` file.
- Perform operations:
  - Above the main diagonal.
  - Below the main diagonal.
  - Above the side diagonal.
  - Below the side diagonal.
- Save results, including analyzed values and the matrix, to an output file.
- Supports both `int` and `double` matrix types.

## Getting Started

### Prerequisites
- A C++17-compatible compiler (e.g., g++ or clang).
- CMake (optional, for building).
- A matrix input file in `.txt` format.

### Matrix Input File Format
The first line specifies the size of the square matrix (N). The subsequent lines contain the matrix rows, with elements separated by spaces.

### Example:
3 1 2 3 4 5 6 7 8 9

## Building the Program

### Using Command Line
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/MatrixAnalyzer.git
   cd MatrixAnalyzer
   ```
Compile the program:

   ```bash
g++ -std=c++17 -o MatrixAnalyzer MatrixAnalyzer.cpp -I.
Run the program:
 ```
bash
   ```bash
./MatrixAnalyzer
 ```
### Using CMake
### Create a build directory:
 ```bash
mkdir build && cd build
 ```
G###enerate the build system:

 ```bash
cmake ..
 ```
Build the project:

```bash
cmake --build .
 ```
###Run the program:

```bash
./MatrixAnalyzer
 ```
###Usage
Prepare a matrix file (e.g., matrix.txt).
Run the program and provide the required inputs:
Input file name.
Output file name.
Matrix type (int or double).
Example Run:

```bash
Enter the matrix file name: matrix.txt
Enter the output file name: results.txt
Choose matrix type (int/double): int
File Structure
Matrix.h & Matrix.cpp: Core class for matrix loading and printing.
Operation.h & Operation.cpp: Abstract base class for matrix operations.
Diagonal Operation Files: Implementations of specific diagonal-based operations:
AboveMainDiagonalOperation.h/cpp
BelowMainDiagonalOperation.h/cpp
AboveSideDiagonalOperation.h/cpp
BelowSideDiagonalOperation.h/cpp
MatrixAnalyzer.cpp: Entry point of the program.
Output File
The output file contains:

The loaded matrix.
Results of the operations:
Minimum and maximum values for each region.
Example Output:

mathematica
Копіювати код
Matrix:
     1      2      3 
     4      5      6 
     7      8      9 

Results:
Above Main Diagonal: Min = 2, Max = 6
Below Main Diagonal: Min = 4, Max = 8
Above Side Diagonal: Min = 1, Max = 3
Below Side Diagonal: Min = 7, Max = 9
 ```
###Error Handling
Ensures the input matrix is square.
Validates input file existence and format.
Handles unsupported matrix types.
###Contributing
Fork the repository.
Create a feature branch:

```bash
git checkout -b feature-name
 ```
Commit your changes:

```bash
git commit -m "Add new feature"
 ```
Push to your branch:

```bash

git push origin feature-name
 ```
Open a pull request.
License
This project is licensed under the MIT License.

This is the entire text wrapped in markdown code formatting for your `README.md` file!

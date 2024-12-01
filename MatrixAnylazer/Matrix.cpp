#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix() : size(0) {}

template <typename T>
bool Matrix<T>::hasTxtExtension(const std::string &filename) const
{
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt";
}

template <typename T>
void Matrix<T>::loadFromFile(const std::string &filename)
{
    if (!hasTxtExtension(filename))
    {
        throw std::runtime_error("Invalid file type. Expected a .txt file.");
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    if (!std::getline(file, line))
    {
        throw std::runtime_error("Failed to read matrix size from file.");
    }

    try
    {
        size = std::stoi(line);
        if (size <= 0)
        {
            throw std::runtime_error("Matrix size must be positive.");
        }
    }
    catch (const std::exception &)
    {
        throw std::runtime_error("Invalid or missing matrix size in file: " + filename);
    }

    data.clear();
    data.resize(size, std::vector<T>(size));

    int rowCount = 0;
    while (std::getline(file, line) && rowCount < size)
    {
        std::istringstream rowStream(line);
        int colCount = 0;

        while (colCount < size)
        {
            std::string cell;
            if (!(rowStream >> cell))
            {
                throw std::runtime_error("Missing data at row " + std::to_string(rowCount + 1) + ", column " + std::to_string(colCount + 1));
            }

            try
            {
                if constexpr (std::is_same<T, double>::value)
                {
                    data[rowCount][colCount] = static_cast<T>(std::stod(cell));
                }
                else if constexpr (std::is_same<T, int>::value)
                {
                    data[rowCount][colCount] = static_cast<T>(std::stoi(cell));
                }
            }
            catch (const std::exception &)
            {
                throw std::runtime_error("Invalid data at row " + std::to_string(rowCount + 1) + ", column " + std::to_string(colCount + 1));
            }

            ++colCount;
        }

        if (colCount != size)
        {
            throw std::runtime_error("Row " + std::to_string(rowCount + 1) + " does not match matrix size.");
        }

        ++rowCount;
    }

    if (rowCount != size)
    {
        throw std::runtime_error("Number of rows does not match matrix size.");
    }

    file.close();
}

template <typename T>
void Matrix<T>::printToConsole() const
{
    for (const auto &row : data)
    {
        for (const auto &value : row)
        {
            std::cout << std::setw(6) << value << " ";
        }
        std::cout << "\n";
    }
}

template <typename T>
void Matrix<T>::printResultsToFile(const std::string &filename) const
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    outFile << "Matrix:\n";
    for (const auto &row : data)
    {
        for (const auto &value : row)
        {
            outFile << std::setw(6) << value << " ";
        }
        outFile << "\n";
    }
    outFile << "\n";

    T aboveMainMin = std::numeric_limits<T>::max();
    T aboveMainMax = std::numeric_limits<T>::min();
    T belowMainMin = std::numeric_limits<T>::max();
    T belowMainMax = std::numeric_limits<T>::min();
    T aboveSideMin = std::numeric_limits<T>::max();
    T aboveSideMax = std::numeric_limits<T>::min();
    T belowSideMin = std::numeric_limits<T>::max();
    T belowSideMax = std::numeric_limits<T>::min();

    int n = data.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i < j)
            {
                aboveMainMin = std::min(aboveMainMin, data[i][j]);
                aboveMainMax = std::max(aboveMainMax, data[i][j]);
            }
            if (i > j)
            {
                belowMainMin = std::min(belowMainMin, data[i][j]);
                belowMainMax = std::max(belowMainMax, data[i][j]);
            }
            if (i + j < n - 1)
            {
                aboveSideMin = std::min(aboveSideMin, data[i][j]);
                aboveSideMax = std::max(aboveSideMax, data[i][j]);
            }
            if (i + j > n - 1)
            {
                belowSideMin = std::min(belowSideMin, data[i][j]);
                belowSideMax = std::max(belowSideMax, data[i][j]);
            }
        }
    }

    outFile << "Results:\n";
    outFile << "Above Main Diagonal: Min = " << aboveMainMin << ", Max = " << aboveMainMax << "\n";
    outFile << "Below Main Diagonal: Min = " << belowMainMin << ", Max = " << belowMainMax << "\n";
    outFile << "Above Side Diagonal: Min = " << aboveSideMin << ", Max = " << aboveSideMax << "\n";
    outFile << "Below Side Diagonal: Min = " << belowSideMin << ", Max = " << belowSideMax << "\n";

    std::cout << "Matrix and calculations saved to file: " << filename << "\n";
}

template <typename T>
const std::vector<std::vector<T>> &Matrix<T>::getData() const
{
    return data;
}

template <typename T>
int Matrix<T>::getSize() const
{
    return size;
}

template class Matrix<int>;
template class Matrix<double>;

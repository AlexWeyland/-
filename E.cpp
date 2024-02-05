#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

using std::vector;
using std::string;

int toomuch = 100000000;

int Distance(const int &first, const int &second, const vector<int> &coordinates) {
    if (coordinates[second] > coordinates[first]) {
        return (coordinates[second] - coordinates[first]);
    } else {
        return (coordinates[first] - coordinates[second]);
    }
}

int CellCalculate(const int &row, const int &column,
                  vector<vector<int>> &matrix,
                  const vector<int> &coordinates,
                  const vector<int> &lifetime) {
    int first, second;
    if (row < column) {
        if (matrix[row][column - 1] == -57) {
            first = CellCalculate(row, column - 1, matrix, coordinates, lifetime);
        } else {
            first = matrix[row][column - 1];
        }
        if (matrix[column - 1][row] == -57) {
            second = CellCalculate(column - 1, row, matrix, coordinates, lifetime);
        } else {
            second = matrix[column - 1][row];
        }
        first += Distance(column - 1, column, coordinates);
        second += Distance(row, column, coordinates);
        if (std::min(first, second) > lifetime[column]) {
            matrix[row][column] = toomuch;
        } else {
            matrix[row][column] = std::min(first, second);
        }
    } else if (row == column) {
        matrix[row][column] = 0;
    } else {
        if (matrix[row][column + 1] == -57) {
            first = CellCalculate(row, column + 1, matrix, coordinates, lifetime);
        } else {
            first = matrix[row][column + 1];
        }
        if (matrix[column + 1][row] == -57) {
            second = CellCalculate(column + 1, row, matrix, coordinates, lifetime);
        } else {
            second = matrix[column + 1][row];
        }
        first += Distance(column + 1, column, coordinates);
        second += Distance(row, column, coordinates);
        if (std::min(first, second) > lifetime[column]) {
            matrix[row][column] = toomuch;
        } else {
            matrix[row][column] = std::min(first, second);
        }
    }
    return matrix[row][column];
}

int main() {
    int number;
    std::cin >> number;
    vector<int> coordinates;
    vector<int> lifetime;
    coordinates.reserve(number);
    lifetime.reserve(number);
    vector<std::pair<int, int>> input;
    input.resize(number);
    for (int coin = 0; coin < number; ++coin) {
        int coord, time;
        std::cin >> coord >> time;
        input[coin].first = coord;
        input[coin].second = time;
    }
    std::sort(input.begin(), input.end());
    for (int coin = 0; coin < number; ++coin) {
        coordinates.push_back(input[coin].first);
        lifetime.push_back(input[coin].second);
    }
    vector<vector<int> > matrix(
            number,
            std::vector<int>(number, -57));
    for (int diag = 0; diag < number; ++diag) {
        matrix[diag][diag] = 0;
    }
    int first = CellCalculate(0, number - 1, matrix, coordinates, lifetime);
    if (first > lifetime[number - 1]) {
        first = toomuch;
    }
    int second = CellCalculate(number - 1, 0, matrix, coordinates, lifetime);
    if (second > lifetime[0]) {
        second = toomuch;
    }
    int result = std::min(first, second);
    if (result < toomuch) {
        std::cout << result;
    } else {
        std::cout << "No solution";
    }
    return 0;
}

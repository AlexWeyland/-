#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>

using std::vector;

bool IsFit(const vector<vector<double>> &points_array,
           const int &kmin, const double &radius) {
    vector<double> leftends;
    vector<double> rightends;
    for (auto &point : points_array) {
        if (abs(point[1]) <= radius) {
            double leftelement = point[0] -
                                 sqrt(abs(std::pow(radius, 2) - std::pow(point[1], 2)));
            leftends.push_back(leftelement);
            double rightelement = point[0] +
                                  sqrt(abs(std::pow(radius, 2) - std::pow(point[1], 2)));
            rightends.push_back(rightelement);
        }
    }
    if (static_cast<int>(leftends.size()) < kmin) {
        return false;
    }
    std::sort(leftends.begin(), leftends.end());
    std::sort(rightends.begin(), rightends.end());
    size_t left_index = 0;
    size_t right_index = 0;
    int res = 0;
    while ((res < kmin) &&
           (left_index < leftends.size()) && (right_index < rightends.size())) {
        if (leftends[left_index] <= rightends[right_index]) {
            ++res;
            ++left_index;
        } else {
            --res;
            ++right_index;
        }
    }
    if (res == kmin) {
        return true;
    } else {
        return false;
    }
}

double MinRadius(const vector<vector<double>> &points_array, const int &kmin) {
    double minradius = 0;
    double maxradius = 1415;
    double midradius = minradius + (maxradius - minradius) / 2;
    while (maxradius - minradius > 0.0009) {
        if (IsFit(points_array, kmin, midradius) == false) {
            minradius = midradius;
            midradius = minradius + (maxradius - minradius) / 2;
        } else {
            maxradius = midradius;
            midradius = minradius + (maxradius - minradius) / 2;
        }
    }
    return midradius;
}

int main() {
//    std::cin.tie(nullptr);
    int number, kmin;
    std::cin >> number >> kmin;

    vector<std::vector<double>> points_array(
            number, vector<double>(2, 0));

    for (auto &point : points_array) {
        for (auto &cordinate : point) {
            std::cin >> cordinate;
        }
    }
    const double &radius = MinRadius(points_array, kmin);
    std::cout << std::fixed << std::setprecision(6) << radius;
    return 0;
}

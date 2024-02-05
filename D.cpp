#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

unsigned int cur = 0;

unsigned int nextRand24(int a_random, int b_random) {
    cur = cur * a_random + b_random;
    return cur >> 8;
}

unsigned int nextRand32(int a_random, int b_random) {
    unsigned int x_var = nextRand24(a_random, b_random),
            y_var = nextRand24(a_random, b_random);
    return (x_var << 8) ^ y_var;
}

unsigned int RandomSelect(const vector<unsigned int> &sequence, size_t key) {
    if (sequence.size() > 1) {
        vector<unsigned int> less;
        less.reserve(sequence.size());
        vector<unsigned int> equal;
        equal.reserve(sequence.size());
        vector<unsigned int> greater;
        greater.reserve(sequence.size());
        size_t mid = rand() % sequence.size();
        unsigned int pivot = sequence[mid];
        for (auto elem : sequence) {
            if (elem < pivot) {
                less.push_back(elem);
            } else if (elem == pivot) {
                equal.push_back(elem);
            } else {
                greater.push_back(elem);
            }
        }
        if (key <= less.size()) {
            return RandomSelect(less, key);
        } else if (key > equal.size() + less.size()) {
            return RandomSelect(greater, key - equal.size() - less.size());
        } else {
            return equal[0];
        }
    } else {
        return sequence[0];
    }
}

int main() {
    int number;
    std::cin >> number;
    int a_random, b_random;
    std::cin >> a_random >> b_random;
    vector<unsigned int> houses;
    houses.reserve(number);
    for (int index = 0; index < number; ++index) {
        houses.push_back(nextRand32(a_random, b_random));
    }
    int64_t sum = 0;
    unsigned int ymin = RandomSelect(houses, houses.size() / 2 + 1);

    for (auto elem : houses) {
        if (ymin > elem) {
            sum += ymin - elem;
        } else {
            sum += elem - ymin;
        }
    }
    std::cout << sum;
    return 0;
}

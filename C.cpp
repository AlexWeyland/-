#include <vector>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int numb, mumb, size;
    std::cin >> numb >> mumb >> size;

    std::vector<std::vector<int> > increase_array(
            numb,
            std::vector<int>(size, 0));

    for (auto &array : increase_array) {
        for (auto &elem : array) {
            std::cin >> elem;
        }
    }

    std::vector<std::vector<int> > decrease_array(
            mumb,
            std::vector<int>(size, 0));
    for (auto &array : decrease_array) {
        for (auto &elem : array) {
            std::cin >> elem;
        }
    }

    int number_of_comands;
    std::cin >> number_of_comands;


    for (int konch = 0; konch < number_of_comands; ++konch) {
        int one, two;
        std::cin >> one >> two;

        int first = 0;
        int last = size - 1;
        while (last - first > 1) {
            int mid = first + (last - first) / 2;
            if ((increase_array[one - 1][mid] < decrease_array[two - 1][mid])) {
                first = mid;
            } else {
                last = mid;
            }
        }
        if ((increase_array[one - 1][last] > decrease_array[two - 1][first])) {
            std::cout << first + 1 << "\n";
        } else {
            std::cout << last + 1 << "\n";
        }
    }

    return 0;
}

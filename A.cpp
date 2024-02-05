#include <vector>
#include <iostream>

using std::vector;

vector<int> Input() {
    vector<int> sequence;
    size_t len;
    std::cin >> len;
    sequence.reserve(len);
    for (size_t k = 0; k < len; ++k) {
        int number;
        std::cin >> number;
        sequence.push_back(number);
    }
    return sequence;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const vector<int> sequence = Input();

    vector<int> stack;
    stack.reserve(sequence.size());
    stack.push_back(sequence[0]);

    size_t rindex = 0;
    size_t lindex = 0;
    size_t index = 0;

    int numberofsteps;
    std::cin >> numberofsteps;

    for (int step = 0; step < numberofsteps; ++step) {
        char command;
        std::cin >> command;
        if (command == 'R') {
            ++rindex;
            while (stack.size() > 0 && sequence[rindex] > stack.back()) {
                stack.pop_back();
            }
            if (index > stack.size()) {
                index = stack.size();
            }
            stack.push_back(sequence[rindex]);
            std::cout << stack[index] << " ";
        } else if (command == 'L') {
            if (sequence[lindex] == stack[index]) {
                ++index;
            }
            ++lindex;
            std::cout << stack[index] << " ";
        }
    }
    return 0;
}

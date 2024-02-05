#include <vector>
#include <iostream>

using std::vector;

vector<int> Input() {
    vector<int> sequence;
    size_t len;
    std::cin >> len;
    sequence.reserve(len);
    int pred;
    std::cin >> pred;
    sequence.push_back(pred);
    for (size_t k = 1; k < len; ++k) {
        int number;
        std::cin >> number;
        if (pred != number) {
            sequence.push_back(number);
        }
        pred = number;
    }
    return sequence;
}

void Output(const vector<int> &sequence) {
    for (const auto &number : sequence) {
        std::cout << number << " ";
    }
}

vector<int> Findtremums(const vector<int> &sequence) {
    vector<int> extremums;
    extremums.reserve(sequence.size());
    extremums.push_back(0);
    int sequence_size = sequence.size();
    if (sequence.size() > 1) {
        for (int ind = 0; ind + 2 < sequence_size; ++ind) {
            if ((sequence[ind + 1] > sequence[ind] &&
                 sequence[ind + 1] > sequence[ind + 2]) ||
                (sequence[ind + 1] < sequence[ind] &&
                 sequence[ind + 1] < sequence[ind + 2])) {
                extremums.push_back(ind + 1);
            }
        }
        extremums.push_back(sequence.size() - 1);
    }
    return extremums;
}


int main() {
    const vector<int> sequence = Input();
    const vector<int> extremums = Findtremums(sequence);

    vector<int> newextremums;
    newextremums.reserve(extremums.size());
    for (const auto &ind : extremums) {
        newextremums.push_back(sequence[ind]);
    }
    for (size_t ind = 0; ind + 2 < extremums.size(); ++ind) {
        for (int kek = extremums[ind]; kek < extremums[ind + 1]; ++kek) {
            if (sequence[extremums[ind + 1]] < sequence[extremums[ind]]) {
                if (sequence[kek] < sequence[extremums[ind + 2]] &&
                    sequence[kek] < newextremums[ind]) {
                    newextremums[ind + 1] = sequence[kek];
                    break;
                }
            } else {
                if (sequence[kek] > sequence[extremums[ind + 2]] &&
                    sequence[kek] > newextremums[ind]) {
                    newextremums[ind + 1] = sequence[kek];
                    break;
                }
            }
        }
    }
    if (extremums.size() > 1) {
        if (sequence[extremums[extremums.size() - 1]] >
            sequence[extremums[extremums.size() - 2]]) {
            for (size_t kek = extremums[extremums.size() - 2]; kek < sequence.size(); ++kek) {
                if (sequence[kek] > newextremums[extremums.size() - 2]) {
                    newextremums[extremums.size() - 1] = sequence[kek];
                    break;
                }
            }
        } else {
            for (size_t kek = extremums[extremums.size() - 2]; kek < sequence.size(); ++kek) {
                if (sequence[kek] < newextremums[extremums.size() - 2]) {
                    newextremums[extremums.size() - 1] = sequence[kek];
                    break;
                }
            }
        }
    }
    Output(newextremums);
    return 0;
}

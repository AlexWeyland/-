#include <iostream>
#include <vector>
#include <math.h>

using std::vector;
int bigint = 2000000000;

vector<int> Input(const int &len) {
    vector<int> sequence;
    sequence.reserve(len);
    for (int elem = 0; elem < len; ++elem) {
        int number;
        std::cin >> number;
        sequence.push_back(number);
    }
    return sequence;
}

void Merge(const vector<int> &sequence, vector<int> &sequence_sample,
           const size_t &index, const size_t &scale) {
    size_t first = index;
    size_t second = index + scale;
    size_t num = index;
    while (first < index + scale && second < index + 2 * scale) {
        if (sequence[first] <= sequence[second]) {
            sequence_sample[num] = sequence[first];
            ++first;
        } else {
            sequence_sample[num] = sequence[second];
            ++second;
        }
        ++num;
    }
    while (first < index + scale) {
        sequence_sample[num] = sequence[first];
        ++first;
        ++num;
    }
    while (second < index + 2 * scale) {
        sequence_sample[num] = sequence[second];
        ++second;
        ++num;
    }
}

void Output(const vector<int> &sequence) {
    for (auto elem : sequence) {
        std::cout << elem << " ";
    }
}

void MergeSort(vector<int> &sequence, const int &size, const int &twopow) {
    vector<int> sequence_sample;
    sequence_sample.resize(sequence.size());
    for (size_t scale = size; scale < sequence.size(); scale *= 2) {
        for (size_t index = 0; index < sequence.size(); index += 2 * scale) {
            Merge(sequence, sequence_sample, index, scale);
        }
        sequence = sequence_sample;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number;
    int size;
    std::cin >> number >> size;
    vector<int> sequence = Input(number * size);
    int twopow = 0;
    while (pow(2, twopow) < number) {
        ++twopow;
    }
    for (int index = 0; index < (pow(2, twopow) - number) * size; ++index) {
        sequence.push_back(bigint);
    }
    MergeSort(sequence, size, twopow);
    for (int index = 0; index < (pow(2, twopow) - number) * size; ++index) {
        sequence.pop_back();
    }
    Output(sequence);
    return 0;
}

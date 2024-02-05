#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using std::vector;

class MinHeap {
private:
    vector<int> tree_;
    vector<size_t> items_;
    vector<size_t> positions_;
    size_t scale_ = 0;

public:
    void MemoryReserve(const size_t &length) {
        tree_.reserve(length);
        items_.reserve(length);
        positions_.resize(length);
        scale_ = 0;
    }

    void Add(const int &number, const size_t &item) {
        tree_.push_back(number);
        items_.push_back(item);
        positions_[item] = scale_;
        size_t index = scale_;
        ++scale_;
        while (index > 0 && tree_[index] < tree_[(index - 1) / 2]) {
            std::swap(tree_[index], tree_[(index - 1) / 2]);
            std::swap(items_[index], items_[(index - 1) / 2]);
            std::swap(positions_[items_[index]], positions_[items_[(index - 1) / 2]]);
            index = (index - 1) / 2;
        }
    }

    int MinValue() {
        return tree_.front();
    }
    
    void Swap(const size_t &first, const size_t &second) {
        std::swap(tree_[first], tree_[second]);
        std::swap(items_[first], items_[second]);
        std::swap(positions_[items_[first]], positions_[items_[second]]);
    }

    void Delete(const size_t &item) {
        if (item == items_.back()) {
            tree_.pop_back();
            items_.pop_back();
            --scale_;
        } else {
            size_t item_to_del = positions_[item];
            Swap(scale_ - 1, item_to_del);
            tree_.pop_back();
            items_.pop_back();
            --scale_;
            if (tree_.size() > 1) {
                size_t index = item_to_del;
                size_t pred_index = (index - 1) / 2;
                size_t next_index = 2 * index + 1;
                if (next_index + 1 < scale_ && tree_[next_index] > tree_[next_index + 1]) {
                    ++next_index;
                }
                if (index > 0 && tree_[index] < tree_[pred_index]) {
                    while (index > 0 && tree_[index] < tree_[pred_index]) {
                        Swap(index, pred_index);
                        index = pred_index;
                        pred_index = (pred_index - 1) / 2;
                    }
                } else {
                    while (next_index < scale_ && tree_[index] > tree_[next_index]) {
                        Swap(index, next_index);
                        index = next_index;
                        next_index = 2 * index + 1;
                        if (next_index + 1 < scale_ && tree_[next_index] > tree_[next_index + 1]) {
                            ++next_index;
                        }
                    }
                }
            }
        }
    }

    int Size() {
        return scale_;
    }

    size_t MinIndex() {
        return items_.front();
    }

    void PrintHeap() {
        for (const auto &elem : tree_) {
            std::cout << elem << " ";
        }
    }
};

class MaxHeap {
private:
    vector<int> tree_;
    vector<size_t> items_;
    vector<size_t> positions_;
    size_t scale_ = 0;

public:
    void MemoryReserve(const size_t &length) {
        tree_.reserve(length);
        items_.reserve(length);
        positions_.resize(length);
        scale_ = 0;
    }

    void Swap(const size_t &first, const size_t &second) {
        std::swap(tree_[first], tree_[second]);
        std::swap(items_[first], items_[second]);
        std::swap(positions_[items_[first]], positions_[items_[second]]);
    }

    void Add(const int &number, const size_t &item) {
        tree_.push_back(number);
        items_.push_back(item);
        positions_[item] = scale_;
        size_t index = scale_;
        ++scale_;
        while (index > 0 && tree_[index] > tree_[(index - 1) / 2]) {
            std::swap(tree_[index], tree_[(index - 1) / 2]);
            std::swap(items_[index], items_[(index - 1) / 2]);
            std::swap(positions_[items_[index]], positions_[items_[(index - 1) / 2]]);
            index = (index - 1) / 2;
        }
    }

    int MaxValue() {
        return tree_.front();
    }

    void Delete(const size_t &item) {
        if (item == items_.back()) {
            tree_.pop_back();
            items_.pop_back();
            --scale_;
        } else {
            size_t item_to_del = positions_[item];
            Swap(scale_ - 1, item_to_del);
            tree_.pop_back();
            items_.pop_back();
            --scale_;
            if (tree_.size() > 1) {
                size_t index = item_to_del;
                size_t pred_index = (index - 1) / 2;
                size_t next_index = 2 * index + 1;
                if (next_index + 1 < scale_ && tree_[next_index] < tree_[next_index + 1]) {
                    ++next_index;
                }
                if (index > 0 && tree_[index] > tree_[pred_index]) {
                    while (index > 0 && tree_[index] > tree_[pred_index]) {
                        Swap(index, pred_index);
                        index = pred_index;
                        pred_index = (pred_index - 1) / 2;
                    }
                } else {
                    while (next_index < scale_ && tree_[index] < tree_[next_index]) {
                        Swap(index, next_index);
                        index = next_index;
                        next_index = 2 * index + 1;
                        if (next_index + 1 < scale_ && tree_[next_index] < tree_[next_index + 1]) {
                            ++next_index;
                        }
                    }
                }
            }
        }
    }

    int Size() {
        return scale_;
    }

    size_t MaxIndex() {
        return items_.front();
    }

    void PrintHeap() {
        for (const auto &elem : tree_) {
            std::cout << elem << " ";
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int len, number_of_comands, order;
    std::cin >> len >> number_of_comands >> order;
    vector<int> sequence;
    sequence.resize(len);
    for (auto &element : sequence) {
        std::cin >> element;
    }

    MinHeap heap_min;
    heap_min.MemoryReserve(len);
    MaxHeap heap_max;
    heap_max.MemoryReserve(len);
    heap_max.Add(sequence[0], 0);
    size_t right = 0;
    size_t left = 0;

    vector<char> wherewego;
    wherewego.resize(len);
    wherewego[0] = 'x';


    std::string commands;
    std::cin >> commands;
    for (int index = 0; index < number_of_comands; ++index) {
        if (commands[index] == 'R') {
            ++right;
            if (heap_max.Size() < order) {
                heap_max.Add(sequence[right], right);
                wherewego[right] = 'x';
            } else {
                if (heap_max.MaxValue() > sequence[right]) {
                    heap_min.Add(heap_max.MaxValue(), heap_max.MaxIndex());
                    wherewego[heap_max.MaxIndex()] = 'n';
                    heap_max.Delete(heap_max.MaxIndex());
                    heap_max.Add(sequence[right], right);
                    wherewego[right] = 'x';
                } else {
                    heap_min.Add(sequence[right], right);
                    wherewego[right] = 'n';
                }
            }
        } else if (commands[index] == 'L') {
            if (wherewego[left] == 'x') {
                heap_max.Delete(left);
                if (heap_min.Size() > 0) {
                    heap_max.Add(heap_min.MinValue(), heap_min.MinIndex());
                    wherewego[heap_min.MinIndex()] = 'x';
                    heap_min.Delete(heap_min.MinIndex());
                }
            } else {
                heap_min.Delete(left);
            }
            ++left;
        }
        if (heap_max.Size() == order) {
            std::cout << heap_max.MaxValue() << "\n";
        } else {
            std::cout << -1 << "\n";
        }
    }
    return 0;
}

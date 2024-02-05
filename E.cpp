#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>

using std::vector;

int64_t GCF(const int64_t &first, const int64_t &second) {
    int64_t remainder = first % second;
    if (remainder == 0) {
        return second;
    } else {
        return GCF(second, remainder);
    }
}

void TriangleTransform(vector<int64_t> &triangle) {
    std::sort(triangle.begin(), triangle.end());
    int64_t gcf = GCF(triangle[2], GCF(triangle[1], triangle[0]));
    for (auto &side : triangle) {
        side = side / gcf;
    }
}

class FixedSet {
private:
    int64_t length_ = 0;
    int64_t transposition_ = 0;
    int64_t expansion_ = 0;
    vector<vector<int64_t>> hash_table_;

public:
    void Initialize(const int &number) {
        length_ = 3000017;
        transposition_ = 1757;
        expansion_ = 7;
        int hash_size = 2 * number + 13;
        hash_table_.resize(hash_size, vector<int64_t>(1, 0));
    }

    void Add(const vector<int64_t> &triangle) {
        size_t hash_size = hash_table_.size();
        int64_t polinom = 17 * triangle[1] + 3 *  triangle[2] + 5 * triangle[0] + 10;
        size_t function = (std::abs(expansion_ * polinom + transposition_) % length_) % hash_size;
        hash_table_[function].push_back(triangle[0] + triangle[1] + triangle[2]);
    }

    bool Contains(const vector<int64_t> &triangle) const {
        size_t hash_size = hash_table_.size();
        int64_t polinom = 17 * triangle[1] + 3 * triangle[2] + 5 * triangle[0] + 10;
        int64_t perimetr = triangle[0] + triangle[1] + triangle[2];
        size_t function = (std::abs(expansion_ * polinom + transposition_) % length_) % hash_size;
        for (size_t index = 1; index < hash_table_[function].size(); ++index) {
            if (hash_table_[function][index] == perimetr) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number;
    int sum = 0;
    std::cin >> number;
    FixedSet triangle_hash;
    triangle_hash.Initialize(number);
    for (int index = 0; index < number; ++index) {
        vector<int64_t> triangle;
        triangle.resize(3, 0);
        for (auto &side : triangle) {
            std::cin >> side;
        }
        TriangleTransform(triangle);
        if (!triangle_hash.Contains(triangle)) {
            triangle_hash.Add(triangle);
            ++sum;
        }
    }
    std::cout << sum;
    return 0;
}

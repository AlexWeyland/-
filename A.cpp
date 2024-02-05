#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <optional>

using std::optional;

int64_t FindSquareSum(const std::vector<int> &container) {
    int64_t square_sum = 0;
    for (const auto &vec_size : container) {
        square_sum += static_cast<int64_t>(vec_size) * static_cast<int64_t>(vec_size);
    }
    return square_sum;
}

class HashFunction {
public:
    HashFunction(int offset, int shift, int64_t prime_number) : \
            shift_(shift), offset_(offset), prime_number_(prime_number) {}

    int64_t operator()(int number) const;

private:
    int64_t shift_ = 0;
    int64_t offset_ = 0;
    int64_t prime_number_ = 0;
};

int64_t HashFunction::operator()(const int number) const {
    int64_t hash = (((static_cast<int64_t>(shift_) * number + offset_\
                    + prime_number_) % prime_number_)\
                    + prime_number_) % prime_number_;

    return hash;
}

class HashTable {
public:
    HashTable();

    void Initialize(const std::vector<int> &numbers, std::mt19937 &generator,
                    int64_t prime_number);

    [[nodiscard]] bool Contains(int request) const;

private:
    HashFunction hash_function_;
    std::vector <optional<int>> hashes_table_;

    [[nodiscard]] bool CheckHashIsOk(const std::vector<int> &numbers) const;

    std::vector <optional<int>> CreateHashes(const std::vector<int> &numbers);
};

class FixedSet {
public:
    int64_t kPrimeNumber = 2147483647;

    FixedSet();

    [[nodiscard]] bool Contains(int value) const;

    void Initialize(const std::vector<int> &numbers_input);

private:
    HashFunction hash_function_;
    std::vector <HashTable> hashes_;

    [[nodiscard]] bool AnyCollisions(const std::vector<int> &numbers) const;

    void CreateHashes(const std::vector<int> &numbers, std::mt19937 *generator);
};

FixedSet::FixedSet()
        : hash_function_(0, 0, 0) {
}

HashTable::HashTable()
        : hash_function_(0, 0, 0) {
}

HashFunction Generate(std::mt19937 *generator,
                          const int64_t prime_number = 2147483647) {
    std::uniform_int_distribution<> distr_offset(0, prime_number);
    std::uniform_int_distribution<> distr_shift(1, prime_number);
    return HashFunction(distr_offset(*generator), distr_shift(*generator), prime_number);
}

void HashTable::Initialize(const std::vector<int> &numbers, std::mt19937 &outer_generator,
                                int64_t prime_number) {
    do {
        hash_function_ = Generate(&outer_generator, prime_number);
    } while (not CheckHashIsOk(numbers));
    hashes_table_ = CreateHashes(numbers);
}

bool HashTable::Contains(int request) const {
    if (hashes_table_.empty()) {
        return false;
    }
    size_t hash_number = hash_function_(request) % hashes_table_.size();
    return hashes_table_[hash_number] == request;
}

std::vector <optional<int>> HashTable::CreateHashes(const std::vector<int> &numbers) {
    auto answer = std::vector<optional<int>> (numbers.size() * numbers.size());

    int64_t hash_number;

    for (auto number : numbers) {
        hash_number = hash_function_(number) % answer.size();
        answer[hash_number] = number;
    }
    return answer;
}

void FixedSet::Initialize(const std::vector<int> &numbers_input) {
    hashes_.clear();

    std::mt19937 generator(42);

    hashes_.resize(numbers_input.size());
    do {
        hash_function_ = Generate(&generator, kPrimeNumber);
    } while (not AnyCollisions(numbers_input));
    CreateHashes(numbers_input, &generator);
}

bool FixedSet::Contains(int value) const {
    if (hashes_.empty()) {
        return false;
    }
    int64_t hash_number = hash_function_(value) % hashes_.size();
    HashTable hash_table = hashes_[hash_number];

    return hash_table.Contains(value);
}

bool FixedSet::AnyCollisions(const std::vector<int> &numbers) const {
    std::vector<int> hash_test(hashes_.size(), 0);
    int64_t hash_number;

    for (auto number : numbers) {
        hash_number = hash_function_(number) % hashes_.size();
        ++hash_test[hash_number];
    }

    return FindSquareSum(hash_test) <= static_cast<int64_t> (hashes_.size() * 4);
}

void FixedSet::CreateHashes(const std::vector<int> &numbers, std::mt19937 *generator) {
    std::vector <std::vector<int>> hashh(hashes_.size());
    int64_t hash_number;

    for (auto number : numbers) {
        hash_number = hash_function_(number) % hashes_.size();
        hashh[hash_number].push_back(number);
    }

    for (size_t index= 0; index < hashes_.size(); ++index) {
        auto possible_hash = hashh[index];
        if (not possible_hash.empty()) {
            hashes_[index] = HashTable();
            hashes_[index].Initialize(possible_hash, *generator, kPrimeNumber);
        }
    }
}

bool HashTable::CheckHashIsOk(const std::vector<int> &numbers) const {
    int64_t hash_number;
    int64_t newsize = numbers.size() * numbers.size();

    std::vector <optional<int>> test_hashes(newsize);
    for (auto number : numbers) {
        hash_number = hash_function_(number) % newsize;
        if (test_hashes[hash_number]) {
            return test_hashes[hash_number] == number;
        } else {
            test_hashes[hash_number] = number;
        }
    }
    return true;
}

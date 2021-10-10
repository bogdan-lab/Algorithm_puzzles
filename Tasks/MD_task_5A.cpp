#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <vector>

class Set {
 public:
  Set() : data_(INITIAL_SIZE, EMPTY_BUCKET) {}

  void Insert(int val) {
    size_t start_idx = Hash(val, data_.size());
    size_t end_idx = FindElement(val, data_);
    if (data_[end_idx] == val) return;
    size_t idx = start_idx;
    while (idx != end_idx && data_[idx] != DELETED_ELEMENT) {
      idx = Next(idx, data_.size());
    }
    if (data_[idx] == DELETED_ELEMENT) {
      data_[idx] = val;
      return;
    }
    data_[idx] = val;
    ++num_elements_inside_;
    if (num_elements_inside_ >= data_.size() / 2) {
      Rehash(2 * data_.size());
    }
  }

  void Delete(int val) {
    auto idx = FindElement(val, data_);
    if (data_[idx] == EMPTY_BUCKET) return;
    if (data_[Next(idx, data_.size())] == EMPTY_BUCKET) {
      data_[idx] = EMPTY_BUCKET;
      --num_elements_inside_;
      if (num_elements_inside_ <= data_.size() / 8 &&
          data_.size() > 2 * INITIAL_SIZE) {
        Rehash(data_.size() / 2);
      }
    } else {
      data_[idx] = DELETED_ELEMENT;
    }
  }

  bool Exists(int val) const {
    return data_[FindElement(val, data_)] != EMPTY_BUCKET;
  }

 private:
  static size_t FindElement(int val, const std::vector<int>& buff) {
    size_t idx = Hash(val, buff.size());
    while (buff[idx] != val && buff[idx] != EMPTY_BUCKET) {
      idx = Next(idx, buff.size());
    }
    return idx;
  }

  static size_t Hash(int val, size_t buff_size) {
    uint64_t exp_val = NEGATIVE_COMPENSATOR + static_cast<int64_t>(val);
    uint64_t res = (A_HASH * exp_val) % P_HASH;
    return res % buff_size;
  }

  void Rehash(size_t new_size) {
    std::vector<int> new_data(new_size, EMPTY_BUCKET);
    num_elements_inside_ = 0;
    for (const auto& el : data_) {
      if (el != EMPTY_BUCKET && el != DELETED_ELEMENT) {
        new_data[FindElement(el, new_data)] = el;
        ++num_elements_inside_;
      }
    }
    data_.swap(new_data);
  }

  static size_t Next(size_t idx, size_t buff_size) {
    return idx + 1 == buff_size ? 0 : idx + 1;
  }

  static constexpr int DELETED_ELEMENT = std::numeric_limits<int>::max();
  static constexpr int EMPTY_BUCKET = std::numeric_limits<int>::min();
  static constexpr int P_HASH = 1'000'000'007;
  static constexpr int A_HASH = 9973;
  static constexpr int NEGATIVE_COMPENSATOR = 1'000'000'001;
  static constexpr size_t INITIAL_SIZE = 2;

  std::vector<int> data_;
  size_t num_elements_inside_ = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string command;
  int val;
  Set set;
  while (input >> command >> val) {
    if (command == "insert") {
      set.Insert(val);
    } else if (command == "exists") {
      std::cout << (set.Exists(val) ? "true" : "false") << '\n';
    } else {
      set.Delete(val);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(insert 2
insert 5
insert 3
exists 2
exists 4
insert 2
delete 2
exists 2
)";
    Solution(ss);
    std::cout << "expected = true false false\n";
  }
  {
    std::stringstream ss;
    for (size_t i = 0; i < 20; ++i) {
      ss << "insert " << i << '\n';
    }
    for (size_t i = 5; i < 26; ++i) {
      ss << "delete " << i << '\n';
    }
    for (size_t i = 10; i < 20; ++i) {
      ss << "insert " << i << '\n';
    }
    for (size_t i = 0; i < 20; ++i) {
      ss << "exists " << i << '\n';
    }
    Solution(ss);
  }
}

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

class Map {
  struct Item;

 public:
  using ValueType = std::vector<std::list<Item>>;

  Map() : data_(INITIAL_SIZE) {}

  void Put(const std::string& key, const std::string& val) {
    size_t idx = Hash(key, data_.size());
    auto key_it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    if (key_it != data_[idx].end()) {
      auto val_it =
          std::find(key_it->values.begin(), key_it->values.end(), val);
      if (val_it == key_it->values.end()) {
        key_it->values.push_back(val);
      }
      return;
    }
    data_[idx].emplace_back(key, val);
    ++num_elements_;
    if (num_elements_ == data_.size()) {
      Rehash(2 * data_.size());
    }
  }

  void Delete(const std::string& key, const std::string& val) {
    size_t idx = Hash(key, data_.size());
    auto key_it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    if (key_it == data_[idx].end()) return;

    auto val_it = std::find(key_it->values.begin(), key_it->values.end(), val);
    if (val_it == key_it->values.end()) return;

    key_it->values.erase(val_it);
    if (key_it->values.empty()) {
      --num_elements_;
      data_[idx].erase(key_it);
      if (num_elements_ <= data_.size() / 4 &&
          data_.size() > 2 * INITIAL_SIZE) {
        Rehash(data_.size() / 2);
      }
    }
  }

  void DeleteAll(const std::string& key) {
    size_t idx = Hash(key, data_.size());
    auto key_it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    if (key_it == data_[idx].end()) return;
    data_[idx].erase(key_it);
    --num_elements_;
    if (num_elements_ <= data_.size() / 4 && data_.size() > 2 * INITIAL_SIZE) {
      Rehash(data_.size() / 2);
    }
  }

  std::list<std::string> Get(const std::string& key) const {
    size_t idx = Hash(key, data_.size());
    auto key_it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    if (key_it == data_[idx].end()) return {};
    return key_it->values;
  }

 private:
  struct Item {
    std::string key;
    std::list<std::string> values;
    Item(const std::string& gk, const std::string& val) : key(gk) {
      values.push_back(val);
    }
  };

  static size_t Hash(const std::string& str, size_t buff_size) {
    uint64_t res = 0;
    for (const auto& el : str) {
      res = (res * A_HASH + el - 'a') % P_HASH;
    }
    return res % buff_size;
  }

  void Rehash(size_t new_size) {
    ValueType new_data(new_size);
    for (const auto& bucket : data_) {
      for (const auto& el : bucket) {
        new_data[Hash(el.key, new_size)].push_back(el);
      }
    }
    data_.swap(new_data);
  }

  static constexpr int INITIAL_SIZE = 2;
  static constexpr size_t P_HASH = 1'000'000'007;
  static constexpr size_t A_HASH = 9973;

  ValueType data_;
  size_t num_elements_ = 0;
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
  Map map;
  while (input >> command) {
    if (command == "put") {
      std::string key;
      std::string value;
      input >> key >> value;
      map.Put(key, value);
    } else if (command == "get") {
      std::string key;
      input >> key;
      const auto& res = map.Get(key);
      std::cout << res.size();
      for (const auto& el : res) {
        std::cout << ' ' << el;
      }
      std::cout << '\n';
    } else if (command == "deleteall") {
      std::string key;
      input >> key;
      map.DeleteAll(key);
    } else {
      std::string key;
      std::string val;
      input >> key >> val;
      map.Delete(key, val);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(put a a
put a b
put a c
get a
delete a b
get a
deleteall a
get a
)";
    Solution(ss);
    std::cout << "expected = 3 a b c ; 2 a c ; 0\n";
  }
}

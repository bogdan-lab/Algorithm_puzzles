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
    num_elements_ += PutElement({key, val}, data_);
    if (num_elements_ == data_.size()) {
      Rehash(2 * data_.size());
    }
  }

  void Delete(const std::string& key) {
    size_t idx = Hash(key, data_.size());
    auto it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    if (it == data_[idx].end()) return;
    data_[idx].erase(it);
    --num_elements_;
    if (num_elements_ <= data_.size() / 4 && data_.size() > 2 * INITIAL_SIZE) {
      Rehash(data_.size() / 2);
    }
  }

  std::string Get(const std::string& key) const {
    size_t idx = Hash(key, data_.size());
    auto it =
        std::find_if(data_[idx].begin(), data_[idx].end(),
                     [&key](const Item& item) { return item.key == key; });
    return it == data_[idx].end() ? "none" : it->value;
  }

 private:
  struct Item {
    std::string key;
    std::string value;
  };

  static bool PutElement(const Item& new_item, ValueType& buff) {
    size_t idx = Hash(new_item.key, buff.size());
    auto it = std::find_if(
        buff[idx].begin(), buff[idx].end(),
        [&new_item](const Item& item) { return item.key == new_item.key; });
    if (it == buff[idx].end()) {
      buff[idx].push_back(new_item);
      return true;
    }
    it->value = new_item.value;
    return false;
  }

  static size_t Hash(const std::string& str, size_t buff_size) {
    uint64_t res = 0;
    for (const auto& el : str) {
      res = (res * A_HASH + el - 'a') % P_HASH;
    }
    return res % buff_size;
  }

  void Rehash(size_t new_size) {
    std::vector<std::list<Item>> new_data(new_size);
    for (const auto& bucket : data_) {
      for (const auto& el : bucket) {
        PutElement(el, new_data);
      }
    }
    data_.swap(new_data);
  }

  static constexpr int INITIAL_SIZE = 2;
  static constexpr size_t P_HASH = 1'000'000'007;
  static constexpr size_t A_HASH = 9973;

  std::vector<std::list<Item>> data_;
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
      std::cout << map.Get(key) << '\n';
    } else {
      std::string key;
      input >> key;
      map.Delete(key);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(put hello privet
put bye poka
get hello
get bye
delete hello
get hello
)";
    Solution(ss);
    std::cout << "expected = privet poka none\n";
  }
}

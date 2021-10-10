#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

class Map {
  struct Item;

 public:
  using ValueType = std::vector<std::list<Item*>>;

  Map() : data_(INITIAL_SIZE) {}

  void Put(const std::string& key, const std::string& val) {
    size_t idx = Hash(key, data_.size());
    auto it = std::find_if(data_[idx].begin(), data_[idx].end(),
                           [&key](const auto ptr) { return ptr->key == key; });
    if (it != data_[idx].end()) {
      (*it)->value = val;
      return;
    }
    Item* new_item = new Item(key, val);
    if (tail_) {
      tail_->next = new_item;
    }
    new_item->prev = tail_;
    tail_ = new_item;

    data_[idx].push_back(new_item);

    ++num_elements_;
    if (num_elements_ == data_.size()) {
      Rehash(2 * data_.size());
    }
  }

  void Delete(const std::string& key) {
    size_t idx = Hash(key, data_.size());
    auto it = std::find_if(data_[idx].begin(), data_[idx].end(),
                           [&key](const auto ptr) { return ptr->key == key; });
    if (it == data_[idx].end()) return;

    Item* del_ptr = *it;
    if (del_ptr->next) {
      del_ptr->next->prev = del_ptr->prev;
    }
    if (del_ptr->prev) {
      del_ptr->prev->next = del_ptr->next;
    }
    if (tail_ == del_ptr) {
      tail_ = del_ptr->prev;
    }

    data_[idx].erase(it);

    delete del_ptr;

    --num_elements_;
    if (num_elements_ <= data_.size() / 4 && data_.size() > 2 * INITIAL_SIZE) {
      Rehash(data_.size() / 2);
    }
  }

  std::string Get(const std::string& key) const {
    const Item* item = FindElement(key);
    return item ? item->value : "none";
  }

  std::string Prev(const std::string& key) const {
    const Item* item = FindElement(key);
    if (!item || !item->prev) return "none";
    return item->prev->value;
  }

  std::string Next(const std::string& key) const {
    const Item* item = FindElement(key);
    if (!item || !item->next) return "none";
    return item->next->value;
  }

  ~Map() {
    while (tail_) {
      Item* del_ptr = tail_;
      tail_ = tail_->prev;
      delete del_ptr;
    }
  }

 private:
  struct Item {
    std::string key;
    std::string value;
    Item* prev = nullptr;
    Item* next = nullptr;

    Item(const std::string& gk, const std::string& gv) : key(gk), value(gv) {}
  };

  const Item* FindElement(const std::string& key) const {
    size_t idx = Hash(key, data_.size());
    auto it = std::find_if(data_[idx].begin(), data_[idx].end(),
                           [&key](const auto ptr) { return ptr->key == key; });
    return it == data_[idx].end() ? nullptr : *it;
  }

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
        new_data[Hash(el->key, new_size)].push_back(el);
      }
    }
    data_.swap(new_data);
  }

  static constexpr int INITIAL_SIZE = 2;
  static constexpr size_t P_HASH = 1'000'000'007;
  static constexpr size_t A_HASH = 9973;

  ValueType data_;
  size_t num_elements_ = 0;
  Item* tail_ = nullptr;
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
    } else if (command == "delete") {
      std::string key;
      input >> key;
      map.Delete(key);
    } else if (command == "next") {
      std::string key;
      input >> key;
      std::cout << map.Next(key) << '\n';
    } else {
      std::string key;
      input >> key;
      std::cout << map.Prev(key) << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(put zero a
put one b
put two c
put three d
put four e
get two
prev two
next two
delete one
delete three
get two
prev two
next two
next four
)";
    Solution(ss);
    std::cout << "expected = c b d c a e none\n";
  }
}

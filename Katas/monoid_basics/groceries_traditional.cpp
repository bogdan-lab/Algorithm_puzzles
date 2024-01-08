#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

constexpr bool kIsDoingSalad = false;
constexpr bool kIsOnDiet = true;

std::string kBunWithCheese = "bun_with_cheese";
std::string kBread = "bread";
std::string kCucumber = "cucumber";
std::string kTomato = "tomato";
std::string kBallPepper = "ball_pepper";
std::string kOrange = "orange";
std::string kApple = "apple";
std::string kPear = "pear";
std::string kBanana = "banana";
std::string kChicken = "chicken";
std::string kSteak = "steak";

using Products = std::map<std::string, std::size_t>;

Products kShopStorage{{kBunWithCheese, 123}, {kBread, 3},       {kCucumber, 1},
                      {kTomato, 2},          {kBallPepper, 17}, {kOrange, 10},
                      {kApple, 2},           {kPear, 77},       {kBanana, 11},
                      {kChicken, 7},         {kSteak, 3}};

Products buy(const std::string& name, size_t count) {
  auto it = kShopStorage.find(name);
  if (it == kShopStorage.end() || it->second < count) {
    return Products{};
  }
  it->second -= count;
  return Products{{name, count}};
}

class ShoppingResult {
 public:
  ShoppingResult& add(const std::string& name, size_t count) {
    products_[name] += count;
    return *this;
  }

  ShoppingResult& add(const Products& data) {
    for (const auto& [name, count] : data) {
      add(name, count);
    }
    return *this;
  }

  const Products& getProducts() const { return products_; }

 private:
  Products products_;
};

Products buyBuns() { return kIsOnDiet ? Products{} : buy(kBunWithCheese, 10); }

void doBread(ShoppingResult& res) { res.add(buy(kBread, 1)).add(buyBuns()); }

void doVegetables(ShoppingResult& res) {
  if (kIsDoingSalad) {
    res.add(buy(kCucumber, 1)).add(buy(kTomato, 1)).add(buy(kBallPepper, 3));
  }
}

void doFruits(ShoppingResult& res) {
  res.add(buy(kOrange, 1))
      .add(buy(kApple, 5))
      .add(buy(kPear, 4))
      .add(buy(kBanana, 2));
}

void doMeat(ShoppingResult& res) {
  if (kIsOnDiet) {
    res.add(buy(kChicken, 1));
  } else {
    res.add(buy(kSteak, 3));
  }
}

ShoppingResult doGroceries() {
  ShoppingResult res;
  doBread(res);
  doVegetables(res);
  doFruits(res);
  doMeat(res);
  return res;
}

void print(const Products& data) {
  for (const auto& [name, count] : data) {
    std::cout << name << " -> " << count << '\n';
  }
}

int main() {
  ShoppingResult res = doGroceries();
  print(res.getProducts());
  return 0;
}

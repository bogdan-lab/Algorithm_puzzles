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

Products merge(const Products& lhs, const Products& rhs) {
  Products res = lhs;
  for (const auto& [name, count] : rhs) res[name] += count;
  return res;
}

template <typename... ProductsT>
Products merge(const Products& l, const Products& r, const Products& n,
               const ProductsT&... args) {
  return merge(merge(l, r), n, args...);
}

Products buy(const std::string& name, size_t count) {
  auto it = kShopStorage.find(name);
  if (it == kShopStorage.end() || it->second < count) {
    return Products{};
  }
  it->second -= count;
  return Products{{name, count}};
}

Products buyBuns() { return kIsOnDiet ? Products{} : buy(kBunWithCheese, 10); }

Products doBread() { return merge(buy(kBread, 1), buyBuns()); }

Products doVegetables() {
  if (kIsDoingSalad) {
    return merge(buy(kCucumber, 1), buy(kTomato, 1), buy(kBallPepper, 3));
  }
  return Products{};
}

Products doFruits() {
  return merge(buy(kOrange, 1), buy(kApple, 5), buy(kPear, 4), buy(kBanana, 2));
}

Products doMeat() { return kIsOnDiet ? buy(kChicken, 1) : buy(kSteak, 3); }

Products doGroceries() {
  return merge(doBread(), doVegetables(), doFruits(), doMeat());
}

void print(const Products& data) {
  for (const auto& [name, count] : data) {
    std::cout << name << " -> " << count << '\n';
  }
}

int main() {
  print(doGroceries());
  return 0;
}

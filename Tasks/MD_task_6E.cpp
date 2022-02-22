#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int kEmptyElement = std::numeric_limits<int>::min();
constexpr int kInfinity = std::numeric_limits<int>::max();
constexpr int kSaleProp = 100;

struct SubtreeLoss {
  int buy = kEmptyElement;
  int coupon = kEmptyElement;
};

// data[k1-coupon left][day index]
using StateToLoss = std::vector<std::vector<SubtreeLoss>>;

void Solution(std::istream& input = std::cin);
void RunTests();

int GetMinLoss(const std::vector<int>& prices);
StateToLoss CreateStateToLoss(int day_num);
int GetMinLoss(int k1, int day_index, StateToLoss& data,
               const std::vector<int>& prices, bool buy_dinner);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n = 0;
  input >> n;
  std::vector<int> prices(n);
  for (auto& el : prices) {
    input >> el;
  }
  StateToLoss data = CreateStateToLoss(prices.size());
  std::cout << GetMinLoss(/*k1=*/0, /*day_index=*/0, data, prices,
                          /*buy_dinner=*/true)
            << '\n';
}

StateToLoss CreateStateToLoss(int day_num) {
  StateToLoss result(day_num);
  for (auto& el_out : result) {
    el_out.resize(day_num);
  }
  return result;
}

int GetMinLoss(int k1, int day_index, StateToLoss& data,
               const std::vector<int>& prices, bool buy_dinner) {
  if (day_index >= prices.size()) {
    return 0;
  }
  if (buy_dinner) {
    if (data[k1][day_index].buy == kEmptyElement) {
      int k = prices[day_index] > kSaleProp ? k1 + 1 : k1;
      data[k1][day_index].buy =
          prices[day_index] +
          std::min(GetMinLoss(k, day_index + 1, data, prices, /*buy=*/true),
                   GetMinLoss(k, day_index + 1, data, prices, /*buy=*/false));
    }
    return data[k1][day_index].buy;
  } else {
    if (data[k1][day_index].coupon == kEmptyElement) {
      if (!k1) {
        data[k1][day_index].coupon = kInfinity;
      } else {
        data[k1][day_index].coupon = std::min(
            GetMinLoss(k1 - 1, day_index + 1, data, prices, /*buy=*/true),
            GetMinLoss(k1 - 1, day_index + 1, data, prices, /*buy=*/false));
      }
    }
    return data[k1][day_index].coupon;
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
110
40
120
110
60
)";
    Solution(ss);
    std::cout << "expected = 260\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
110
110
110
)";
    Solution(ss);
    std::cout << "expected = 220\n";
  }
}

#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <vector>

constexpr int kSaleProp = 100;

class Loss {
 public:
  static Loss InfiniteLoss() { return {std::numeric_limits<int>::max()}; }

  static Loss ZeroLoss() { return Loss(0); }

  Loss(int day_index, int curr_spent, const Loss& lhs, const Loss& rhs) {
    const Loss& chosen_loss = lhs.total_loss_ < rhs.total_loss_ ||
                                      (lhs.total_loss_ == rhs.total_loss_ &&
                                       lhs.coupon_left_ > rhs.coupon_left_)
                                  ? lhs
                                  : rhs;
    total_loss_ = curr_spent > 0 ? curr_spent + chosen_loss.total_loss_
                                 : chosen_loss.total_loss_;
    coupon_left_ = curr_spent > kSaleProp ? chosen_loss.coupon_left_ + 1
                                          : chosen_loss.coupon_left_;
    coupon_used_ = chosen_loss.coupon_used_;
    coupon_days_ = chosen_loss.coupon_days_;
    if (curr_spent < 0) {
      coupon_used_ += 1;
      coupon_left_ -= 1;
      coupon_days_.push_back(day_index + 1);
    }
  }

  int GetTotal() const { return total_loss_; }
  int GetCouponLeft() const { return coupon_left_; }
  int GetCouponUsed() const { return coupon_used_; }
  const std::vector<int>& GetDays() {
    std::reverse(coupon_days_.begin(), coupon_days_.end());
    return coupon_days_;
  }

 private:
  Loss(int total_loss) : total_loss_(total_loss) {}

  int total_loss_ = 0;
  int coupon_left_ = 0;
  int coupon_used_ = 0;
  std::vector<int> coupon_days_;
};

struct SubtreeLoss {
  std::optional<Loss> buy;
  std::optional<Loss> coupon;
};

// data[k1-coupon left][day index]
using StateToLoss = std::vector<std::vector<SubtreeLoss>>;

void Solution(std::istream& input = std::cin);
void RunTests();

StateToLoss CreateStateToLoss(int day_num);
Loss GetMinLoss(int k1, int day_index, StateToLoss& data,
                const std::vector<int>& prices, bool buy_dinner);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
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
  Loss min_loss = GetMinLoss(/*k1=*/0, /*day_index=*/0, data, prices,
                             /*buy_dinner=*/true);

  std::cout << min_loss.GetTotal() << '\n'
            << min_loss.GetCouponLeft() << ' ' << min_loss.GetCouponUsed()
            << '\n';
  for (const auto& el : min_loss.GetDays()) {
    std::cout << el << '\n';
  }
}

StateToLoss CreateStateToLoss(int day_num) {
  StateToLoss result(day_num);
  for (auto& el_out : result) {
    el_out.resize(day_num);
  }
  return result;
}

Loss GetMinLoss(int k1, int day_index, StateToLoss& data,
                const std::vector<int>& prices, bool buy_dinner) {
  if (day_index >= prices.size()) {
    return Loss::ZeroLoss();
  }
  if (buy_dinner) {
    if (!data[k1][day_index].buy) {
      int k = prices[day_index] > kSaleProp ? k1 + 1 : k1;
      data[k1][day_index].buy =
          Loss{day_index, prices[day_index],
               GetMinLoss(k, day_index + 1, data, prices, /*buy=*/true),
               GetMinLoss(k, day_index + 1, data, prices, /*buy=*/false)};
    }
    return data[k1][day_index].buy.value();
  } else {
    if (!data[k1][day_index].coupon) {
      if (!k1) {
        data[k1][day_index].coupon = Loss::InfiniteLoss();
      } else {
        data[k1][day_index].coupon = Loss{
            day_index, /*curr_spent=*/-1,
            GetMinLoss(k1 - 1, day_index + 1, data, prices, /*buy=*/true),
            GetMinLoss(k1 - 1, day_index + 1, data, prices, /*buy=*/false)};
      }
    }
    return data[k1][day_index].coupon.value();
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
    std::cout << "expected = 260; 0 2; 3; 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
110
110
110
)";
    Solution(ss);
    std::cout << "expected = 220; 1 1; 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(0
)";
    Solution(ss);
    std::cout << "expected = 0; 0 0;\n";
  }
}

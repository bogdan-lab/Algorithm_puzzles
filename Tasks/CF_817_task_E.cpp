#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

constexpr int kMaxHeight = 100'000;

struct Rec {
  explicit Rec(int gh) : h(gh), w_acc(1, {-1, 0}) {}

  int h;
  std::vector<std::pair<int, int64_t>> w_acc;
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

int64_t CalcArea(const std::vector<Rec>& data, int hs, int ws, int hb, int wb) {
  int64_t res = 0;
  auto h_begin =
      std::upper_bound(data.begin(), data.end(), hs,
                       [](int h, const auto& rec) { return h < rec.h; });
  auto h_end =
      std::lower_bound(data.begin(), data.end(), hb,
                       [](const auto& rec, int h) { return rec.h < h; });

  for (auto it = h_begin; it != h_end; ++it) {
    auto it_begin =
        std::upper_bound(it->w_acc.begin(), it->w_acc.end(), ws,
                         [](int w, const auto& p) { return w < p.first; });
    int64_t prefix = std::prev(it_begin)->second;
    auto it_end =
        std::lower_bound(it->w_acc.begin(), it->w_acc.end(), wb,
                         [](const auto& p, int w) { return p.first < w; });
    res += std::prev(it_end)->second - prefix;
  }
  return res;
}

std::vector<Rec> ExtractFilled(std::vector<Rec>& data) {
  std::vector<Rec> result;
  result.reserve(data.size());
  for (auto& el : data) {
    if (el.w_acc.size() > 1) {
      result.push_back(std::move(el));
    }
  }
  return result;
}

void Solution(std::istream& input) {
  int case_num;
  input >> case_num;
  while (case_num--) {
    std::vector<Rec> total;
    total.reserve(kMaxHeight + 1);
    std::generate_n(std::back_inserter(total), kMaxHeight + 1,
                    [n = 0]() mutable { return Rec(n++); });

    int rec_num, requests;
    input >> rec_num >> requests;
    while (rec_num--) {
      int h, w;
      input >> h >> w;
      total[h].w_acc.push_back({w, 0});
    }

    std::vector<Rec> data = ExtractFilled(total);

    for (auto& el : data) {
      std::sort(el.w_acc.begin(), el.w_acc.end());
      for (int i = 1; i < el.w_acc.size(); ++i) {
        el.w_acc[i].second += el.w_acc[i - 1].second + el.h * el.w_acc[i].first;
      }
    }

    while (requests--) {
      int hs, ws, hb, wb;
      input >> hs >> ws >> hb >> wb;
      std::cout << CalcArea(data, hs, ws, hb, wb) << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

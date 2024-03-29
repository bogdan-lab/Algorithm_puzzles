#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

constexpr int64_t kFlightPrice = 10'000'000'000'000;
constexpr int64_t kInfinity = std::numeric_limits<int64_t>::max();

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

struct Weight {
  int64_t fp = kFlightPrice;
  int64_t sp = 0;
  bool accessibale = false;
};

int64_t GetWeight(Weight w) { return w.accessibale ? w.fp - w.sp : kInfinity; }

Weight Add(Weight l, Weight r) {
  return {l.fp + r.fp, l.sp + r.sp, l.accessibale && r.accessibale};
}

void Solution(std::istream& input) {
  int n;
  input >> n;

  std::vector<int64_t> prices(n);
  for (auto& el : prices) {
    input >> el;
  }

  std::vector<std::vector<Weight>> curr(n, std::vector<Weight>(n));

  std::string buff;
  for (int i = 0; i < n; ++i) {
    input >> buff;
    for (int j = 0; j < buff.size(); ++j) {
      if (buff[j] == 'Y') {
        curr[i][j].sp = prices[j];
        curr[i][j].accessibale = true;
      }
    }
  }

  std::vector<std::vector<Weight>> next = curr;
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (GetWeight(curr[i][j]) <= GetWeight(Add(curr[i][k], curr[k][j]))) {
          next[i][j] = curr[i][j];
        } else {
          next[i][j] = Add(curr[i][k], curr[k][j]);
        }
      }
    }
    std::swap(curr, next);
  }

  int q;
  input >> q;
  while (q--) {
    int start, end;
    input >> start >> end;
    --start;
    --end;
    if (!curr[start][end].accessibale) {
      std::cout << "Impossible\n";
    } else {
      std::cout << curr[start][end].fp / kFlightPrice << ' '
                << curr[start][end].sp + prices[start] << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
30 50 70 20 60
NYYNN
NNYNN
NNNYY
YNNNN
YNNNN
3
1 3
3 1
4 5
)";
    Solution(ss);
    std::cout << "expected = 1 100; 2 160; 3 180\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
100 100
NN
NN
1
1 2
)";
    Solution(ss);
    std::cout << "expected = Impossible\n";
  }
}

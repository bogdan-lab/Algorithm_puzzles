#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

constexpr int kMaxHeight = 1000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t CalcArea(const std::vector<std::vector<int64_t>>& data, int hs, int ws,
                 int hb, int wb) {
  return data[hb - 1][wb - 1] - data[hs][wb - 1] - data[hb - 1][ws] +
         data[hs][ws];
}

void Solution(std::istream& input) {
  int case_num;
  input >> case_num;
  while (case_num--) {
    std::vector<std::vector<int64_t>> data(
        kMaxHeight + 1, std::vector<int64_t>(kMaxHeight + 1));
    int rec_num, requests;
    input >> rec_num >> requests;
    while (rec_num--) {
      int h, w;
      input >> h >> w;
      data[h][w] += static_cast<int64_t>(h * w);
    }

    for (int i = 1; i < data.size(); ++i) {
      for (int j = 1; j < data.size(); ++j) {
        data[i][j] += data[i - 1][j] + data[i][j - 1] - data[i - 1][j - 1];
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

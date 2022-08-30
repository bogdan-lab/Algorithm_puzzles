#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t CalcArea(const std::vector<std::vector<std::pair<int, int64_t>>>& data,
                 int hs, int ws, int hb, int wb) {
  int64_t res = 0;
  int max_h = std::min<int>(hb, data.size());
  for (int h = hs + 1; h < max_h; ++h) {
    if (data[h].empty()) continue;
    auto it_begin = std::upper_bound(
        data[h].begin(), data[h].end(), ws,
        [](int w, const std::pair<int, int64_t>& p) { return w < p.first; });
    int64_t prefix = std::prev(it_begin)->second;
    auto it_end = std::lower_bound(
        data[h].begin(), data[h].end(), wb,
        [](const std::pair<int, int64_t>& p, int w) { return p.first < w; });
    int64_t total = std::prev(it_end)->second;
    res += total - prefix;
  }
  return res;
}

void AddRec(std::vector<std::vector<std::pair<int, int64_t>>>& data, int h,
            int w) {
  if (h >= data.size()) {
    data.resize(h + 1);
  }
  if (data[h].empty()) {
    data[h].push_back({-1, 0});
  }
  data[h].push_back({w, 0});
}

void Solution(std::istream& input) {
  int case_num;
  input >> case_num;
  while (case_num--) {
    int rec_num, requests;
    input >> rec_num >> requests;
    std::vector<std::vector<std::pair<int, int64_t>>> data;
    data.reserve(rec_num);
    while (rec_num--) {
      int h, w;
      input >> h >> w;
      AddRec(data, h, w);
    }

    for (int h = 0; h < data.size(); ++h) {
      std::sort(data[h].begin(), data[h].end());
      for (int i = 1; i < data[h].size(); ++i) {
        data[h][i].second += data[h][i - 1].second + h * data[h][i].first;
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

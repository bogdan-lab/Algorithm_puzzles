#include <iostream>
#include <sstream>
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

void Solution(std::istream& input) {
  int H, W, N, h, w;
  input >> H >> W >> N >> h >> w;
  std::vector<std::vector<int>> data(H, std::vector<int>(W));
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      input >> data[i][j];
    }
  }

  std::vector<int> count(N + 1);
  int unique_count = 0;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      ++count[data[i][j]];
      if (count[data[i][j]] == 1) {
        ++unique_count;
      }
    }
  }

  std::vector<std::vector<int>> res(H - h + 1, std::vector<int>(W - w + 1));

  // Blackout first
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      --count[data[i][j]];
      if (!count[data[i][j]]) {
        --unique_count;
      }
    }
  }
  res[0][0] = unique_count;

  // Moving blackouts
  int k = 0;
  while (true) {
    for (int l = 1; l < res[k].size(); ++l) {
      // Here we shift black to the right
      // open previous column
      for (int i = k; i < k + h; ++i) {
        ++count[data[i][l - 1]];
        if (count[data[i][l - 1]] == 1) {
          ++unique_count;
        }
      }
      // close next column
      for (int i = k; i < k + h; ++i) {
        --count[data[i][l - 1 + w]];
        if (!count[data[i][l - 1 + w]]) {
          --unique_count;
        }
      }
      res[k][l] = unique_count;
    }
    if (k + h >= data.size()) break;
    // Here we step one row down
    // open top row
    for (int i = W - 1; i >= W - w; --i) {
      ++count[data[k][i]];
      if (count[data[k][i]] == 1) {
        ++unique_count;
      }
    }
    // close bottom row
    for (int i = W - 1; i >= W - w; --i) {
      --count[data[k + h][i]];
      if (!count[data[k + h][i]]) {
        --unique_count;
      }
    }
    ++k;
    res[k].back() = unique_count;
    // Move Blackout from right to left
    for (int l = res[k].size() - 2; l >= 0; --l) {
      // Open column on the right
      for (int i = k; i < k + h; ++i) {
        ++count[data[i][l + w]];
        if (count[data[i][l + w]] == 1) {
          ++unique_count;
        }
      }
      // Close column on the left
      for (int i = k; i < k + h; ++i) {
        --count[data[i][l]];
        if (!count[data[i][l]]) {
          --unique_count;
        }
      }
      res[k][l] = unique_count;
    }
    if (k + h >= data.size()) break;
    // Here we step one more row down
    // Open top row
    for (int i = 0; i < w; ++i) {
      ++count[data[k][i]];
      if (count[data[k][i]] == 1) {
        ++unique_count;
      }
    }
    // close bot row
    for (int i = 0; i < w; ++i) {
      --count[data[k + h][i]];
      if (!count[data[k + h][i]]) {
        --unique_count;
      }
    }
    ++k;
    res[k].front() = unique_count;
  }

  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 4 5 2 2
2 2 1 1
3 2 5 3
3 4 4 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 6 9 3 4
7 1 5 3 9 5
4 5 4 5 1 2
6 1 6 2 9 7
4 7 1 5 8 8
3 4 3 3 5 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(9 12 30 4 7
2 2 2 2 2 2 2 2 2 2 2 2
2 2 20 20 2 2 5 9 10 9 9 23
2 29 29 29 29 29 28 28 26 26 26 15
2 29 29 29 29 29 25 25 26 26 26 15
2 29 29 29 29 29 25 25 8 25 15 15
2 18 18 18 18 1 27 27 25 25 16 16
2 19 22 1 1 1 7 3 7 7 7 7
2 19 22 22 6 6 21 21 21 7 7 7
2 19 22 22 22 22 21 21 21 24 24 24
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

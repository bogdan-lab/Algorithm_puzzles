#include <deque>
#include <iostream>
#include <sstream>
#include <utility>

void Solution(std::istream& input = std::cin);
void RunTests();
std::deque<size_t> MakeReverseOperations(std::deque<size_t> ans);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    size_t n;
    input >> n;
    std::deque<size_t> ans;
    while (n--) {
      size_t tmp;
      input >> tmp;
      ans.push_back(tmp);
    }
    auto res = MakeReverseOperations(std::move(ans));
    if (res.empty()) {
      std::cout << "-1";
    } else {
      for (const auto& el : res) {
        std::cout << el << ' ';
      }
    }
    std::cout << '\n';
  }
}

std::deque<size_t> MakeReverseOperations(std::deque<size_t> ans) {
  std::deque<size_t> result;
  if (ans.empty()) return result;
  if (ans.size() == 1) return ans;
  if (ans.front() > ans.back()) {
    result.push_back(ans.front());
    ans.pop_front();
  } else {
    result.push_back(ans.back());
    ans.pop_back();
  }
  while (!ans.empty()) {
    if (ans.front() <= result.back()) {
      result.push_front(ans.front());
      ans.pop_front();
    } else if (ans.back() <= result.front()) {
      result.push_back(ans.back());
      ans.pop_back();
    } else {
      result.clear();
      break;
    }
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
4
1 3 2 4
1
1
5
1 3 5 4 2
3
3 2 1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

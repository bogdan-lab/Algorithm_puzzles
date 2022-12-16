#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
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

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

char ToChar(int i) { return static_cast<char>(i + static_cast<int>('a')); }

std::vector<std::vector<int>> BuildMG(const std::string& pwd) {
  int total_size = ToInt('z') + 1;
  std::vector<std::vector<int>> res(total_size, std::vector<int>(total_size));
  res[ToInt(pwd[0])][ToInt(pwd[1])] = 1;
  res[ToInt(pwd.back())][ToInt(pwd[pwd.size() - 2])] = 1;
  for (int i = 1; i < pwd.size() - 1; ++i) {
    res[ToInt(pwd[i])][ToInt(pwd[i - 1])] = 1;
    res[ToInt(pwd[i])][ToInt(pwd[i + 1])] = 1;
  }
  return res;
}

void DFS(const std::vector<std::vector<int>>& g, int id,
         std::vector<int>& lookup, std::vector<int>& res) {
  if (lookup[id]) return;
  lookup[id] = 1;
  res.push_back(id);
  for (const auto& el : g[id]) {
    DFS(g, el, lookup, res);
  }
}

std::vector<int> BuildIntRepr(const std::vector<std::vector<int>>& g,
                              int start) {
  std::vector<int> res;
  res.reserve(ToInt('z') + 1);
  std::vector<int> lookup(ToInt('z') + 1);
  DFS(g, start, lookup, res);

  for (int i = 0; i < lookup.size(); ++i) {
    if (!lookup[i]) {
      res.push_back(i);
    }
  }
  return res;
}

std::string ConvertToString(const std::vector<int>& repr) {
  std::string res;
  res.reserve(repr.size());
  std::transform(repr.begin(), repr.end(), std::back_inserter(res),
                 [](int i) { return ToChar(i); });
  return res;
}

std::string BuildOneLetterKeyboard(char c) {
  std::vector<int> res(ToInt('z') + 1);
  std::iota(res.begin(), res.end(), 0);
  std::swap(res[0], res[ToInt(c)]);
  return ConvertToString(res);
}

std::vector<std::vector<int>> BuildLinkedGraph(
    const std::vector<std::vector<int>>& mg) {
  std::vector<std::vector<int>> g;
  for (int i = 0; i < mg.size(); ++i) {
    g.emplace_back();
    for (int j = 0; j < mg[i].size(); ++j) {
      if (mg[i][j]) {
        g.back().push_back(j);
      }
    }
    if (g.back().size() > 2) {
      g.clear();
      return g;
    }
  }

  return g;
}

std::string BuildKeyboard(const std::string& pwd) {
  if (pwd.size() == 1) {
    return BuildOneLetterKeyboard(pwd[0]);
  }

  auto g = BuildLinkedGraph(BuildMG(pwd));
  int start =
      std::find_if(g.begin(), g.end(),
                   [](const std::vector<int>& d) { return d.size() == 1; }) -
      g.begin();

  if (start == g.size()) return {};

  return ConvertToString(BuildIntRepr(g, start));
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) {
    std::string pwd;
    input >> pwd;
    std::string keyboard = BuildKeyboard(pwd);
    if (keyboard.empty()) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n" << keyboard << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
ababa
codedoca
abcda
zxzytyz
abcdefghijklmnopqrstuvwxyza
)";
    Solution(ss);
    std::cout << "expected = YES; YES; NO; YES; NO\n";
  }
}

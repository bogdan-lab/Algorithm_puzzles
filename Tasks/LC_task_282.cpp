#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int64_t Apply(int64_t l, int64_t r, char op);
void TrySingleVal(char op, const std::string& str, int i, int64_t curr_val,
                  int64_t target, std::string& curr_path,
                  std::vector<std::string>& res);
void TryMultiplied(char op, const std::string& str, int i, int64_t curr_val,
                   int64_t target, std::string& curr_path,
                   std::vector<std::string>& res);
void TryMultiDigit(char op, const std::string& str, int i, int64_t curr_val,
                   int64_t target, std::string& curr_path,
                   std::vector<std::string>& res);
void TryOperation(char op, const std::string& str, int i, int64_t curr_val,
                  int64_t target, std::string& curr_path,
                  std::vector<std::string>& res);
void BuildPath(const std::string& str, int i, int64_t curr_val, int64_t target,
               std::string& curr_path, std::vector<std::string>& res);

int64_t ToInt(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

int64_t Apply(int64_t l, int64_t r, char op) {
  if (op == '+') return l + r;
  return l - r;
}

void TrySingleVal(char op, const std::string& str, int i, int64_t curr_val,
                  int64_t target, std::string& curr_path,
                  std::vector<std::string>& res) {
  curr_path.push_back(str[i]);
  BuildPath(str, i + 1, Apply(curr_val, ToInt(str[i]), op), target, curr_path,
            res);
  curr_path.pop_back();
}

void TryMultiplied(char op, const std::string& str, int i, int64_t curr_val,
                   int64_t target, std::string& curr_path,
                   std::vector<std::string>& res) {
  if (i + 1 >= str.size()) return;

  int initial_size = curr_path.size();
  curr_path.push_back(str[i]);
  int64_t mult_val = ToInt(str[i]);
  for (int j = i + 1; j < str.size(); ++j) {
    curr_path.push_back('*');
    curr_path.push_back(str[j]);
    mult_val *= ToInt(str[j]);
    BuildPath(str, j + 1, Apply(curr_val, mult_val, op), target, curr_path,
              res);
  }

  while (initial_size < curr_path.size()) {
    curr_path.pop_back();
  }
}

void TryMultiDigit(char op, const std::string& str, int i, int64_t curr_val,
                   int64_t target, std::string& curr_path,
                   std::vector<std::string>& res) {
  if (i + 1 >= str.size() || str[i] == '0') return;

  int initial_size = curr_path.size();
  curr_path.push_back(str[i]);
  int64_t md_val = ToInt(str[i]);
  for (int j = i + 1; j < str.size(); ++j) {
    curr_path.push_back(str[j]);
    md_val = 10 * md_val + ToInt(str[j]);
    BuildPath(str, j + 1, Apply(curr_val, md_val, op), target, curr_path, res);
  }

  while (curr_path.size() > initial_size) {
    curr_path.pop_back();
  }
}

void TryOperation(char op, const std::string& str, int i, int64_t curr_val,
                  int64_t target, std::string& curr_path,
                  std::vector<std::string>& res) {
  curr_path.push_back(op);
  TrySingleVal(op, str, i, curr_val, target, curr_path, res);
  TryMultiplied(op, str, i, curr_val, target, curr_path, res);
  TryMultiDigit(op, str, i, curr_val, target, curr_path, res);
  curr_path.pop_back();
}

void BuildPath(const std::string& str, int i, int64_t curr_val, int64_t target,
               std::string& curr_path, std::vector<std::string>& res) {
  std::cout << curr_path << " = " << curr_val << '\n';
  if (i == str.size()) {
    if (curr_val == target) {
      res.push_back(curr_path.substr(1));
    }
    return;
  }
  TryOperation('+', str, i, curr_val, target, curr_path, res);
  TryOperation('-', str, i, curr_val, target, curr_path, res);
}

class Solution {
 public:
  std::vector<std::string> addOperators(std::string num, int target) {
    std::vector<std::string> res;
    std::string curr_path;
    curr_path.reserve(2 * num.size());
    TryOperation('+', num, 0, 0, target, curr_path, res);
    return res;
  }
};

int main() {
  {
    Solution s;
    std::vector<std::string> data = s.addOperators("2222222", 0);
    for (const auto& el : data) {
      std::cout << el << '\n';
    }
  }
  return 0;
}

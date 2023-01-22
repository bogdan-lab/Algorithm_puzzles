#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void BuildPathes(std::string_view str, int64_t target, std::string& curr_path,
                 std::vector<std::string>& res);
void TryPlusMinus(int64_t curr_val, int64_t target, std::string_view next_str,
                  std::string& curr_path, std::vector<std::string>& res);
void TrySingleValue(std::string_view str, int64_t target,
                    std::string& curr_path, std::vector<std::string>& res);
void TryMultiplication(std::string_view str, int64_t target,
                       std::string& curr_path, std::vector<std::string>& res);
void TryManyDigits(std::string_view str, int64_t target, std::string& curr_path,
                   std::vector<std::string>& res);

int64_t ToInt(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

void TryPlusMinus(int64_t curr_val, int64_t target, std::string_view next_str,
                  std::string& curr_path, std::vector<std::string>& res) {
  // Try this value with +
  curr_path.push_back('+');
  BuildPathes(next_str, target - curr_val, curr_path, res);
  curr_path.pop_back();
  // Try this value with -
  curr_path.push_back('-');
  BuildPathes(next_str, target + curr_val, curr_path, res);
  curr_path.pop_back();
}

void TrySingleValue(std::string_view str, int64_t target,
                    std::string& curr_path, std::vector<std::string>& res) {
  curr_path.push_back(str.front());
  int64_t curr_val = ToInt(str.front());
  if (str.size() == 1) {
    if (curr_val == target) {
      res.push_back(curr_path);
    }
  } else {
    TryPlusMinus(curr_val, target, str.substr(1), curr_path, res);
  }
  curr_path.pop_back();
}

void TryMultiplication(std::string_view str, int64_t target,
                       std::string& curr_path, std::vector<std::string>& res) {
  if (str.size() < 2) return;
  int initial_size = curr_path.size();
  curr_path.push_back(str.front());
  int64_t curr_val = ToInt(str.front());
  for (int i = 1; i < str.size() - 1; ++i) {
    curr_path.push_back('*');
    curr_path.push_back(str[i]);
    curr_val *= ToInt(str[i]);
    TryPlusMinus(curr_val, target, str.substr(i + 1), curr_path, res);
  }
  // the last value is treated separately
  curr_path.push_back('*');
  curr_path.push_back(str.back());
  curr_val *= ToInt(str.back());
  if (target == curr_val) {
    res.push_back(curr_path);
  }
  while (curr_path.size() > initial_size) {
    curr_path.pop_back();
  }
}

void TryManyDigits(std::string_view str, int64_t target, std::string& curr_path,
                   std::vector<std::string>& res) {
  if (str.size() < 2 || str.front() == '0') return;
  int initial_size = curr_path.size();

  int64_t curr_val = ToInt(str.front());
  curr_path.push_back(str.front());
  for (int i = 1; i < str.size() - 1; ++i) {
    curr_path.push_back(str[i]);
    curr_val = 10 * curr_val + ToInt(str[i]);
    TryPlusMinus(curr_val, target, str.substr(i + 1), curr_path, res);
  }
  // The last case separately
  curr_path.push_back(str.back());
  curr_val = 10 * curr_val + ToInt(str.back());
  if (curr_val == target) {
    res.push_back(curr_path);
  }

  while (curr_path.size() > initial_size) {
    curr_path.pop_back();
  }
}

void BuildPathes(std::string_view str, int64_t target, std::string& curr_path,
                 std::vector<std::string>& res) {
  TrySingleValue(str, target, curr_path, res);
  TryMultiplication(str, target, curr_path, res);
  TryManyDigits(str, target, curr_path, res);
}

class Solution {
 public:
  std::vector<std::string> addOperators(std::string num, int target) {
    std::vector<std::string> res;
    std::string curr_path;
    curr_path.reserve(2 * num.size() - 1);
    BuildPathes(num, target, curr_path, res);
    return res;
  }
};

int main() {
  {
    Solution s;
    std::vector<std::string> data = s.addOperators("232", 8);
    for (const auto& el : data) {
      std::cout << el << '\n';
    }
  }
  return 0;
}

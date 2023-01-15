#include <algorithm>
#include <cassert>
#include <string>
#include <string_view>
#include <utility>

int DoCalc(std::string_view data);
std::string_view ClearFrontSpaces(std::string_view data);
int ToInt(char c);
std::pair<int, std::string_view> GetNumber(std::string_view data);
std::pair<int, std::string_view> GetParentesis(std::string_view data);
std::pair<int, std::string_view> GetNextValue(std::string_view data);
std::pair<int, std::string_view> GetUnaryMinus(std::string_view data);

std::string_view ClearFrontSpaces(std::string_view data) {
  if (!data.empty()) {
    data.remove_prefix(std::min(data.find_first_not_of(" "), data.size()));
  }
  return data;
}

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

std::pair<int, std::string_view> GetNumber(std::string_view data) {
  data = ClearFrontSpaces(data);
  assert(!data.empty() && std::isdigit(data.front()));
  int count = 0;
  int val = 0;
  while (count < data.size() && std::isdigit(data[count])) {
    val = 10 * val + ToInt(data[count]);
    ++count;
  }
  if (count == data.size()) return {val, std::string_view{}};
  return {val, data.substr(count)};
}

std::pair<int, std::string_view> GetParentesis(std::string_view data) {
  data = ClearFrontSpaces(data);
  assert(!data.empty() && data.front() == '(');
  int count = 1;
  int i = 1;
  while (i < data.size()) {
    if (data[i] == '(') {
      ++count;
    } else if (data[i] == ')') {
      --count;
    }
    if (!count) break;
    ++i;
  }
  assert(i < data.size());
  int val = DoCalc(data.substr(1, i - 1));
  if (i + 1 == data.size()) return {val, std::string_view{}};
  return {val, data.substr(i + 1)};
}

std::pair<int, std::string_view> GetNextValue(std::string_view data) {
  data = ClearFrontSpaces(data);
  if (std::isdigit(data.front())) {
    return GetNumber(data);
  }
  return GetParentesis(data);
}

std::pair<int, std::string_view> GetUnaryMinus(std::string_view data) {
  data = ClearFrontSpaces(data);
  assert(!data.empty() && data.front() == '-');
  auto nv = GetNextValue(data.substr(1));
  nv.first = -nv.first;
  return nv;
}

int DoCalc(std::string_view data) {
  std::pair<int, std::string_view> buff{0, ClearFrontSpaces(data)};
  assert(!buff.second.empty());
  if (buff.second.front() == '-') {
    buff = GetUnaryMinus(buff.second);
  } else if (buff.second.front() == '(') {
    buff = GetParentesis(buff.second);
  } else {
    buff = GetNumber(buff.second);
  }
  int res = buff.first;
  buff.second = ClearFrontSpaces(buff.second);
  while (!buff.second.empty()) {
    char sign = buff.second.front();
    buff = GetNextValue(buff.second.substr(1));

    if (sign == '-') {
      res -= buff.first;
    } else {
      res += buff.first;
    }
    buff.second = ClearFrontSpaces(buff.second);
  }

  return res;
}

class Solution {
 public:
  int calculate(std::string s) { return DoCalc(s); }
};


#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
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

std::vector<int> buildSuffArr(const std::string& data) {
  std::vector<std::pair<char, size_t>> suf;
  suf.reserve(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    suf.emplace_back(data[i], i);
  }
  std::sort(suf.begin(), suf.end());

  std::vector<int> res;
  res.reserve(suf.size());
  for (const auto& el : suf) {
    res.push_back(el.second);
  }
  return res;
}

std::vector<int> buildEqvClass(const std::string& data,
                               const std::vector<int>& suff_arr) {
  std::vector<int> res(data.size());
  int cnt = 0;
  res[suff_arr.front()] = cnt;
  for (size_t i = 1; i < suff_arr.size(); ++i) {
    int index = suff_arr[i];
    int prev_index = suff_arr[i - 1];
    if (data[index] != data[prev_index]) {
      ++cnt;
    }
    res[index] = cnt;
  }
  return res;
}

std::vector<int> buildEqvClass(const std::vector<std::pair<int, int>>& data,
                               const std::vector<int>& suff_arr) {
  std::vector<int> res(data.size());
  int cnt = 0;
  res[suff_arr[0]] = cnt;
  for (size_t i = 1; i < suff_arr.size(); ++i) {
    int index = i;
    int prev_index = i - 1;
    if (data[index] != data[prev_index]) {
      ++cnt;
    }
    res[suff_arr[index]] = cnt;
  }
  return res;
}

size_t getCycle(size_t full, size_t curr) { return curr % full; }

std::vector<std::pair<int, int>> BuildNewStrings(
    const std::vector<int>& eqv_class, const std::vector<int>& suff_arr,
    int delta) {
  std::vector<std::pair<int, int>> res;
  res.reserve(eqv_class.size());

  for (size_t i = 0; i < suff_arr.size(); ++i) {
    int index = suff_arr[i];
    res.emplace_back(eqv_class[index],
                     eqv_class[getCycle(eqv_class.size(), index + delta)]);
  }

  return res;
}

void SortTogether(std::vector<std::pair<int, int>>& data,
                  std::vector<int>& suff_arr) {
  std::vector<std::pair<std::pair<int, int>, int>> tmp;
  tmp.reserve(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    tmp.emplace_back(data[i], suff_arr[i]);
  }

  std::sort(tmp.begin(), tmp.end());

  for (size_t i = 0; i < tmp.size(); ++i) {
    data[i] = tmp[i].first;
    suff_arr[i] = tmp[i].second;
  }
}

void PrintAns(const std::vector<int>& data) {
  for (const auto& el : data) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void Solution(std::istream& input) {
  std::string data;
  input >> data;
  data.push_back('$');

  std::vector<int> suff_arr = buildSuffArr(data);
  std::vector<int> eqv_class = buildEqvClass(data, suff_arr);

  int k = 0;
  while ((1 << k) < data.size()) {
    int half_len = (1 << k);
    std::vector<std::pair<int, int>> next_str =
        BuildNewStrings(eqv_class, suff_arr, half_len);

    SortTogether(next_str, suff_arr);
    eqv_class = buildEqvClass(next_str, suff_arr);

    ++k;
  }

  PrintAns(suff_arr);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(ababba
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

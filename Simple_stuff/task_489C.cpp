#include <iostream>
#include <vector>
#include <algorithm>


std::vector<int> get_min_num(const std::vector<int>& max_vec) { 
    std::vector<int> vec{max_vec};
    std::reverse(vec.begin(), vec.end());
    auto it_non_zero = std::find_if(vec.begin(), vec.end(), [](int el){return el;});
    if(it_non_zero==vec.begin()){
        return vec;
    }
    if(it_non_zero==vec.end()){
        //if we are here then our number is 0
        return vec;
    }
    vec.front()=1;
    --(*it_non_zero);
    return vec; 
}

std::vector<int> get_max_num(int m, int s) {
  // previous checks guaranty that m>s and s>9*m
  std::vector<int> res;
  res.reserve(m);
  int val = 9;
  while (val > 0) {
    size_t val_num = s / val;
    for (size_t i = 0; i < val_num; ++i) {
      res.push_back(val);
    }
    s -= val_num * val;
    --val;
  }
  for (size_t i = res.size(); i < m; ++i) {
    res.push_back(0);
  }
  return res;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
  for (auto el : vec) {
    out << el;
  }
  return out;
}

bool check_correctness(int m, int s) {
  if (s==0 && m>1) {
    return false;
  }
  if (s > 9 * m) {
    return false;
  }
  return true;
}

void solution(std::istream& input = std::cin) {
  int m, s;
  input >> m >> s;
  if (!check_correctness(m, s)) {
    std::cout << "-1 -1\n";
    return;
  }
  std::vector<int> max_vec = get_max_num(m, s);
  std::cout << get_min_num(max_vec) << ' ' << max_vec << '\n';
}

int main() {
  solution();

  return 0;
}

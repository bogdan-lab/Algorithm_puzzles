#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

std::vector<int> integrate_durations(const std::vector<int>& dv) {
  std::vector<int> res(dv.size() + 1, 0);
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = res[i - 1] + dv[i - 1];
  }
  return res;
}

int get_distance(std::vector<int>::const_iterator begin,
                 std::vector<int>::const_iterator end) {
  return static_cast<int>(std::distance(begin, end));
}

int get_max_book_num(const std::vector<int>& integ, int t) {
  // here integ is sorted since data is only positive!
  int max_num = 0;
  for (auto curr_begin = integ.begin(); curr_begin != integ.end();
       ++curr_begin) {
    int t_search = *curr_begin + t;
    auto it = std::upper_bound(curr_begin, integ.end(), t_search);
    if (it == integ.end()) {
      max_num = std::max(max_num, get_distance(curr_begin, integ.end())-1);
      break;
    }
    max_num = std::max(max_num, get_distance(curr_begin, it)-1);
  }
  return max_num;
}

int solution(std::istream& input = std::cin) {
  int n, t;
  input >> n >> t;
  std::vector<int> durations;
  durations.reserve(n);
  std::copy_n(std::istream_iterator<int>(input), n,
              std::back_inserter(durations));
  std::vector<int> integ_dur = integrate_durations(durations);
  return get_max_book_num(integ_dur, t);
}

int main() {
  std::stringstream ss;
  ss << R"(4 5
    3 1 2 1)";

  std::cout << solution();

  return 0;
}

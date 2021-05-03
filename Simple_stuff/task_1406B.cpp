#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int get_max_multiply(std::vector<int>& vec) {
  if (vec.size() == 5) return vec[0] * vec[1] * vec[2] * vec[3] * vec[4];
  std::sort(vec.begin(), vec.end());
  int res = vec.back();
  int pos_idx = vec.size() - 1;
  int neg_idx = 0;
  int pos_hand = vec[--pos_idx] * vec[--pos_idx];
  int neg_hand = vec[neg_idx++] * vec[neg_idx++];
  if (pos_hand > neg_hand) {
    res *= pos_hand;
    pos_hand = vec[--pos_idx] * vec[--pos_idx];
  } else {
    res *= neg_hand;
    neg_hand = vec[neg_idx++] * vec[neg_idx++];
  }
  return res * std::max(neg_hand, pos_hand);
}

void solution(std::istream& input = std::cin) {
  std::vector<int> data;
  data.reserve(100'000);
  int t;
  input >> t;
  int n;
  while (t--) {
    input >> n;
    std::copy_n(std::istream_iterator<int>(input), n, std::back_inserter(data));
    std::cout << get_max_multiply(data) << '\n';
    data.clear();
  }
}

int main() {
  /*{
    std::stringstream ss;
    ss << R"(4
5
-1 -2 -3 -4 -5
6
-1 -2 -3 1 2 -1
6
-1 0 0 0 -1 -1
6
-9 -7 -5 -3 -2 1)";
    solution(ss);
  }*/

  solution();
  return 0;
}

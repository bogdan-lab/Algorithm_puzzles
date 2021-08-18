#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_set>
#include <vector>

std::unordered_set<size_t> get_unique_elements(const std::vector<size_t> vec) {
  return {vec.begin(), vec.end()};
}

void make_beautiful(const std::vector<size_t>& v_in, size_t k,
                    std::vector<size_t>& v_out) {
  v_out.clear();
  if (k == v_in.size()) {
    std::copy(v_in.begin(), v_in.end(), std::back_inserter(v_out));
    return;
  }
  std::unordered_set<size_t> unique = get_unique_elements(v_in);
  if (unique.size() > k) {
    return;  // return empty vector -> cannot make it beautiful
  }
  // Here we should be able to make it beautiful by inserting stuff
  // and if we do not care about optimization it will be n times of elements
  // with period k
  std::vector<size_t> period;
  period.reserve(k);
  std::copy(unique.begin(), unique.end(), std::back_inserter(period));
  for (size_t i = unique.size(); i < k; ++i) period.push_back(1u);
  for (size_t i = 0; i < v_in.size(); ++i) {
    for (auto el : period) v_out.push_back(el);
  }
}

void print_answer(const std::vector<size_t>& v_out) {
  if (v_out.empty()) {
    std::cout << "-1\n";
    return;
  }
  std::cout << v_out.size() << '\n';
  for (auto el : v_out) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void solution(std::istream& input = std::cin) {
  size_t t;
  input >> t;
  std::vector<size_t> vec_in;
  vec_in.reserve(100);
  std::vector<size_t> vec_out;
  vec_out.reserve(10000);
  while (t--) {
    size_t n, k;
    input >> n >> k;
    std::copy_n(std::istream_iterator<size_t>(input), n,
                std::back_inserter(vec_in));
    make_beautiful(vec_in, k, vec_out);
    print_answer(vec_out);
    vec_in.clear();
  }
}

int main() {
  std::stringstream ss;
  ss << R"(4
4 2
1 2 2 1
4 3
1 2 2 1
3 2
1 2 3
4 4
4 3 4 2
)";
  solution(std::cin);
  return 0;
}

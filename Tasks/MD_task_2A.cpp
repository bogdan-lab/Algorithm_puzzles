#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

struct PartitionResult {
  size_t less_end;
  size_t equal_end;
};

void solution(std::istream& input = std::cin);
void run_tests();
int find_k_stat(std::vector<int>& iq_data, size_t begin, size_t end,
                size_t k_stat, std::mt19937& rnd);

PartitionResult partition(std::vector<int>& iq_data, size_t begin, size_t end,
                          std::mt19937& rnd);

int main() {
  //run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  size_t n = 0;
  input >> n;
  std::vector<int> iq_data(n);
  for (auto& el : iq_data) {
    input >> el;
  }
  int m = 0;
  input >> m;
  std::mt19937 rnd(m);
  while (m--) {
    size_t begin = 0;
    size_t end = 0;
    size_t k_stat = 0;
    input >> begin >> end >> k_stat;
    std::cout << find_k_stat(iq_data, --begin, end, --k_stat, rnd) << '\n';
  }
}

PartitionResult partition(std::vector<int>& iq_data, size_t begin, size_t end,
                          std::mt19937& rnd) {
  std::uniform_int_distribution<size_t> dist(begin, end - 1);
  std::swap(iq_data[dist(rnd)], iq_data[end - 1]);
  const int pivot = iq_data[end - 1];
  size_t l_idx = begin;
  size_t r_idx = begin;
  size_t m_idx = begin;
  while (r_idx < end - 1) {
    if (iq_data[r_idx] < pivot) {
      std::swap(iq_data[l_idx], iq_data[r_idx]);
      if (l_idx != m_idx) std::swap(iq_data[r_idx], iq_data[m_idx]);
      l_idx++;
      m_idx++;
      r_idx++;
    } else if (iq_data[r_idx] == pivot) {
      std::swap(iq_data[m_idx], iq_data[r_idx]);
      m_idx++;
      r_idx++;
    } else {
      r_idx++;
    }
  }
  std::swap(iq_data[m_idx], iq_data[end - 1]);
  m_idx++;
  if(iq_data[m_idx] == pivot) m_idx++;
  return {l_idx, m_idx};
}

int find_k_stat(std::vector<int>& iq_data, size_t begin, size_t end,
                size_t k_stat, std::mt19937& rnd) {
  const PartitionResult p_res = partition(iq_data, begin, end, rnd);
  if (k_stat >= p_res.less_end - begin && k_stat < p_res.equal_end - begin) {
    return iq_data[p_res.less_end];
  } else if (k_stat < p_res.less_end - begin) {
    return find_k_stat(iq_data, begin, p_res.less_end, k_stat, rnd);
  } else {
    return find_k_stat(iq_data, p_res.equal_end, end,
                       k_stat - (p_res.equal_end - begin), rnd);
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(5
1 3 2 4 5
3
1 3 2
1 5 1
1 5 2
)";
    solution(ss);
    std::cout << "expected = 2 1 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 1 1 1 1
4
1 4 2
3 4 1
2 5 4
2 5 3
)";
    solution(ss);
    std::cout << "expected = 1 1 1 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
1 2 3 4 5 6 7
7
1 1 1
1 2 2
1 3 2
1 4 3
1 5 5
1 6 2
1 7 1
)";
    solution(ss);
    std::cout << "expected = 1 2 2 3 5 2 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
1 2 3 4 5 6 7
6
2 7 1
3 7 2
4 7 1
5 7 2
6 7 2
7 7 1
)";
    solution(ss);
    std::cout << "expected = 2 4 4 6 7 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 4 4 4
3
1 4 4
1 4 3
1 4 2
)";
    solution(ss);
    std::cout << "expected = 4 4 4\n";
  }

}

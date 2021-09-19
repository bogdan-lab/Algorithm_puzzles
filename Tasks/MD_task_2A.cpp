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

size_t partition(std::vector<int>& iq_data, size_t begin, size_t end,
                 std::mt19937& rnd);

int main() {
  run_tests();
   //solution(std::cin);
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
    //std::cout << find_k_stat(iq_data, --begin, end, --k_stat, rnd) << '\n';
    auto first = iq_data.begin() + begin - 1;
    auto stat = first + k_stat - 1;
    auto last = iq_data.begin() + end;
    std::nth_element(first, stat, last);
    std::cout << *stat << '\n';
  }
}

/*PartitionResult partition(std::vector<int>& iq_data, size_t begin, size_t end,
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
  if (iq_data[m_idx] == pivot) m_idx++;
  return {l_idx, m_idx};
}*/

size_t partition(std::vector<int>& data, size_t begin, size_t end,
                 std::mt19937& rnd) {
  std::uniform_int_distribution<size_t> dist(begin, end - 1);
  std::swap(data[dist(rnd)], data[end - 1]);
  size_t pivot = end - 1;
  size_t big_idx = pivot;
  size_t small_idx = begin;
  while (big_idx > small_idx) {
    while (big_idx > begin && data[big_idx - 1] >= data[pivot]) {
      --big_idx;
    }
    while (small_idx < data.size() && data[small_idx] < data[pivot]) {
      ++small_idx;
    }
    if (small_idx < big_idx) {
      std::swap(data[small_idx], data[big_idx - 1]);
    }
  }
  std::swap(data[pivot], data[big_idx]);
  return big_idx;
}

int find_k_stat(std::vector<int>& iq_data, size_t begin, size_t end,
                size_t k_stat, std::mt19937& rnd) {
  if (end - begin == 1) return iq_data[begin];
  const size_t p_res = partition(iq_data, begin, end, rnd);

  if (k_stat == p_res - begin) {
    return iq_data[p_res];
  } else if (k_stat > p_res - begin) {
    return find_k_stat(iq_data, p_res + 1, end, k_stat - (p_res - begin + 1),
                       rnd);
  } else {
    return find_k_stat(iq_data, begin, p_res, k_stat, rnd);
  }
}

/*

int find_k_stat(std::vector<int>& iq_data, size_t begin, size_t end,
                size_t k_stat, std::mt19937& rnd) {
  std::vector<int> slice(iq_data.begin() + begin, iq_data.begin() + end);
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
*/
void run_tests() {
  {
    std::stringstream ss;
    ss << R"(5
1 3 2 4 5
4
1 3 2
1 5 1
1 5 2
1 3 3
)";
    solution(ss);
    std::cout << "expected = 2 1 2 3\n";
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
  {

    std::stringstream ss;
    ss << R"(1
1
1
1 1 1
)";
    solution(ss);
    std::cout << "expected = 1\n";
  }
  /*{
    std::stringstream ss;
    ss << R"(122
725830443 212032328 532627309 952328364 13652509 693434078 306990073 720969247
876116360 340292920 924888990 944107530 908937853 277488835 986689851 584133356
270841733 682975782 810720100 237364992 494500518 904089058 803364940 782210906
598947388 833704098 193911974 704548411 57829816 190512691 343661632 585218198
808728742 289192279 579344087 46357448 781627332 176968565 115903681 141442696
735833142 779514996 98645613 878090311 229256088 524409204 543155197 161787238
902698006 367631627 786839668 443902534 582222763 814094954 633881008 798245209
545847982 657066113 319490224 113742238 606687749 162746374 739684968 100670728
937723338 619734555 683212636 941820231 817248032 465789754 171875612 172709410
495593563 599193391 10019748 871612306 264869409 796407259 780032322 946450561
298395105 106491674 208256377 431101240 944695760 859069659 706050009 219081595
333857399 596017923 797090150 787129312 875226700 661409338 660327863 201890023
738609937 381591275 402932252 841590020 578420067 595096189 562811625 5615254
910584379 817107607 901904463 37915278 894083843 800725557 11845108 217411844
804818335 814622574 395073375 728403717 351040147 812032996 159867325 904058808
328140030 505001234
1
107 115 10
)";
    solution(ss);
    std::cout << "expected = 574526736\n";
  }*/
}

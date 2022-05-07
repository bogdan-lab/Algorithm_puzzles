#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int kMaxValue = 1'000'001;

struct Health {
  Health(int g_health) {
    if (g_health <= 0) return;
    health = g_health;
    count_c_hits = (health + 1) / 2;
  }

  int health = 0;
  int count_c_hits = 0;
};

int SolveForTriplet(const std::vector<Health>& data, size_t index,
                    const std::vector<int>& pref_min_c_counts);

int SimpleShotCount(Health first, Health second);
int ShotParallel(Health first, Health second);
int ShotByOnes(Health lhs, Health rhs);
std::vector<int> GetPrefixMinCCounts(const std::vector<Health>& data);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<Health> data;
  data.reserve(n);
  while (n--) {
    int tmp = 0;
    input >> tmp;
    data.push_back(Health(tmp));
  }
  int min_val = std::min({SimpleShotCount(data[0], data[1]),
                          SimpleShotCount(data[1], data[0]),
                          ShotParallel(data[0], data[1])});
  // pref_...[i] stores min counts for all values before i
  std::vector<int> pref_min_c_counts = GetPrefixMinCCounts(data);
  for (size_t i = 0; i < data.size() - 2; ++i) {
    min_val = std::min(min_val, SolveForTriplet(data, i, pref_min_c_counts));
  }
  std::cout << min_val << '\n';
}

int SolveForTriplet(const std::vector<Health>& data, size_t index,
                    const std::vector<int>& pref_min_c_counts) {
  return std::min(
      {SimpleShotCount(data[index], data[index + 1]),
       SimpleShotCount(data[index + 1], data[index]),
       ShotParallel(data[index + 1], data[index]),
       ShotByOnes(data[index], data[index + 2]),
       SimpleShotCount(data[index + 1], data[index + 2]),
       SimpleShotCount(data[index + 2], data[index + 1]),
       ShotParallel(data[index + 2], data[index + 1]),
       data[index].count_c_hits + pref_min_c_counts[index],
       data[index + 1].count_c_hits + pref_min_c_counts[index + 1],
       data[index + 2].count_c_hits + pref_min_c_counts[index + 2]});
}

int SimpleShotCount(Health first, Health second) {
  return first.count_c_hits + std::max(0, second.health - first.count_c_hits);
}

int ShotParallel(Health first, Health second) {
  int count_pair_shot = std::min(first.health, second.health) / 3;
  int damage = count_pair_shot * 3;
  first = Health(first.health - damage);
  second = Health(second.health - damage);
  return 2 * count_pair_shot + std::min(SimpleShotCount(first, second),
                                        SimpleShotCount(second, first));
}

int ShotByOnes(Health lhs, Health rhs) {
  if (lhs.health < rhs.health) {
    return lhs.health + (rhs.health - lhs.health + 1) / 2;
  } else {
    return rhs.health + (lhs.health - rhs.health + 1) / 2;
  }
}

std::vector<int> GetPrefixMinCCounts(const std::vector<Health>& data) {
  std::vector<int> res(data.size(), kMaxValue);
  for (size_t i = 1; i < data.size(); ++i) {
    res[i] = std::min(res[i - 1], data[i - 1].count_c_hits);
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
20 10 30 10 20
)";
    Solution(ss);
    std::cout << "expected = 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 8 1
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
7 6 6 8 5 8
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
14 3 8 10 15 4
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 100 100 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
40 10 10
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
3 89 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
}

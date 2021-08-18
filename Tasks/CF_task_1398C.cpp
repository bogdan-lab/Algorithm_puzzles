#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>


using Table = std::vector<std::vector<int>>;

void solution(std::istream& input = std::cin);
void run_tests();
int to_int(char ch);

uint64_t count_good_intervals(const std::vector<int>& full);
std::vector<int> get_integral(const std::vector<int>& full);

int main() {
  //run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> full_interval;
    full_interval.reserve(n);
    std::string rec;
    input >> rec;
    for (size_t i = 0; i < rec.size(); ++i) {
      full_interval.push_back(to_int(rec[i]));
    }

    std::cout << count_good_intervals(full_interval) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(3
3
120
5
11011
6
600005
)";
    solution(ss);
    std::cout << "expected = 3 6 1\n";
  }
}

int to_int(char ch) { return static_cast<int>(ch) - 48; }

std::vector<int> get_integral(const std::vector<int>& full) {
  std::vector<int> res(full.size())  ;
  int sum = 0;
  for (size_t i = 0; i < res.size(); ++i) {
    sum += full[i];
      res[i] = sum;
  }
  return res;
}


uint64_t count_good_intervals(const std::vector<int>& full){
    std::vector<int> integral = get_integral(full);
    std::unordered_map<int, uint64_t> point_count;
    for(int i=0; i<integral.size(); ++i){
        point_count[integral[i]-i-1]++;
    }
    uint64_t count = 0;
    for(const auto& el : point_count){
        count += ((el.second - 1)*el.second)/2;
    }
    count += point_count[0];
    return count;
}


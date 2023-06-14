#include <deque>
#include <iostream>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::deque<int> ReadHand(std::istream& input) {
  int k;
  input >> k;
  std::deque<int> hand;
  while (k--) {
    int v;
    input >> v;
    hand.push_back(v);
  }
  return hand;
}

void Play(std::deque<int>& lhs, std::deque<int>& rhs) {
  if (lhs.front() < rhs.front()) {
    rhs.push_back(lhs.front());
    rhs.push_back(rhs.front());
  } else {
    lhs.push_back(rhs.front());
    lhs.push_back(lhs.front());
  }
  lhs.pop_front();
  rhs.pop_front();
}

void PrintAnswer(uint64_t count, int winner) {
  if (count) std::cout << count << ' ';
  std::cout << winner << '\n';
}

bool CheckWin(const std::deque<int>& first, const std::deque<int>& second,
              uint64_t count) {
  if (first.empty()) {
    PrintAnswer(count, 2);
    return true;
  }
  if (second.empty()) {
    PrintAnswer(count, 1);
    return true;
  }
  return false;
}

bool CheckCycle(const std::deque<int>& l, const std::deque<int>& r,
                const std::deque<int>& lf, const std::deque<int>& rf) {
  if (l.size() != lf.size() || r.size() != rf.size()) return false;
  for (size_t i = 0; i < l.size(); ++i) {
    if (l[i] != lf[i]) return false;
  }
  for (size_t i = 0; i < r.size(); ++i) {
    if (r[i] != rf[i]) return false;
  }
  return true;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::deque<int> first = ReadHand(input);
  std::deque<int> second = ReadHand(input);

  std::deque<int> first_faster = first;
  std::deque<int> second_faster = second;

  uint64_t faster_count = 0;
  while (true) {
    Play(first_faster, second_faster);
    ++faster_count;
    if (CheckWin(first_faster, second_faster, faster_count)) return;
    Play(first_faster, second_faster);
    ++faster_count;
    if (CheckWin(first_faster, second_faster, faster_count)) return;

    Play(first, second);
    if (CheckCycle(first, second, first_faster, second_faster)) {
      PrintAnswer(0, -1);
      return;
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

#include <cmath>
#include <iostream>

void solution(std::istream& input = std::cin) {
  double r, x1, y1, x2, y2;
  input >> r >> x1 >> y1 >> x2 >> y2;
  double dist = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  std::cout << std::ceil(dist / (2 * r)) << '\n';
}

int main() {
  solution(std::cin);
  return 0;
}

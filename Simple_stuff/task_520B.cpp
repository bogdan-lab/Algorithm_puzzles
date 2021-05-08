#include <iostream>

int calc_btn_cnt(int n, int m, int btn_cnt) {
  if (n >= m) {
    return btn_cnt + n-m;
  }
  //here n<m
  if(m%2){
      return calc_btn_cnt(n, m+1, ++btn_cnt);
  }
  else {
      return calc_btn_cnt(n, m/2, ++btn_cnt);
  }
}

int solution(std::istream& input = std::cin) {
  int n, m;
  input >> n >> m;
  return calc_btn_cnt(n, m, 0);
}

int main() {
  std::cout << solution();

  return 0;
}


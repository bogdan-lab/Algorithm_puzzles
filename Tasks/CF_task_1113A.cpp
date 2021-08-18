#include <iostream>




int main(){
    unsigned short n, v;
    std::cin >> n >> v;
    unsigned short pass_num = n-1;
    if (pass_num<v){
        std::cout << pass_num << '\n';
        return 0;
    }
    unsigned remain = pass_num - v;
    unsigned sum = v;
    unsigned delta = 2;
    while(remain--){
        sum += delta;
        delta++;
    }
    std::cout << sum << '\n';
    return 0;
}

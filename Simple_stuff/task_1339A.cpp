#include<iostream>

typedef unsigned long long ull;

ull power(const unsigned val, const unsigned p){
    ull res = 1;
    unsigned idx = p;
    while(idx--){
        res *= static_cast<ull>(val);
    }
    return res;
}

int main(){
    unsigned t;
    std::cin >> t;
    while(t--){
        unsigned n;
        std::cin>>n;
        std::cout << n << '\n';
    }
    return 0;
}

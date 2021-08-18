#include <iostream>
#include<string>


void do_case(const std::string& bin_str, const unsigned l, const unsigned r){
    size_t prefix_res = bin_str.find(bin_str[l-1]);
    size_t suffix_res = bin_str.find(bin_str[r-1], r);
    if(prefix_res==l-1 && suffix_res==std::string::npos){
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
}


int main(){
    unsigned t;
    std::cin>>t;
    while(t--){
        unsigned size;
        unsigned q;
        std::cin >> size >> q;
        std::string bin_str;
        std::cin >> bin_str;
        while(q--){
            unsigned l, r;
            std::cin >> l >> r;
            do_case(bin_str, l ,r);
        }
    }
    return 0;
}

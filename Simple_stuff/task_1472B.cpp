#include<iostream>
#include<cstdlib>

int main(){
    unsigned t;
    std::cin>>t;
    for(unsigned i=0; i<t; i++){
        unsigned n;
        std::cin >> n;
        unsigned num_2=0;
        unsigned num_1=0;
        int tmp;
        for(unsigned k=0; k<n; k++){
            std::cin >> tmp;
            num_2 += --tmp;
            num_1 += std::abs(--tmp);
        }
        if((num_2%2==0 && num_1%2==0)
                || (num_2%2!=0 && num_1%2==0 && num_1!=0)){
            std::cout << "YES\n";
        }
        else{
            std::cout << "NO\n";
        }
    }
}


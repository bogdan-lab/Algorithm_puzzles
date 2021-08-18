#include<iostream>


int main(){
    unsigned n;
    std::cin >> n;
    unsigned minus_num = 0;
    unsigned zero_num = 0;
    unsigned long long cost = 0;
    for(unsigned i=0; i<n; i++){
        int tmp;
        std::cin >> tmp;
        if(tmp>0){
            cost += --tmp;
        }
        else if(tmp<0){
            cost += -(++tmp);
            minus_num++;
        }
        else{
            cost++;
            zero_num++;
        }
    }
    if(zero_num>0 || minus_num%2==0){
        std::cout << cost << '\n';
    }
    else {
        std::cout << cost+2 << '\n';
    }
    return 0;
}

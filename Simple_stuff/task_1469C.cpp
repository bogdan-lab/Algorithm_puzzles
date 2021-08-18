#include <algorithm>
#include <iostream>
#include <stdint.h>


void check_data_set(const int n, const int k, const int* h){
    int max_pos = h[0] + k - 1;
    int min_pos = h[0]+1<k ? 0 : h[0]-k+1;
    for(int i=1; i<n-1; i++){
        if(!(h[i]<=max_pos && h[i]+k-1>=min_pos)){
            std::cout << "NO\n";
            return;
        }
        max_pos = std::min(h[i]+k-1, max_pos) + k - 1;
        min_pos = std::max(h[i], min_pos);
        min_pos = min_pos+1<k ? 0 : min_pos - k + 1;
    }
    //add check about final is on the ground!
    if(!(h[n-1]<=max_pos && h[n-1]>=min_pos)){
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
    return;
}



int main(){
    int t;
    int h[200000];

    std::cin >> t;
    for(int i=0; i<t; i++){
        int n, k;
        std::cin >> n >> k;
        for(int j=0; j<n; j++){
            std::cin >> h[j];
        }
        check_data_set(n, k, h);
    }
    return 0;
}

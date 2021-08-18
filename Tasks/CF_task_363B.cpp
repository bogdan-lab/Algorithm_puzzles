#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

typedef std::vector<unsigned short> Collection;



unsigned get_min_sum_idx(const Collection& fence, const unsigned k){
    if(fence.size()==k) return 1u;
    unsigned idx = 0u;
    unsigned sum = std::accumulate(fence.begin(), fence.begin()+k, 0);
    unsigned min_sum = sum;
    for(unsigned i=1; i<fence.size()-k+1; i++){
        sum += fence[i+k-1] - fence[i-1];
        if(min_sum>sum){
            min_sum = sum;
            idx = i;
        }
    }
    return idx+1u;
}


int main(){
    unsigned n, k;
    std::cin >> n >> k;
    Collection fence;
    fence.reserve(n);
    std::copy_n(std::istream_iterator<unsigned short>(std::cin), n, std::back_inserter(fence));
    std::cout << get_min_sum_idx(fence, k) << '\n';
    return 0;
}

#include<iostream>
#include<algorithm>
#include<iterator>
#include<vector>


typedef std::vector<unsigned int> Collection;

int main(){
    size_t n;
    std::cin>>n;
    Collection vec;
    vec.reserve(n);
    std::copy_n(std::istream_iterator<unsigned int>(std::cin), n, std::back_inserter(vec));
    unsigned int max_res = 0;
    unsigned int cur_res = 1;
    for(unsigned int i=1; i<vec.size(); i++){
        if(vec[i]>vec[i-1]) {
            cur_res++;
        } else{
            max_res = std::max(max_res, cur_res);
            cur_res = 1;
        }
    }
    max_res = std::max(max_res, cur_res);
    std::cout << max_res << '\n';
    return 0;
}

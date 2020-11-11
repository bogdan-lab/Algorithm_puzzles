#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

size_t parent(size_t i){
    return (i-1)/2;
}

size_t left(size_t i){
    return 2*i+1;
}

size_t right(size_t i){
    return 2*(i+1);
}


void max_heapify(std::vector<int>& vec, size_t idx){
    size_t l_idx = left(idx);
    size_t r_idx = right(idx);
    if(l_idx>=vec.size()){
        return;
    }
    size_t max_idx = r_idx>=vec.size()
                     ? l_idx
                     : std::max(r_idx, l_idx,
                                [&vec](const size_t l, const size_t r)
                                            {return vec[l]<vec[r];});
    if (vec[idx]>=vec[max_idx]){
        return;
    }
    std::swap(vec[idx], vec[max_idx]);
    max_heapify(vec, max_idx);
}

void build_heap(std::vector<int>& vec){
    for(size_t i=vec.size()/2+1; i!=0; i--){
        max_heapify(vec, i-1);
    }
}

std::vector<int> generate_vector(size_t s){
    std::vector<int> vec;
    vec.reserve(s);
    std::mt19937 rnd_gen(42u);
    std::uniform_int_distribution<int> dist(-100, 100);
    for(size_t i=0; i<s; i++){
        vec.push_back(dist(rnd_gen));
    }
    return vec;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec){
    for(const auto& el : vec){
        out << el << " ";
    }
    out << "\n";
    return out;
}

int main(){

    for(size_t i=10; i<1000; i++){
        std::vector<int> vec = generate_vector(i);
        build_heap(vec);
        if(!std::is_heap(vec.begin(), vec.end())){
            std::cout << "NOT HEAP\n";
            std::cout << vec;
            break;
        }
    }
    std::cout << "HEAP IS BUILD FINE!";

    return 0;
}

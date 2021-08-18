#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

size_t left(size_t i){
    return 2*i+1;
}

size_t right(size_t i){
    return 2*(i+1);
}


void max_heapify(std::vector<int>& vec, size_t idx, size_t heap_size){
    size_t l_idx = left(idx);
    size_t r_idx = right(idx);
    if(l_idx>=heap_size){
        return;
    }
    auto comp = [&vec](const size_t l, const size_t r){return vec[l]<vec[r];};
    size_t max_idx = r_idx>=heap_size
                     ? l_idx : std::max(r_idx, l_idx, comp);
    if (vec[idx]>=vec[max_idx]){
        return;
    }
    std::swap(vec[idx], vec[max_idx]);
    max_heapify(vec, max_idx, heap_size);
}

void build_heap(std::vector<int>& vec, size_t heap_size){
    for(size_t i=heap_size/2+1; i!=0; i--){
        max_heapify(vec, i-1, heap_size);
    }
}

void heap_sort(std::vector<int>& vec){
    if(vec.size()==0){return;}
    size_t heap_size = vec.size();
    build_heap(vec, heap_size);
    while(heap_size!=1){
        std::swap(vec[0], vec[heap_size-1]);
        heap_size--;
        max_heapify(vec, 0, heap_size);
    }
}

std::vector<int> generate_vector(size_t s, std::mt19937& rnd_gen){
    std::vector<int> vec;
    vec.reserve(s);
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

    std::random_device device;
    std::mt19937 rnd_gen(device());
    //CHECK BUILD HEAP
    for(size_t i=0; i<1000; i++){
        std::vector<int> vec = generate_vector(i, rnd_gen);
        build_heap(vec, vec.size());
        if(!std::is_heap(vec.begin(), vec.end())){
            std::cout << "NOT HEAP\n";
            std::cout << vec;
            break;
        }
    }
    std::cout << "HEAP IS BUILD FINE!\n";
    //CHECK HEAP SORT
    for(size_t i=0; i<1000; i++){
        std::vector<int> vec = generate_vector(i, rnd_gen);
        heap_sort(vec);
        if(!std::is_sorted(vec.begin(), vec.end())){
            std::cout<<"NOT SORTED\n";
            std::cout << vec;
            break;
        }
    }
    std::cout << "SORTING IS FINE!";

    return 0;
}

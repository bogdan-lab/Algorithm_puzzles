#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#define LEFT(I) 2*I+1
#define RIGHT(I) 2*(I+1)


class PriorityQueu{
    /*
     * Takes vector as input so key of each element --> its index in vector*/
private:
    std::vector<size_t> pos_to_key_ = {}; 	//pos = idx in prior_queu, key = idx
    std::vector<size_t> key_to_pos_ = {}; 	//key = idx, pos = idx in prior_queu
    size_t next_key_ = {};
    //key -> index in queu
    //take (key + corresponding priority)
    //Order keys according to priorities so can pop next one
    //want const access to priority of given key
    std::vector<int> prior_queu_ = {};

    size_t MaxHeapify(size_t idx){
        size_t left = LEFT(idx);
        size_t right = RIGHT(idx);
        if(left>=prior_queu_.size()){return idx; }  //reached final element
        auto comp = [&](size_t l, size_t r)
                {return this->prior_queu_[l]<this->prior_queu_[r];};
        size_t max_idx = right==prior_queu_.size() ? left : std::max(left, right, comp);
        if(prior_queu_[max_idx]<=prior_queu_[idx]){return idx;}
        std::swap(prior_queu_[idx], prior_queu_[max_idx]);
        size_t swapped_key = pos_to_key_[max_idx];
        key_to_pos_[swapped_key] = idx;
        std::swap(pos_to_key_[idx], pos_to_key_[max_idx]);
        return MaxHeapify(max_idx);
    }

    void BuildHeap(){
        for(size_t i=prior_queu_.size()/2+1; i!=0; i--){
            key_to_pos_[i-1] = MaxHeapify(i-1);
        }
    }
public:
    PriorityQueu() = default;
    PriorityQueu(std::vector<int>&& priorities): prior_queu_(priorities){
        key_to_pos_.resize(prior_queu_.size());
        std::iota(key_to_pos_.begin(), key_to_pos_.end(), 0);
        pos_to_key_.resize(prior_queu_.size());
        std::iota(pos_to_key_.begin(), pos_to_key_.end(), 0);
        BuildHeap();
    }

    bool CheckHeapity() const {
        return std::is_heap(prior_queu_.begin(), prior_queu_.end());
    }

    int GetVal(size_t key) const {
        size_t pos = key_to_pos_[key];
        return prior_queu_[pos];
    }

    bool Insert(size_t key, int priority){}
    size_t Maximum() const {} //returns max priority element key
    size_t PopMaximum(){} 	//returns and delete max priority key
    void ChangePriority(size_t key, int new_priority){} 	//changes priority of element

    void PrintQueu() const {
        for(size_t i=0; i<key_to_pos_.size(); i++){
            printf("P = %i;\tK = %zu\n", prior_queu_[i], pos_to_key_[i]);
        }
    }
};






int main(){
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    PriorityQueu pq(std::move(vec));

    pq.PrintQueu();

    for(size_t i=0; i<vec.size(); i++){
        std::cout << "key = " << i << " --> " << pq.GetVal(i) << " ? " << i+1 << "\n";
    }

    std::cout << pq.CheckHeapity();



    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <string>

#define LEFT(I) 2*I+1
#define RIGHT(I) 2*(I+1)


class PriorityQueu{
    /*
     * Takes vector as input so key of each element --> its index in vector*/
private:
    //TODO make key and priority - template paramters
    //TODO check stuff for copying
    //TODO write other methods which are now commented
    std::unordered_map<size_t, std::string> pos_to_key_ = {}; 	//pos = idx in prior_queu, key = idx
    std::unordered_map<std::string, size_t> key_to_pos_ = {}; 	//key = idx, pos = idx in prior_queu
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
        std::string swapped_key = pos_to_key_[max_idx];
        key_to_pos_[swapped_key] = idx;
        std::swap(pos_to_key_[idx], pos_to_key_[max_idx]);
        return MaxHeapify(max_idx);
    }

    void BuildHeap(){
        for(size_t i=prior_queu_.size()/2+1; i!=0; i--){
            std::string key = pos_to_key_[i-1];
            key_to_pos_[key] = MaxHeapify(i-1);
        }
    }
public:
    PriorityQueu() = default;
    PriorityQueu(std::vector<int>&& priorities, std::vector<std::string>&& keys)
        : prior_queu_(priorities){
        for(size_t i=0; i<prior_queu_.size(); i++){
            key_to_pos_[keys[i]] = i;
            pos_to_key_[i] = keys[i];
        }
        BuildHeap();
    }

    bool CheckHeapity() const {
        return std::is_heap(prior_queu_.begin(), prior_queu_.end());
    }

    int GetPriority(const std::string& key) const {
        size_t pos = key_to_pos_.at(key);
        return prior_queu_[pos];
    }
    /*
    bool Insert(size_t key, int priority){ return true;}
    size_t Maximum() const {return 0;} //returns max priority element key
    size_t PopMaximum(){return 0;} 	//returns and delete max priority key
    void ChangePriority(size_t key, int new_priority){} 	//changes priority of element
*/
    void PrintQueu() const {
        for(size_t i=0; i<key_to_pos_.size(); i++){
            printf("P = %i;\tK = %s\n", prior_queu_[i], pos_to_key_.at(i).c_str());
        }
    }
};



int main(){
    std::vector<int> vec = {1,2,3,4,5,6,7};
    std::vector<std::string> keys = {"one", "two", "three", "four", "five", "six", "seven"};
    PriorityQueu pq(std::move(vec), std::move(keys));

    pq.PrintQueu();

    for(const auto& el : keys){
        printf("K = %s;\t P = %i\n", el.c_str(), pq.GetPriority(el));
    }

    std::cout << pq.CheckHeapity();
    return 0;
}

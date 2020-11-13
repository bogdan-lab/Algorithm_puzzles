#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#define PARENT(I) (I-1)/2
#define LEFT(I) 2*I+1
#define RIGHT(I) 2*(I+1)


template <typename KeyT, typename PriorT>
class PriorityQueu{
private:
    std::vector<PriorT> prior_queu_ = {};
    std::vector<KeyT> pos_to_key_ = {}; 	//pos = idx in prior_queu, key = idx
    std::unordered_map<KeyT, size_t> key_to_pos_ = {}; 	//key = idx, pos = idx in prior_queu
    PriorT min_priority_ = {};

    void MaxHeapify(size_t idx){
        size_t left = LEFT(idx);
        size_t right = RIGHT(idx);
        if(left>=prior_queu_.size()){return ; }  //reached final element
        auto comp = [&](size_t l, size_t r)
                {return this->prior_queu_[l]<this->prior_queu_[r];};
        size_t max_idx = right==prior_queu_.size() ? left : std::max(left, right, comp);
        if(prior_queu_[max_idx]<=prior_queu_[idx]){return ;}
        std::swap(prior_queu_[idx], prior_queu_[max_idx]);
        std::swap(key_to_pos_[pos_to_key_[max_idx]], key_to_pos_[pos_to_key_[idx]]);
        std::swap(pos_to_key_[idx], pos_to_key_[max_idx]);
        MaxHeapify(max_idx);
    }

    void BuildHeap(){
        if(prior_queu_.empty()){return;}
        for(size_t i=prior_queu_.size()/2+1; i!=0; i--){
            MaxHeapify(i-1);
        }
    }

    void IncreasePriority(KeyT key, PriorT prior_new){
        size_t pos = key_to_pos_.at(key);
        prior_queu_[pos] = prior_new;
        while(pos!=0 && prior_queu_[PARENT(pos)]<prior_queu_[pos]){
            std::swap(prior_queu_[PARENT(pos)], prior_queu_[pos]);
            std::swap(pos_to_key_[PARENT(pos)], pos_to_key_[pos]);
            std::swap(key_to_pos_[pos_to_key_[PARENT(pos)]], key_to_pos_[pos_to_key_[pos]]);
            pos = PARENT(pos);
        }
    }

    void DecreasePriority(KeyT key, PriorT prior_new){
        size_t pos = key_to_pos_.at(key);
        prior_queu_[pos] = prior_new;
        MaxHeapify(pos);
        min_priority_ = std::min(prior_new, min_priority_);
    }

public:
    PriorityQueu() = default;
    PriorityQueu(std::vector<PriorT>&& priorities, std::vector<KeyT>&& keys)
        : prior_queu_(priorities), pos_to_key_(keys){
        if(keys.size()!=prior_queu_.size()){
            fprintf(stderr, "Incorrect size of priority or keys\n");
            exit(1);
        }
        for(size_t i=0; i<prior_queu_.size(); i++){
            key_to_pos_[pos_to_key_[i]] = i;
        }
        BuildHeap();
        auto second_half = prior_queu_.begin();
        std::advance(second_half, prior_queu_.size()/2);
        auto it = std::min_element(second_half, prior_queu_.end());
        if(it!=prior_queu_.end()){
            min_priority_ = *it;
        }
    }

    const KeyT& Maximum() const {
        return pos_to_key_[0];
    }

    KeyT PopMaximum(){
        std::swap(prior_queu_[0], prior_queu_.back());
        std::swap(pos_to_key_[0], pos_to_key_.back());
        key_to_pos_.erase(pos_to_key_.back());
        KeyT max_key = std::move(pos_to_key_.back());
        pos_to_key_.pop_back();
        prior_queu_.pop_back();
        key_to_pos_[pos_to_key_[0]] = 0;
        MaxHeapify(0);
        return max_key;
    }

    bool ChangePriority(KeyT key, PriorT prior_new){
        if(key_to_pos_.count(key)==0){return false;}
        if(GetPriority(key)<prior_new){
            IncreasePriority(key, prior_new);
        }
        else if (GetPriority(key)>prior_new){
            DecreasePriority(key, prior_new);
        }
        return true;
    }

    bool Insert(KeyT key, PriorT given_priority){
        if(key_to_pos_.count(key)>0){return false;}
        prior_queu_.push_back(min_priority_);
        pos_to_key_.push_back(key);
        key_to_pos_[key] = prior_queu_.size()-1;
        ChangePriority(key, given_priority);
        return true;
    }

    size_t ElementNum() const {
        return prior_queu_.size();
    }

    bool Empty() const {
        return prior_queu_.empty();
    }

    bool CheckHeapity() const {
        return std::is_heap(prior_queu_.begin(), prior_queu_.end());
    }

    const PriorT& GetPriority(const KeyT& key) const {
        size_t pos = key_to_pos_.at(key);
        return prior_queu_[pos];
    }

};



TEST_CASE("Building priority queu" "[build]"){
    std::vector<int> r;
    std::vector<int> keys;
    PriorityQueu<int, int> pq(std::move(keys), std::move(r));
    CHECK(pq.CheckHeapity());
    r.assign({1,2,3,4,5,6,7,8});
    keys.assign(r.begin(), r.end());
    PriorityQueu<int, int> pq2(std::move(keys), std::move(r));
    CHECK(pq2.CheckHeapity());
    r.assign({13, 53, 178, 235, 387, 654, 1, 39, 11});
    PriorityQueu<int, int> pq3(std::move(r), std::move(r));
    CHECK(pq3.CheckHeapity());
}

TEST_CASE("Extracting from queu", "[extract]"){
    std::vector<int> p = {1,205,32,41,-5,639,7,81,9};
    std::vector<int> correct = {639, 205, 81, 41, 32, 9, 7, 1, -5};
    PriorityQueu<int, int> pq(std::move(p), std::move(p));
    size_t idx = 0;
    while (!pq.Empty()) {
        int k = pq.PopMaximum();
        CHECK(k==correct[idx]);
        idx++;
    }
}

TEST_CASE("Change priority", "[ChangePriority]"){
    std::vector<int> p = {1,2,3,4,5,6,7,8,9};
    PriorityQueu<int, int> pq(std::move(p), std::move(p));
    CHECK(9==pq.Maximum());
    CHECK(pq.ChangePriority(1, 12));
    CHECK(1==pq.Maximum());
    CHECK(pq.ChangePriority(1, 3));
    CHECK(pq.ChangePriority(5, 25));
    CHECK(5==pq.Maximum());
    CHECK_FALSE(pq.ChangePriority(25, 135));
}

TEST_CASE("Inserting elements", "[Insert]"){
    PriorityQueu<int, int> pq;
    std::vector<int> p = {13, 56, 5, 17, 89, 674, 123};
    for(size_t i=0; i<p.size(); i++){
        CHECK(pq.Insert(p[i], p[i]));
        CHECK(pq.CheckHeapity());
    }
    CHECK(674==pq.Maximum());
    CHECK_FALSE(pq.Insert(13, 895));
}

/*Задача - Найти количество инверсий в массиве за nlog(n).
 * Инверсия это когда i<j, но A[i]>A[j]                   */

#include <iostream>
#include <vector>
#include <assert.h>

void swap(int& lhs, int& rhs){
    int tmp = rhs;
    rhs = lhs;
    lhs = tmp;
}


size_t merge(std::vector<int>::iterator begin, std::vector<int>::iterator mid, std::vector<int>::iterator end){
    std::vector<int> lhs(begin, mid);
    std::vector<int> rhs(mid, end);
    size_t lhs_id = 0;
    size_t rhs_id = 0;
    size_t count = 0;
    for(int i=0; i<end-begin; i++){
        if(lhs_id>=lhs.size()){
            *(begin+i) = rhs[rhs_id];
            rhs_id++;
        }
        else if (rhs_id>=rhs.size()){
            *(begin+i) = lhs[lhs_id];
            lhs_id++;
        }
        else if(lhs[lhs_id]<=rhs[rhs_id]){
            *(begin+i) = lhs[lhs_id];
            lhs_id++;
        }
        else {
            *(begin+i) = rhs[rhs_id];
            rhs_id++;
            count += lhs.size() - lhs_id;
        }
    }
    return count;
}


size_t calculate_inversions(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    if(end-begin==1){
        return 0;
    }
    size_t count = 0;
    std::vector<int>::iterator mid = begin + (end-begin)/2;
    count += calculate_inversions(begin, mid);
    count += calculate_inversions(mid, end);
    count += merge(begin, mid, end);
    return count;
}



int main(){
    {
        std::vector<int> test = {2,3,8,6,1};
        size_t res = calculate_inversions(test.begin(), test.end());
        assert(res==5);
    }
    {
        std::vector<int> test={5, 4, 3, 2, 1};
        size_t res = calculate_inversions(test.begin(), test.end());
        assert(res==10);
    }
    {
        std::vector<int> test={1,2,3,4,5};
        size_t res = calculate_inversions(test.begin(), test.end());
        assert(res==0);
    }
    return 0;
}

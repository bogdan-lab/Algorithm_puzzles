/*На складе n поддонов. У каждого есть длина и ширина.
 * Поддон можно опставить на другой поддон, если первый на нем полностью помещается
 * (Длина и ширина одного строго меньше длины и ширины другого)
 * Найти количество поддонов, которые нельзя поставить ни на один дугой*/


#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <sstream>
#include <assert.h>

using PelletMap = std::map<size_t, std::vector<size_t>>;

struct Pellet{
    size_t min_;
    size_t max_;
};

std::vector<Pellet> ReadInput(std::istream& input){
    size_t n;
    input >> n;
    std::vector<Pellet> pellets;
    pellets.reserve(n);
    for(size_t i=0; i<n; i++){
        size_t h, w;
        input >> h >> w;
        pellets.push_back({std::min(h, w), std::max(h, w)});
    }
    return pellets;
}

PelletMap OrganizePellets(const std::vector<Pellet>& pellets){
    PelletMap org_pellets;
    for(size_t i=0; i<pellets.size(); i++){
        org_pellets[pellets[i].max_].push_back(pellets[i].min_);
    }
    return org_pellets;
}

size_t CountBadPellets(const PelletMap& org_pellets){
    if(org_pellets.empty()){return 0;}
    auto it = org_pellets.rbegin();
    size_t count = it->second.size();
    size_t max_min = *(std::max_element(it->second.cbegin(), it->second.cend()));
    it = std::next(it);
    while(it!=org_pellets.rend()){
        for(size_t i=0; i<it->second.size(); i++){
            if(max_min<it->second[i]){
                max_min = it->second[i];
                count++;
            }
        }
        it = std::next(it);
    }
    return count;
}

size_t SolveProblem(std::istream& input){
    std::vector<Pellet> pellets = ReadInput(input);
    PelletMap org_pellets = OrganizePellets(pellets);
    size_t count = CountBadPellets(org_pellets);
    std::cout << "I counted " << count << " bad pellets\n";
    return count;
}

int main(){
    {
        std::stringstream ss;
        ss << R"(4
              1 4
              3 2
              5 5
              2 6)";
        size_t count = SolveProblem(ss);
        assert(count==2);
    }

    {
        std::stringstream ss;
        ss << R"(4
              120 6
              120 1
              120 85
              120 95)";
        size_t count = SolveProblem(ss);
        assert(count==4);
    }

    {
        std::stringstream ss;
        ss << R"(0)";
        size_t count = SolveProblem(ss);
        assert(count==0);
    }

    {
        std::stringstream ss;
        ss << R"(5
              20 5
              20 13
              18 15
              13 18
              1 13)";
        size_t count = SolveProblem(ss);
        assert(count==3);
    }
    return 0;
}

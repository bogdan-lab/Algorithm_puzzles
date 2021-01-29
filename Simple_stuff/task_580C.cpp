#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>
#include <unordered_set>


#include <sstream>

using Graph = std::vector<std::stack<unsigned>>;
using FlagCol = std::vector<short>;

unsigned count_leafs(Graph graph, const std::unordered_set<unsigned>& leafs, const FlagCol& cats,
                     const unsigned max_cat_num){
    unsigned leafs_num = 0;
    unsigned nodes_num = cats.size();
    FlagCol visited(nodes_num, 0);
    unsigned cur_node = 0;
    std::stack<unsigned> parents;
    parents.push(0);
    std::stack<unsigned> cat_count;
    cat_count.push(0);
    unsigned cur_cat_num = 0;
    while(!parents.empty()){
        if(visited[cur_node]==0){
            cur_cat_num = cats[cur_node]==0 ? 0 : cur_cat_num+1;
        }
        visited[cur_node] = 1;
        if(leafs.count(cur_node)>0){
            //I am in leaf
            leafs_num++;
            cur_node = parents.top();
            parents.pop();
            cur_cat_num = cat_count.top();
            cat_count.pop();
            continue;
        }
        while(!graph[cur_node].empty() &&
                   (visited[graph[cur_node].top()]==1 ||
                    cur_cat_num + cats[graph[cur_node].top()]>max_cat_num)){
            graph[cur_node].pop();
        }
        if(graph[cur_node].empty()){
            //this node is fully studied --> go up
            cur_node = parents.top();
            parents.pop();
            cur_cat_num = cat_count.top();
            cat_count.pop();
            continue;
        }
        parents.push(cur_node);
        cat_count.push(cur_cat_num);
        cur_node = graph[cur_node].top();
    }
    return leafs_num;
}


void solve(std::istream& input = std::cin){
    unsigned n, m;
    input >> n >> m;
    FlagCol cats;
    cats.reserve(n);
    std::copy_n(std::istream_iterator<short>(input), n, std::back_inserter(cats));

    Graph graph;
    graph.resize(n);
    n--;
    while(n--){
        unsigned from, to;
        input >> from >> to;
        from--;
        to--;
        graph[from].push(to);
        graph[to].push(from);
    }
    std::unordered_set<unsigned> leafs;
    for(unsigned i=1; i<graph.size(); i++){
        if(graph[i].size()==1) leafs.insert(i);
    }
    std::cout << count_leafs(graph, leafs, cats, m) << '\n';
}


int main(){
    /*{
        std::stringstream ss;
        ss << R"(4 1
              1 1 0 0
              1 2
              1 3
              1 4)";
        solve(ss);
    }
    {
        std::stringstream ss;
        ss << R"(7 1
              1 0 1 1 0 0 0
              1 2
              1 3
              2 4
              2 5
              3 6
              3 7)";
        solve(ss);
    }*/
    solve(std::cin);
    return 0;
}

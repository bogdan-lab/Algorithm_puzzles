#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

#include <sstream>

using Graph = std::vector<std::vector<unsigned>>;
using FlagCol = std::vector<short>;

unsigned count_leafs(const Graph& graph, const FlagCol& cats,
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
        if(graph[cur_node].size()==1 && cur_node!=0){
            //I am in leaf
            leafs_num++;
            cur_node = parents.top();
            parents.pop();
            cur_cat_num = cat_count.top();
            cat_count.pop();
            continue;
        }
        unsigned i=0;
        while(i<graph[cur_node].size()
              && (visited[graph[cur_node][i]]==1
              || cur_cat_num + cats[graph[cur_node][i]]>max_cat_num)) i++;
        if(i>=graph[cur_node].size()){
            //this node is fully studied --> go up
            cur_node = parents.top();
            parents.pop();
            cur_cat_num = cat_count.top();
            cat_count.pop();
            continue;
        }
        parents.push(cur_node);
        cat_count.push(cur_cat_num);
        cur_node = graph[cur_node][i];
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
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    std::cout << count_leafs(graph, cats, m) << '\n';
}


int main(){
    solve(std::cin);
    return 0;
}

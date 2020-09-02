//O(E log V)
#include <algorithm>
#include <queue>
#include <vector>
const int INF = 1'000'000'000; //1e9

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){};
};


long long prim(std::vector<std::vector<edge>>& G){
    int V(G.size());
    long long res(0);
    //std::pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> que;
    std::vector<int> d(V, INF);
    d[0] = 0;
    que.push({0, 0});

    while(!que.empty()){
        std::pair<int, int> p(que.top()); que.pop();
        int v(p.second);
        if(d[v] < p.first) continue;
        d[v] = 0;
        res += p.first;
        for(edge &e : G[v]){
            if(d[e.to] > e.cost){
                d[e.to] = e.cost;
                que.push({d[e.to], e.to});
            }
        }
    }
    return res;
}

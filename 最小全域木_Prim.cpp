//O(E log V)
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
const int INF = 1'000'000'000; //1e9
const int NIL = -1;

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){}
};


long long prim_Cost(std::vector<std::vector<edge>>& G){
    int V{int(G.size())};
    long long res{};
    //std::pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> que;
    std::vector<int> d(V, INF);
    d[0] = 0;
    que.emplace(0, 0);

    while(!que.empty()){
        std::pair<int, int> p{que.top()}; que.pop();
        int v{p.second};
        if(d[v] < p.first) continue;
        d[v] = 0;
        res += p.first;
        for(edge &e : G[v]){
            if(d[e.to] > e.cost){
                d[e.to] = e.cost;
                que.emplace(d[e.to], e.to);
            }
        }
    }
    return res;
}

struct Edge{
    int from, to, cost;
    Edge(int From, int To, int Cost): from(From), to(To), cost(Cost){}
};

// cost, Graph
std::pair<long long, std::vector<Edge>> prim(std::vector<std::vector<edge>>& G){
    int V{int(G.size())};
    std::vector<Edge> T;
    long long total{};
    //std::pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> que;
    //cost, from
    std::vector<std::pair<int, int>> d(V, {INF, NIL});
    d[0] = {0, NIL};
    que.emplace(0, 0);

    while(!que.empty()){
        std::pair<int, int> p{que.top()}; que.pop();
        int v{p.second};
        if(d[v].first < p.first) continue;
        if(d[v].second != NIL) T.emplace_back(d[v].second, v, d[v].first);
        d[v] = {0, NIL};
        total += p.first;
        for(edge &e : G[v]){
            if(d[e.to].first > e.cost){
                d[e.to] = {e.cost, v};
                que.emplace(d[e.to].first, e.to);
            }
        }
    }
    return {total, T};
}

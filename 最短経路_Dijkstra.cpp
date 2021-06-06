//　O(E log V) 負の辺があると使えない 頂点sからの距離を求める
#include <algorithm>
#include <queue>
#include <vector>
const int NIL = -1;
const long long LINF = 1'000'000'000'000'000'000; // 1e18

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){}
};

/*
int V; //頂点数
std::vector<std::vector<edge>> G;  std::vector<int> G;
std::vector<int> d; //sからの距離
*/


void dijkstra(int s, std::vector<std::vector<edge>> &G, std::vector<long long> &d, std::vector<int> &prv){
    //pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>> que;
    int V{int(G.size())};
    d.resize(V, LINF+3);
    prv.resize(V, NIL);
    d[s] = 0;
    que.emplace(0, s);

    while(!que.empty()){
        std::pair<long long, int> p{que.top()}; que.pop();
        int v{p.second};
        if(d[v] < p.first) continue;
        for(edge &e: G[v]){
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                prv[e.to] = v;
                que.emplace(d[e.to], e.to);
            }
        }
    }
}

void dijkstraWithoutCost(int s, std::vector<std::vector<int>> &G, std::vector<long long> &d, std::vector<int> &prv){
    //pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>> que;
    int V{int(G.size())};
    d.resize(V, LINF+3);
    prv.resize(V, NIL);
    d[s] = 0;
    que.emplace(0, s);

    while(!que.empty()){
        std::pair<long long, int> p{que.top()}; que.pop();
        int v{p.second};
        if(d[v] < p.first) continue;
        for(int &u: G[v]){
            if(d[u] > d[v] + 1){
                d[u] = d[v] + 1;
                prv[u] = v;
                que.emplace(d[u], u);
            }
        }
    }
}


std::vector<int> buildPath(const std::vector<int> &prv, int t){
    std::vector<int> path;
    for(int u = t; u >= 0; u = prv[u]){
        path.push_back(u);
    }
    reverse(path.begin(), path.end());
    return path;
}

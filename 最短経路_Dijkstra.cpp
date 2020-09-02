//　O(V log E) 負の辺があると使えない 頂点sからの距離を求める
#include <algorithm>
#include <queue>
#include <vector>
const int INF = 1'000'000'000; // 1e9

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){}
};

/*
int V; //頂点数
std::vector<std::vector<edge>> G;  std::vector<int> G;
std::vector<int> d; //sからの距離
*/


void dijkstra(std::vector<std::vector<edge>>& G, std::vector<int>& d, int s){
    //pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> que;
    int V(G.size());
    d.resize(V, INF+3);
    d[s] = 0;
    que.push({0, s});

    while(!que.empty()){
        std::pair<int, int> p(que.top()); que.pop();
        int v(p.second);
        if(d[v] < p.first) continue;
        for(edge &e: G[v]){
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push({d[e.to], e.to});
            }
        }
    }
}

void dijkstra_WithoutCost(std::vector<std::vector<int>>& G, std::vector<int>& d, int s){
    //pair<int, int> first: 距離　second: 頂点
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> que;
    int V(G.size());
    d.resize(V, INF+3);
    d[s] = 0;
    que.push({0, s});

    while(!que.empty()){
        std::pair<int, int> p(que.top()); que.pop();
        int v(p.second);
        if(d[v] < p.first) continue;
        for(int &e: G[v]){
            if(d[e] > d[v] + 1){
                d[e] = d[v] + 1;
                que.push({d[e], e});
            }
        }
    }
}

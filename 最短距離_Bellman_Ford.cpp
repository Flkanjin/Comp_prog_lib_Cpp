//O(V E) 頂点sからの距離を求める
#include <algorithm>
#include <vector>
const long long LINF{1'000'000'000'000'000'000}; // 1e18
const int NIL{-1};

struct Edge{
    int from, to, cost;
    Edge(int From, int To, int Cost): from(From), to(To), cost(Cost){}
};

// d: 距離, prv: 最短経路での一つ前の頂点
// 負閉路が存在しない 即ち最短距離が求まっている場合: true
bool bellmanFord(int V, int s, std::vector<Edge> &G, std::vector<long long> &d, std::vector<int> &prv){
    d.resize(V, LINF);
    prv.resize(V, NIL);
    d[s] = 0;
    bool negLoop = false;
    for(int i{0}; i < V; ++i){
        for(auto &e: G){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                prv[e.to] = e.from;
                // V回目に更新があれば負閉路
                if(i == V-1){
                    d[e.to] = -LINF;
                    negLoop = true;
                }
            }
        }
    }
    return !negLoop;
}


struct edge_wc{
    int from, to;
    edge_wc(int From, int To): from(From), to(To){}
};

// d: 距離, prv: 最短経路での一つ前の頂点
// 負閉路が存在しない 即ち最短距離が求まっている場合: true
bool bellmanFordWithoutCost(int V, int s, std::vector<edge_wc> &G, std::vector<long long> &d, std::vector<int> &prv){
    d.resize(V, LINF);
    prv.resize(V, NIL);
    d[s] = 0;
    bool negLoop = false;
    for(int i{0}; i < V; ++i){
        for(auto &e: G){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + 1){
                d[e.to] = d[e.from] + 1;
                prv[e.to] = e.from;
                // V回目に更新があれば負閉路
                if(i == V-1){
                    d[e.to] = -LINF;
                    negLoop = true;
                }
            }
        }
    }
    return !negLoop;
}

std::vector<int> buildPath(const std::vector<int> &prv, int t){
    std::vector<int> path;
    for(int u{t}; u >= 0; u = prv[u]){
        path.push_back(u);
    }
    std::reverse(std::begin(path), std::end(path));
    return path;
}
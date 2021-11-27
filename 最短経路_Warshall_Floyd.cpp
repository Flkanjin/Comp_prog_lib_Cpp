//O(V^3) 全ての点同士(連結ならば)
#include <vector>
const long long LINF = 1'000'000'000'000'000'000; // 1e18
template<class T, class S> inline bool chmin(T &a, const S &b){
    if(b < a){
        a = b; return true;
    }
    return false;
}


// 負閉路が存在しない 即ち最短距離が求まっている場合: true
bool warshallFloyd(std::vector<std::vector<long long>>& d){
    int V{int(d.size())};
    for(int k{0}; k < V; ++k)
        for(int i{0}; i < V; ++i)
            for(int j{0}; j < V; ++j)
                if(d[i][k] < LINF && d[k][j] < LINF)
                    chmin(d[i][j], d[i][k] + d[k][j]);
    for(int i{0}; i < V; ++i) if(d[i][i] < 0) return false;
    return true;
}

struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){};
};

void initialFromGraphList_Cost(std::vector<std::vector<edge>>& G, std::vector<std::vector<long long>>& d){
    int V{int(G.size())};
    d.resize(V);
    for(int i{0}; i < V; ++i){
        d[i].resize(V, LINF);
        d[i][i] = 0;
    }
    for(int i{0}; i < V; ++i){
        for(auto& e: G[i])
            d[i][e.to] = e.cost;
    }
}


void initialFromGraphList_WitoutCost(std::vector<std::vector<int>>& G, std::vector<std::vector<long long>>& d){
    int V{int(G.size())};
    d.resize(V);
    for(int i{0}; i < V; ++i){
        d[i].resize(V, LINF);
        d[i][i] = 0;
    }
    for(int i{0}; i < V; ++i){
        for(auto to: G[i])
            d[i][to] = 1;
    }
}




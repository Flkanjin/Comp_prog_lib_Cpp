//O(V E) 頂点sからの距離を求める
#include <algorithm>
#include <vector>
const long long LINF = 1'000'000'000'000'000'000; // 1e18

struct edge{
    int from, to, cost;
    edge(int From, int To, int Cost): from(From), to(To), cost(Cost){}
};

void bellmanFord_Cost(int V, std::vector<edge>& es, std::vector<long long>& d, int s){
    d.resize(V, LINF);
    d[s] = 0;
    while(1){
        bool update = false;
        for(auto &e : es){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if(!update) break;
    }
}

bool find_negative_loop_Cost(int V, std::vector<edge>& es, std::vector<long long>& d, int s){
    d.resize(V, LINF);
    d[s] = 0;
    for(int i(0); i < V; ++i){
        for(auto &e : es){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                
                //V回目に更新なら負閉路あり
                if(i == V-1) return true;
            }
        }
    }
    return false;
}



struct Edge{
    int from, to;
    Edge(int From, int To): from(From), to(To){}
};

void bellmanFord_WithoutCost(int V, std::vector<Edge>& es, std::vector<long long>& d, int s){
    d.resize(V, LINF);
    d[s] = 0;
    while(1){
        bool update = false;
        for(auto &e : es){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + 1){
                d[e.to] = d[e.from] + 1;
                update = true;
            }
        }
        if(!update) break;
    }
}

bool find_negative_loop_WIthoutCost(int V, std::vector<Edge>& es, std::vector<long long>& d, int s){
    d.resize(V, LINF);
    d[s] = 0;
    for(int i(0); i < V; ++i){
        for(auto &e : es){
            if(d[e.from] != LINF && d[e.to] > d[e.from] + 1){
                d[e.to] = d[e.from] + 1;
                
                //V回目に更新なら負閉路あり
                if(i == V-1) return true;
            }
        }
    }
    return false;
}

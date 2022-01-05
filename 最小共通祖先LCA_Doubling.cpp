#include <vector>
#include <cmath>
const int NIL = -1;


struct edge{
    int to, cost;
    edge(int To, int Cost): to(To), cost(Cost){}
    edge(): to(NIL), cost(NIL){}
};

class LowestCommonAncestorDoubling{
    std::vector<edge> par;//NIL
    std::vector<long long> d;
    std::vector<int> dep;
    std::vector<std::vector<edge>> child; //G: 有向木
    std::vector<std::vector<int>> ances;
    int V, M, root;
public:
    LowestCommonAncestorDoubling(std::vector<edge> &p): par(p){
        V = par.size();
        child.resize(V);
        for(int i{0}; i < V; ++i){
            if(par[i].to == NIL) root = i;
            else child[par[i].to].emplace_back(i, par[i].cost);
        }
        build();
    }
    LowestCommonAncestorDoubling(std::vector<std::vector<edge>> &G): child(G){
        V = child.size();
        par.resize(V, {NIL, NIL});
        for(int i{0}; i < V; ++i){
            for(auto &e: child[i]){
                par[e.to].to = i;
                par[e.to].cost = e.cost;
            }
        }
        for(int i{0}; i < V; ++i){
            if(par[i].to == NIL) root = i;
        }
        build();
    }

private:
    void build(){
        M = int(std::log2(V)) + 3;
        ances.resize(V); d.resize(V, -1); dep.resize(V, -1);
        for(int i{0}; i < V; ++i){
            ances[i].resize(M, NIL);
            ances[i][0] = par[i].to;
        }
        for(int j{0}, j_len{M-1}; j < j_len; ++j){
            for(int i{0}; i < V; ++i){
                if(ances[i][j] == NIL) continue;
                ances[i][j+1] = ances[ances[i][j]][j];
            }
        }
        dfs(root, 0, 0);
    }

    void dfs(int cur, int depth, long long dist){
        dep[cur] = depth;
        d[cur] = dist;
        for(auto &e: child[cur]){
            dfs(e.to, depth + 1, dist + e.cost);
        }
    }

public:
    int LCA(int u, int v) const{
        if(dep[u] > dep[v]) std::swap(u, v);
        for(int i{M-1}; i >= 0; --i){
            if(((dep[v] - dep[u]) >> i) & 1)
                v = ances[v][i];
        }
        if(u == v) return u;
        for(int i{M-1}; i >= 0; --i){
            if(ances[u][i] != ances[v][i]){
                u = ances[u][i];
                v = ances[v][i];
            }
        }
        return ances[u][0];
    }
    long long distance(int u, int v) const{
        int a{LCA(u, v)};
        return d[u] + d[v] - 2 * d[a];
    }
};

//木のグラフを親への有向グラフへ
void treeToParentDFS(int cur, std::vector<edge> &par, std::vector<std::vector<edge>> &G){
    for(auto &e: G[cur]){
        if(par[cur].to == e.to) continue;
        par[e.to].to = cur;
        par[e.to].cost = e.cost;
        treeToParentDFS(e.to, par, G);
    }
    return;
}
std::vector<edge> treeToParent(int root, std::vector<std::vector<edge>> &G){
    int V(G.size());
    std::vector<edge> par(V, {NIL, NIL});
    treeToParentDFS(root, par, G);
    return par;
}

//木のグラフを親への有向グラフへ
void treeToParentDFSWithoutCost(int cur, std::vector<edge> &par, std::vector<std::vector<int>> &G){
    for(auto &e: G[cur]){
        if(par[cur].to == e) continue;
        par[e].to = cur;
        par[e].cost = 1;
        treeToParentDFSWithoutCost(e, par, G);
    }
    return;
}
std::vector<edge> treeToParentWithoutCost(int root, std::vector<std::vector<int>> &G){
    int V(G.size());
    std::vector<edge> par(V, {NIL, NIL});
    treeToParentDFSWithoutCost(root, par, G);
    return par;
}

#include <vector>
#include <cmath>
const int NIL = -1;


class LowestCommonAncestorDoubling{
    std::vector<int> par;//NIL
    std::vector<int> d;
    std::vector<std::vector<int>> child; //G: 有向木
    std::vector<std::vector<int>> ances;
    int V, M, root;
public:
    LowestCommonAncestorDoubling(std::vector<int> &p): par(p){
        V = par.size();
        child.resize(V);
        for(int i(0); i < V; ++i){
            if(par[i] == NIL) root = i;
            else child[par[i]].push_back(i);
        }
        build();
    }
    LowestCommonAncestorDoubling(std::vector<std::vector<int>> &G): child(G){
        V = child.size();
        par.resize(V, NIL);
        for(int i(0); i < V; ++i){
            for(auto e: child[i]){
                par[e] = i;
            }
        }
        for(int i(0); i < V; ++i){
            if(par[i] == NIL) root = i;
        }
        build();
    }

private:
    void build(){
        M = int(std::log2(V)) + 3;
        ances.resize(V); d.resize(V, -1);
        for(int i(0); i < V; ++i){
            ances[i].resize(M, -1);
            ances[i][0] = par[i];
        }
        for(int j(0), j_len(M-1); j < j_len; ++j){
            for(int i(0); i < V; ++i){
                if(ances[i][j] == NIL) continue;
                ances[i][j+1] = ances[ances[i][j]][j];
            }
        }
        dfs(root, 0);
    }

    void dfs(int cur, int depth){
        d[cur] = depth;
        for(auto e: child[cur]){
            dfs(e, depth + 1);
        }
    }

public:
    int LCA(int u, int v){
        if(d[u] > d[v]) std::swap(u, v);
        for(int i(M-1); i >= 0; --i){
            if(((d[v] - d[u]) >> i) & 1)
                v = ances[v][i];
        }
        if(u == v) return u;
        for(int i(M-1); i >= 0; --i){
            if(ances[u][i] != ances[v][i]){
                u = ances[u][i];
                v = ances[v][i];
            }
        }
        return ances[u][0];
    }
    int distance(int u, int v){
        int a(LCA(u, v));
        return d[u] + d[v] - 2 * d[a];
    }
};

//木のグラフを親への有向グラフへ
void treeToParentDFS(int cur, std::vector<int> &par, std::vector<std::vector<int>> &G){
    for(auto e: G[cur]){
        if(par[cur] == e) continue;
        par[e] = cur;
        treeToParentDFS(e, par, G);
    }
    return;
}
std::vector<int> treeToParent(int root, std::vector<std::vector<int>> &G){
    int V(G.size());
    std::vector<int> par(V, NIL);
    treeToParentDFS(root, par, G);
    return par;
}

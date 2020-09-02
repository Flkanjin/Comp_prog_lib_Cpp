//O(E log V)
#include <algorithm>
#include <vector>

struct edge{
    int from, to, cost;
    edge(int From, int To, int Cost): from(From), to(To), cost(Cost){};
};
 

bool edgeComp(const edge& e1, const edge& e2){
    return e1.cost < e2.cost;
}
 
class UnionFind{
    std::vector<int> par;
    std::vector<int> rank;
    std::vector<int> membnum;

public:
    UnionFind(){}
    UnionFind(int n): par(n), rank(n), membnum(n){
        for(int i(0); i < n; ++i){
            par[i] = i;
            rank[i] = 0;
            membnum[i] = 1;
        }
    }

    void resize(int n){
        int m(par.size());
        par.resize(n);
        rank.resize(n, 0);
        membnum.resize(n, 1);
        for(int i(m); i < n; ++i) par[i] = i;
    }

    int find(int x){
        if(x == par[x]) return x;
        else return par[x] = find(par[x]);
    }

    bool unit(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return false;

        if(rank[x] < rank[y]){
            par[x] = y;
            membnum[y] += membnum[x];
        }else{
            par[y] = x;
            if(rank[x] == rank[y]) ++rank[x];
            membnum[x] += membnum[y];
        }
        return true;
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    int howmany(int x){ //同じグループに属すものの個数(自分を含む)
        return membnum[find(x)];
    }
};
 
int kruskal(std::vector<edge>& G){
    int V(G.size());
    std::sort(std::begin(G), std::end(G), edgeComp);
    int res = 0;
    UnionFind UF(V);
    for(edge &e: G){
        if(!UF.same(e.from, e.to)){
            UF.unit(e.from, e.to);
            res += e.cost;
        }
    }
    return res;
}
 
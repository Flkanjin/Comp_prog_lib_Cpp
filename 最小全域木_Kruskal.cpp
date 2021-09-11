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
    int n;
    std::vector<int> par;//根ならマイナス*要素数

public:
    UnionFind(): n(0){}
    UnionFind(int N): n(N), par(n, -1){}

    void resize(int N){
        n = N;
        par.resize(n, -1);
    }

    int find(int x){
        if(par[x] < 0) return x;
        else return par[x] = find(par[x]);
    }

    bool unit(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return false;

        if(-par[x] < -par[y]) std::swap(x, y); 
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    int howmany(int x){ //同じグループに属すものの個数(自分を含む)
        return -par[find(x)];
    }

    std::vector<std::vector<int>> groups(){
        std::vector<int> root_buf(n), group_size(n);
        for(int i{0}; i < n; ++i){
            root_buf[i] = find(i);
            ++group_size[root_buf[i]];
        }
        std::vector<std::vector<int>> ret(n);
        for(int i{0}; i < n; ++i){
            ret[i].reserve(group_size[i]);
        }
        for(int i{0}; i < n; ++i){
            ret[root_buf[i]].push_back(i);
        }
        ret.erase(
            std::remove_if(std::begin(ret), std::end(ret),
                [&](const std::vector<int>& v){return v.empty();}),
            std::end(ret));
        return ret;
    }
};

long long kruskal_Cost(int V, std::vector<edge>& G){
    std::sort(std::begin(G), std::end(G), edgeComp);
    long long res{};
    UnionFind UF(V);
    for(edge &e: G){
        if(!UF.same(e.from, e.to)){
            UF.unit(e.from, e.to);
            res += e.cost;
        }
    }
    return res;
}

std::pair<long long, std::vector<edge>> kruskal(int V, std::vector<edge>& G){
    std::sort(std::begin(G), std::end(G), edgeComp);
    long long res{};
    std::vector<edge> T;
    UnionFind UF(V);
    for(edge &e: G){
        if(!UF.same(e.from, e.to)){
            UF.unit(e.from, e.to);
            res += e.cost;
            T.emplace_back(e.from, e.to, e.cost);
        }
    }
    return {res, T};
}

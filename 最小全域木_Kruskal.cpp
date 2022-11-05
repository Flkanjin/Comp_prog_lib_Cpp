//O(E log V)
#include <algorithm>
#include <vector>
#include "Union_Find.cpp"

struct Edge{
    int from, to, cost;
    Edge(int From, int To, int Cost): from(From), to(To), cost(Cost){}
};


bool edgeComp(const Edge& e1, const Edge& e2){
    return e1.cost < e2.cost;
}

long long kruskal_Cost(int V, std::vector<Edge>& G){
    std::sort(std::begin(G), std::end(G), edgeComp);
    long long res{};
    UnionFind UF(V);
    for(Edge &e: G){
        if(!UF.same(e.from, e.to)){
            UF.unit(e.from, e.to);
            res += e.cost;
        }
    }
    return res;
}

std::pair<long long, std::vector<Edge>> kruskal(int V, std::vector<Edge>& G){
    std::sort(std::begin(G), std::end(G), edgeComp);
    long long res{};
    std::vector<Edge> T;
    UnionFind UF(V);
    for(Edge &e: G){
        if(!UF.same(e.from, e.to)){
            UF.unit(e.from, e.to);
            res += e.cost;
            T.emplace_back(e.from, e.to, e.cost);
        }
    }
    return {res, T};
}

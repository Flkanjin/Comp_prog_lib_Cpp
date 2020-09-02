#include <vector>


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

//Tはアーベル群
template<class T> class WeightedUnionFind{
    std::vector<int> par;
    std::vector<int> rank;
    std::vector<int> membnum;
    std::vector<T> diff_weight;
 
public:
    WeightedUnionFind(){}
    WeightedUnionFind(int n, T UNITY = 0): par(n), rank(n), membnum(n), diff_weight(n){
        for(int i(0); i < n; ++i){
            par[i] = i;
            rank[i] = 0;
            membnum[i] = 1;
            diff_weight[i] = UNITY;
        }
    }
 
    void  resize(int n, T UNITY = 0){
        int m(par.size());
        par.resize(n);
        rank.resize(n, 0);
        membnum.resize(n, 1);
        diff_weight.resize(n, UNITY);
        for(int i(m); i < n; ++i) par[i] = i;
    }
 
    int find(int x){
        if(x == par[x]) return x;
        int r(find(par[x]));
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = r;
    }
 
    T weight(int x){
        find(x);
        return diff_weight[x];
    }
 
    //weight(y) = weight(x) + w
    bool unit(int x, int y, T w){
        w += weight(x); w -= weight(y);
        x = find(x); y = find(y);
        if(x == y) return false;
 
        if(rank[x] < rank[y]){
            par[x] = y;
            diff_weight[x] = -w;
            membnum[y] += membnum[x];
        }else{
            par[y] = x;
            if(rank[x] == rank[y]) ++rank[x];
            diff_weight[y] = w;
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

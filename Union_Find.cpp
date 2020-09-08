#include <algorithm>
#include <vector>


class UnionFind{
    int n;
    std::vector<int> par;//根ならマイナス*要素数

public:
    UnionFind(): n(0){}
    UnionFind(int N): n(N), par(n){
        for(int i(0); i < n; ++i){
            par[i] = -1;
        }
    }

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
        for(int i(0); i < n; ++i){
            root_buf[i] = find(i);
            ++group_size[root_buf[i]];
        }
        std::vector<std::vector<int>> ret(n);
        for(int i(0); i < n; ++i){
            ret[i].reserve(group_size[i]);
        }
        for(int i(0); i < n; ++i){
            ret[root_buf[i]].push_back(i);
        }
        ret.erase(
            std::remove_if(std::begin(ret), std::end(ret),
                [&](const std::vector<int>& v){return v.empty();}),
            std::end(ret));
        return ret;
    }
};

//AbelianGはアーベル群
template<class AbelianG> class WeightedUnionFind{
    int n;
    std::vector<int> par;//根ならマイナス*要素数
    std::vector<AbelianG> diff_weight;
 
public:
    WeightedUnionFind(): n(0){}
    WeightedUnionFind(int N, AbelianG UNITY = 0):
        n(N), par(n), diff_weight(n){
            for(int i(0); i < n; ++i){
                par[i] = -1;
                diff_weight[i] = UNITY;
            }
        }
 
    void resize(int N, AbelianG UNITY = 0){
        n = N;
        par.resize(n, -1);
        diff_weight.resize(n, UNITY);
    }
 
    int find(int x){
        if(par[x] < 0) return x;
        int r(find(par[x]));
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = r;
    }
 
    AbelianG weight(int x){
        find(x);
        return diff_weight[x];
    }
 
    //weight(y) = weight(x) + w
    bool unit(int x, int y, AbelianG w){
        w += weight(x); w -= weight(y);
        x = find(x); y = find(y);
        if(x == y) return false;

        if(-par[x] < -par[y]){
            std::swap(x, y); w *= -1;
        }

        par[x] += par[y];
        par[y] = x;
        diff_weight[y] = w;
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
        for(int i(0); i < n; ++i){
            root_buf[i] = find(i);
            ++group_size[root_buf[i]];
        }
        std::vector<std::vector<int>> ret(n);
        for(int i(0); i < n; ++i){
            ret[i].reserve(group_size[i]);
        }
        for(int i(0); i < n; ++i){
            ret[root_buf[i]].push_back(i);
        }
        ret.erase(
            std::remove_if(std::begin(ret), std::end(ret),
                [&](const std::vector<int>& v){return v.empty();}),
            std::end(ret));
        return ret;
    }
};

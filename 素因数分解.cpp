#include <map>
#include <set>
#include <utility>
#include <vector>



std::vector<std::pair<long long, int>> primeFactorisation_Vector_Pair(long long n){
    std::vector<std::pair<long long, int>> ret;
    for(long long i{2}; i * i <= n; ++i){
        int cnt{};
        while(!(n % i)){
            ++cnt;
            n /= i;
        }
        ret.emplace_back(i, cnt);
    }
    if(n > 1) ret.emplace_back(n, 1);;
    return ret;
}

std::map<long long, int> primeFactorisation_Map(long long n){
    std::map<long long, int> mp;
    for(long long i{2}; i * i <= n; ++i) while(!(n % i)){
        ++mp[i]; n /= i;
    }
    if(n > 1) ++mp[n];
    return mp;
}

//指数無し

std::set<long long> primeFactorisation_Set(long long n){
    std::set<long long> s;
    for(long long i{2}; i * i <= n; ++i) if(!(n % i)){
        s.insert(i);
        while(!(n % i)) n /= i;
    }
    if(n > 1) s.insert(n);
    return s;
}

std::vector<long long> primeFactorisation_Vector(long long n){
    std::vector<long long> v;
    for(long long i{2}; i * i <= n; ++i) while(!(n % i)){
        v.push_back(i); n /= i;
    }
    if(n > 1) v.push_back(n);
    return v;
}

std::vector<long long> primeFactor(long long n){
    std::vector<long long> vec;
    for(long long i{2}; i * i <= n; ++i) if(!(n % i)){
        vec.push_back(i);
        while(!(n % i)) n /= i;
    }
    if(n > 1) vec.push_back(n);
    return vec;
}


// オイラーのトーシェント
std::vector<int> EulerTotient(int n){
    std::vector<int> ret(n+1);
    for(int i{0}; i < n; ++i) ret[i] = i;
    for(int i{2}; i <= n; ++i) if(ret[i] == i) for(int j{i}; j <= n; j += i) ret[j] = ret[j] / i * (i-1);
    return ret;
}

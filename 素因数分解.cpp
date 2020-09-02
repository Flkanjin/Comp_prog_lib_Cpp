#include <map>
#include <vector>



std::map<long long, int> primeFactorisation_Map(long long n){
    std::map<long long, int> mp;
    for(long long i(2); i * i <= n; ++i)
        while(!(n % i)){
            ++mp[i]; n /= i;
        }
    if(n > 1) ++mp[n];
    return mp;
}

//指数無し
std::vector<long long> primeFactorisation_Vector(long long n){
    std::vector<long long> v;
    for(long long i(2); i * i <= n; ++i)
        while(!(n % i)){
            v.push_back(i); n /= i;
        }
    if(n > 1) v.push_back(n);
    return v;
}

std::vector<long long> primeFactor(long long n){
    std::vector<long long> vec;
    for(long long i(2); i * i <= n; ++i){
        if(!(n % i)){
            vec.push_back(i);
            while(!(n % i)){
                n /= i;
            }
        }
    }
    if(n > 1) vec.push_back(n);
    return vec;
}

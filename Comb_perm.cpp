#include <vector>


template<unsigned long long m> class comb_perm{
private:
    int n;
    std::vector<long long> fact, fact_inv;
public:
    comb_perm(): n{0}, fact(1), fact_inv(1){
        fact[0] = fact_inv[0] = 1;
    }
    comb_perm(int N): n{N}, fact(N+1), fact_inv(N+1){
        fact[0] = fact[1] = fact_inv[0] = fact_inv[1] = 1;
        for(int i{2}; i <= n; ++i) fact[i] = fact[i - 1] * i % m;
        for(int i{2}; i <= n; ++i) fact_inv[i] = inv(fact[i]);
    }

    bool resize(int N){
        if(N <= n) return false;
        fact.resize(N+1);
        fact_inv.resize(N+1);
        if(!n && N){
            fact[1] = fact_inv[1] = 1;
        }
        for(int i{std::max(2, n+1)}; i <= N; ++i) fact[i] = fact[i - 1] * i % m;
        for(int i{std::max(2, n+1)}; i <= N; ++i) fact_inv[i] = inv(fact[i]);
        n = N;
        return true;
    }

    long long power(long long a, unsigned long long b){
        long long ret{1};
        while(b){
            if(b & 1) ret = (ret * a) % m;
            a = (a * a) % m;
            b /= 2;
            if(ret < 0) ret += m;
            if(a < 0) a += m;
        }
        return ret;
    }

    long long inv(long long a){ // GCD(a, m) = 1
        return power(a, m - 2);
    }

    long long permutation(int n, int r){
        if(n < r) return 0;
        if(n < 0 || r < 0) return 0;
        long long ret{factorial(n)};
        ret = ret * inv_factorial(n - r) % m;
        return ret;
    }

    long long combination(int n, int r){
        if(n < r) return 0;
        if(n < 0 || r < 0) return 0;
        long long ret{permutation(n, r)};
        return ret * inv_factorial(r) % m;
    }

    long long multi_combination(int n, int r){
        return combination(n + r - 1, r);
    }

    long long factorial(int a){
        if(a > n) resize(a);
        return fact[a];
    }

    long long inv_factorial(int a){
        if(a > n) resize(a);
        return fact_inv[a];
    }

};

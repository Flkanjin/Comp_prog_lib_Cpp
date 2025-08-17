const int MOD{1'000'000'007};

long long power(long long a, unsigned long long b, long long m){
    auto ret{1LL};
    while(b){
        if(b & 1) ret = (ret * a) % m;
        a = (a * a) % m;
        b >>= 1;
        if(ret < 0) ret += m;
        if(a < 0) a += m;
    }
    return ret;
}


long long power(long long a, unsigned long long b) {
    return power(a, b, MOD);
}

long long inv(int a, long long m){ // GCD(a, m) = 1
    return power(a, m-2, m);
}

long long inv(int a){
    return inv(a, MOD);
}
#include <cassert>
#include <utility>
#include <vector>

long long extgcd(long long a, long long b, long long& x, long long& y){ //ax + by = gcd(a, b)
    long long d(a);
    if(b){
        d = extgcd(b, a%b, y, x);
        y -= (a/b) * x;
    }else{
        x = 1; y = 0;
    }
    return d;
}

std::pair<long long, long long> crt(const std::vector<long long> &r,
                                    const std::vector<long long> &m){
    int n(r.size());
    assert(n == m.size());
    long long y0, y1;
    long long r0(0), m0(1);
    for(int i(0); i < n; ++i){
        long long r1(r[i] % m[i]), m1(m[i]);
        if(r1 < 0) r1 += m1;
        long long d(extgcd(m0, m1, y0, y1));
        if((r0 - r1) % d) return {0, 0};
        r0 += m0 * (((r1 - r0) / d) * y0 % (m1 / d));
        m0 *= m1 / d;
        r0 %= m0;
        if(r0 < 0) r0 += m0;
    }
    return {r0, m0};
}
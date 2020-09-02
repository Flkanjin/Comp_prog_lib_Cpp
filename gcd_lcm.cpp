
long long gcd(long long a, long long b){
    if(!b) return a;
    if(a % b) return gcd(b, a % b);
    return b;
}

long long lcm(long long a, long long b){
    long long g(gcd(a, b));
    return a / g * b;
}

int gcd(int a, int b){
    if(!b) return a;
    if(a % b) return gcd(b, a % b);
    return b;
}

long long lcm(int a, int b){
    long long g(gcd(a, b));
    return a / g * b;
}

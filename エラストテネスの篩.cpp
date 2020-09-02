#include <vector>


std::vector<bool> isPrime;

void Eratosthenes(int n){
    if(n + 1 <= int(isPrime.size())) return;
    isPrime.resize(n+1, true);
    isPrime[0] = isPrime[1] = false;

    for(int i = 2; i * i <= n; ++i){
        if(isPrime[i]){
            for(int j = i; i * j <= n; ++j)
                isPrime[i*j] = false;
        }
    }
}

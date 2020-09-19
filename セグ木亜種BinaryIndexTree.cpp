#include <vector>

//T: int系
template<class T> class BinaryIndexTree{
    int n;
    std::vector<unsigned long long> data;
public:
    BinaryIndexTree(): n(0){}
    BinaryIndexTree(int m): n(m), data(m){}

    void add(int k, T a){
        ++k;
        while(k <= n){
            data[k - 1] += (unsigned long long)a;
            k += k & -k;
        }
    }

    T getSum(int l, int r){
        //[l, r[
        return sum(r) - sum(l);
    }
private:
    unsigned long long sum(int r){
        unsigned long long s(0);
        while(r > 0){
            s += data[r-1];
            r -= r & -r;
        }
        return s;
    }
};

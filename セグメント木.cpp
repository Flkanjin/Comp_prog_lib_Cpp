#include <vector>

constexpr int INF{1'000'000'000}; //1e9

template<class T> class SegmentTreeMin{
    int n = 0;
    std::vector<T> dat;
    T fill = INF;
public:
    SegmentTreeMin(){}
    SegmentTreeMin(int m, T fil = INF){
        fill = fil;
        int i{1};
        while(i < m) i *= 2;
        n = i;
        dat.resize(2*i - 1);
        for(int j{0}, j_len{2*i-1}; j < j_len; ++j)
            dat[j] = fill;
    }

    void update(int k, T a){
        k += n - 1;
        dat[k] = a;
        while(k){
            k = (k - 1) / 2;
            dat[k] = std::min(dat[2*k+1], dat[2*k+2]);
        }
    }

    T getMin(int a, int b, int k=0, int l=0, int r=-1){
        // NOTE: [a, b[
        if(r < 0) r = n;
        if(r <= a || b <= l) return fill;
        if(a <= l && r <= b) return dat[k];
        return std::min(getMin(a, b, 2*k+1, l, (l+r)/2), getMin(a, b, 2*k+2, (l+r)/2, r));
    }

    T getvalue(int k){
        return dat[k+n-1];
    }
};

template<class T> class SegmentTreeMax{
    int n = 0;
    std::vector<T> dat;
    T fill = -INF;
public:
    SegmentTreeMax(){}
    SegmentTreeMax(int m, T fil = -INF){
        fill = fil;
        int i{1};
        while(i < m) i *= 2;
        n = i;
        dat.resize(2*i - 1);
        for(int j{0}, j_len{2*i-1}; j < j_len; ++j)
            dat[j] = fill;
    }

    void update(int k, T a){
        k += n - 1;
        dat[k] = a;
        while(k){
            k = (k - 1) / 2;
            dat[k] = std::max(dat[2*k+1], dat[2*k+2]);
        }
    }

    T getMax(int a, int b, int k=0, int l=0, int r=-1){
        // NOTE: [a, b[
        if(r < 0) r = n;
        if(r <= a || b <= l) return fill;
        if(a <= l && r <= b) return dat[k];
        return std::max(getMax(a, b, 2*k+1, l, (l+r)/2), getMax(a, b, 2*k+2, (l+r)/2, r));
    }

    T getvalue(int k){
        return dat[k+n-1];
    }
};

//Tはアーベル群
template<class T> class SegmentTreeSum{
    int n = 0;
    std::vector<T> dat;
    T fill = 0;
public:
    SegmentTreeSum(){}
    SegmentTreeSum(int m, T fil = 0){
        fill = fil;
        int i{1};
        while(i < m) i *= 2;
        n = i;
        dat.resize(2*i - 1);
        for(int j{0}, j_len{2*i-1}; j < j_len; ++j)
            dat[j] = fill;
    }

    void update(int k, T a){
        k += n - 1;
        T moto{dat[k]};
        dat[k] = a;
        while(k){
            k = (k - 1) / 2;
            dat[k] += a - moto;
        }
    }

    void updateIncrease(int k, T a){
        update(k, dat[k+n-1] + a);
    }
    void updateIncrease(int k){
        updateIncrease(k, 1);
    }

    void updateDecrease(int k, T a){
        update(k, dat[k+n-1] - a);
    }
    void updateDecrease(int k){
        updateDecrease(k, 1);
    }

    T getSum(int a, int b, int k=0, int l=0, int r=-1){
        // NOTE: [a, b[
        if(r < 0) r = n;
        if(r <= a || b <= l) return fill;
        if(a <= l && r <= b) return dat[k];
        return getSum(a, b, 2*k+1, l, (l+r)/2) + getSum(a, b, 2*k+2, (l+r)/2, r);
    }

    T getvalue(int k){
        return dat[k+n-1];
    }

    bool getExist(int l, int r){//Assume non-neg
        // NOTE: [l, r]
        return (getSum(l, r+1) > fill);
    }
};

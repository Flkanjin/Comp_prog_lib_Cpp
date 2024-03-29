#include <cassert>
#include <vector>
#include <iomanip>
#include <iostream>

template <class T> class Matrix{
private:
    std::vector<std::vector<T>> A;
public:
    Matrix(){}

    Matrix(std::size_t m, std::size_t n): A(m, std::vector<T>(n, 0)) {}

    Matrix(std::size_t n): A(n, std::vector<T>(n, 0)) {}

    Matrix(std::size_t m, std::size_t n, T a): A(m, std::vector<T>(n, a)) {}

    Matrix(const Matrix& mat){if(this != &mat) A = mat.A;}

    Matrix(const std::vector<std::vector<T>> &v){
        std::size_t m{v.size()};
        assert(m != 0);
        std::size_t n{v[0].size()};
        for(int i{0}; i < m; ++i)
            assert(v[i].size() == n);
        A = v;
    }

    Matrix(const std::vector<T> &v){
        std::size_t m{v.size()};
        assert(m != 0);
        A.resize(1);
        A[0] = v;
    }

    ~Matrix() {}

    std::size_t height() const{return A.size();}

    std::size_t width() const{
        if(!height()) return 0;
        return A[0].size();
    }

    void setHeight(std::size_t h){A.resize(h, std::vector<T>(width(), 0));}

    void setWidth(std::size_t w){
        std::size_t m{height()};
        for(int i{0}; i < m; ++i) A[i].resize(w, 0);
    }

    void setSize(std::size_t h, std::size_t w){
        setHeight(h); setWidth(w);
    }

    void inputNoChangeSize(){
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i)
            for(int j{0}; j < n; ++j)
                std::cin >> A[i][j];
    }

    void input(std::size_t h, std::size_t w){
        setSize(h, w);
        inputNoChangeSize();
    }

    void input(){
        std::size_t h, w; std::cin >> h >> w;
        input(h, w);
    }

    bool sameSize(const Matrix& mat) const{
        return height() == mat.height() && width() == mat.width();
    }

    inline const std::vector<T> &operator[](int idx) const{return A.at(idx);}

    inline std::vector<T> &operator[](int k){return (A.at(k));}

    void print2D(int w) const{
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) std::cout << std::setw(w) << (*this)[i][j] << " \n"[j == n-1];
    }

    void print2D() const{
        std::cout << *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& B){
        std::size_t m{B.height()}, n{B.width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) os << B[i][j] << " \n"[j == n-1];
        return (os);
    }

    static Matrix identity(std::size_t n){
        Matrix ret(n);
        for(int i{0}; i < n; ++i) ret[i][i] = 1;
        return ret;
    }

    Matrix transpose() const{
        std::size_t n{height()}, m{width()};
        Matrix ret(m, n);
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) ret[i][j] = (*this)[j][i];
        return ret;
    }

    Matrix operator+() const{return *this;}

    Matrix operator-() const{
        std::size_t m{height()}, n{width()};
        Matrix temp(height(), width());
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) temp[i][j] = -(*this)[i][j];
        return temp;
    }

    Matrix& operator=(const Matrix& B){
        if(this != &B) A = B.A;
        return *this;
    }

    Matrix& operator+=(const Matrix& B){
        assert(sameSize(B));
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] += B[i][j];
        return *this;
    }

    Matrix& operator-=(const Matrix& B){
        assert(sameSize(B));
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] -= B[i][j];
        return *this;
    }

    Matrix& operator*=(const Matrix& B){
        std::size_t m{height()}, n{width()}, l = B.width();
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i{0}; i < m; ++i) for(int j{0}; j < l; ++j) for(int k{0}; k < n; ++k) C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
        A.swap(C);
        return *this;
    }

    Matrix& operator*=(const T a){
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] *= a;
        return *this;
    }

    Matrix& operator%=(const long long &mod){
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] %= mod;
        return *this;
    }

    Matrix& operator^=(const Matrix &B){
        assert(sameSize(B));
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] ^= B[i][j];
        return *this;
    }

    Matrix& operator|=(const Matrix &B){
        assert(sameSize(B));
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) (*this)[i][j] |= B[i][j];
        return *this;
    }

    Matrix& operator&=(const Matrix &B){
        std::size_t m{height()}, n{width()}, l{B.width()};
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i{0}; i < m; ++i) for(int j{0}; j < l; ++j) for(int k{0}; k < n; ++k) C[i][j] = (C[i][j] ^ ((*this)[i][k] & B[k][j]));
        A.swap(C);
        return *this;
    }

    Matrix operator+(const Matrix& mat) const{
        Matrix temp(*this);
        return temp += mat;
    }

    Matrix operator-(const Matrix& mat) const{
        Matrix temp(*this);
        return temp -= mat;
    }

    Matrix operator*(const Matrix& mat) const{
        Matrix temp(*this);
        return temp *= mat;
    }

    Matrix operator*(const T& a) const{
        Matrix temp(*this);
        return temp *= a;
    }

    friend Matrix operator*(T a, const Matrix& B){
        return B * a;
    }

    Matrix operator%(const long long mod) const{
        Matrix temp(*this);
        return temp %= mod;
    }

    Matrix operator^(const Matrix& mat) const{
        Matrix temp(*this);
        return temp ^= mat;
    }

    Matrix operator|(const Matrix& mat) const{
        Matrix temp(*this);
        return temp |= mat;
    }

    Matrix operator&(const Matrix& mat) const{
        Matrix temp(*this);
        return temp &= mat;
    }

    bool operator==(const Matrix& mat) const{
        if(!sameSize(mat)) return false;
        std::size_t m{height()}, n{width()};
        for(int i{0}; i < m; ++i) for(int j{0}; j < n; ++j) if((*this)[i][j] != mat[i][j]) return false;
        return true;
    }

    bool operator!=(const Matrix& mat) const{return !(*this == mat);}

    Matrix modmul(const Matrix& B, long long mod){
        Matrix temp(*this);
        std::size_t m{height()}, n{width()}, l = B.width();
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i{0}; i < m; ++i) for(int j{0}; j < l; ++j) for(int k{0}; k < n; ++k){
            C[i][j] = (C[i][j] + temp[i][k] * B[k][j]) % mod;
            if(C[i][j] < 0) C[i][j] += mod;
        }
        return C;
    }
    
    Matrix& modmmul(const Matrix& B){
        return modmul(B, MOD);
    }

    Matrix powWithoutMod(unsigned long long b) const{
        std::size_t n{height()};
        assert(n == width());
        Matrix ret = identity(n);
        Matrix a = *this;
        while(b){
            if(b & 1) ret = ret * a;
            a = a * a;
            b /= 2;
        }
        return ret;
    }

    Matrix power(unsigned long long b, long long mod) const{
        std::size_t n{height()};
        assert(n == width());
        Matrix ret = identity(n);
        Matrix a = *this;
        while(b){
            if(b & 1) ret = ret.modmul(a, mod);
            a = a.modmul(a, mod);
            for(int i{0}; i < n; ++i) for(int j{0}; j < n; ++j){
                if(ret[i][j] < 0) ret[i][j] += mod;
                if(a[i][j] < 0) a[i][j] += mod;
            }
            b /= 2;
        }
        return ret;
    }

    Matrix power(unsigned long long b) const{
        return power(b, MOD);
    }

    Matrix powXorAnd(unsigned long long b) const{
        std::size_t n{height()};
        assert(n == width());
        Matrix ret = identity(n);
        ret *= -1;
        Matrix a = *this;
        while(b){
            if(b & 1) ret = ret & a;
            a = a & a;
            b /= 2;
        }
        return ret;
    }
};

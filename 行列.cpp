#include <cassert>
#include <vector>


template <class T> class Matrix{
private:
    std::vector<std::vector<T>> A;
public:
    Matrix(){}
 
    Matrix(size_t m, size_t n): A(m, std::vector<T>(n, 0)) {}
 
    Matrix(size_t n): A(n, std::vector<T>(n, 0)) {}
 
    Matrix(size_t m, size_t n, T a): A(m, std::vector<T>(n, a)) {}
 
    Matrix(const Matrix& mat){if(this != &mat) A = mat.A;}
 
    Matrix(const std::vector<std::vector<T>> &v){
        size_t m = v.size();
        assert(m != 0);
        size_t  n(v[0].size());
        for(int i(0); i < m; ++i)
            assert(v[i].size() == n);
        A = v;
    }
 
    Matrix(const std::vector<T> &v){
        size_t m = v.size();
        assert(m != 0);
        A.resize(1);
        A[0] = v;
    }
 
    ~Matrix() {}
 
    size_t height() const{return A.size();}
 
    size_t width() const{
        if(!height()) return 0;
        return A[0].size();
    }
 
    void setHeight(int h){A.resize(h, std::vector<T>(width(), 0));}
 
    void setWidth(int w){
        size_t m = height();
        for(int i(0); i < m; ++i) A[i].resize(w, 0);
    }
 
    void setSize(int h, int w){
        setHeight(h); setWidth(w);
    }
 
    void inputNoChangeSize(){
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                std::cin >> A[i][j];
    }
 
    void input(int h, int w){
        setSize(h, w);
        inputNoChangeSize();
    }
 
    void input(){
        int h, w; std::cin >> h >> w;
        input(h, w);
    }
 
    bool sameSize(const Matrix& mat) const{
        return height() == mat.height() && width() == mat.width();
    }
 
    inline const std::vector<T> &operator[](int idx) const{return A.at(idx);}
 
    inline std::vector<T> &operator[](int k){return (A.at(k));}
 
    void print2D(int w) const{
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i){
            for(int j(0); j < n; ++j){
                if(j) std::cout << " ";
                std::cout << std::setw(w) << (*this)[i][j];
            }
            std::cout << "\n";
        }
    }
 
    void print2D() const{
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i){
            for(int j(0); j < n; ++j){
                if(j) std::cout << " ";
                std::cout << (*this)[i][j];
            }
            std::cout << "\n";
        }
    }
 
    friend std::ostream& operator<<(std::ostream& os, const Matrix& B){
        size_t m = B.height(), n = B.width();
        for(int i(0); i < m; ++i){
            for(int j(0); j < n; ++j){
                if(j) os << " ";
                os << B[i][j];
            }
            os << "\n";
        }
        return (os);
    }
 
    static Matrix identity(size_t n){
        Matrix ret(n);
        for(int i(0); i < n; ++i) ret[i][i] = 1;
        return ret;
    }
 
    Matrix transpose() const{
        size_t n = height(), m = width();
        Matrix ret(m, n);
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                ret[i][j] = (*this)[j][i];
        return ret;
    }
 
    Matrix operator+() const{return *this;}
 
    Matrix operator-() const{
        size_t m = height(), n = width();
        Matrix temp(height(), width());
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                temp[i][j] = -(*this)[i][j];
        return temp;
    }
 
    Matrix& operator=(const Matrix& B){
        if(this != &B){
            A = B.A;
        }
        return *this;
    }
 
    Matrix& operator+=(const Matrix& B){
        assert(sameSize(B));
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] += B[i][j];
        return *this;
    }
 
    Matrix& operator-=(const Matrix& B){
        assert(sameSize(B));
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] -= B[i][j];
        return *this;
    }
 
    Matrix& operator*=(const Matrix& B){
        size_t m = height(), n = width(), l = B.width();
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i(0); i < m; ++i)
            for(int j(0); j < l; ++j)
                for(int k(0); k < n; ++k)
                    C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
        A.swap(C);
        return *this;
    }
 
    Matrix& operator*=(const T a){
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] *= a;
        return *this;
    }
 
    Matrix& operator%=(const long long &mod){
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] %= mod;
        return *this;
    }
 
    Matrix& operator^=(const Matrix &B){
        assert(sameSize(B));
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] ^= B[i][j];
        return *this;
    }
 
    Matrix& operator|=(const Matrix &B){
        assert(sameSize(B));
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                (*this)[i][j] |= B[i][j];
        return *this;
    }
 
    Matrix& operator&=(const Matrix &B){
        size_t m = height(), n = width(), l = B.width();
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i(0); i < m; ++i)
            for(int j(0); j < l; ++j)
                for(int k(0); k < n; ++k)
                    C[i][j] = (C[i][j] ^ ((*this)[i][k] & B[k][j]));
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
        size_t m = height(), n = width();
        for(int i(0); i < m; ++i)
            for(int j(0); j < n; ++j)
                if((*this)[i][j] != mat[i][j]) return false;
        return true;
    }
 
    bool operator!=(const Matrix& mat) const{return !(*this == mat);}
 
    Matrix modmul(const Matrix& B, long long mod){
        Matrix temp(*this);
        size_t m = height(), n = width(), l = B.width();
        assert(n == B.height());
        std::vector<std::vector<T>> C(m, std::vector<T>(l, 0));
        for(int i(0); i < m; ++i)
            for(int j(0); j < l; ++j)
                for(int k(0); k < n; ++k){
                    C[i][j] = (C[i][j] + temp[i][k] * B[k][j]) % mod;
                    if(C[i][j] < 0) C[i][j] += mod;
                }
        return C;
    }
    
    Matrix& modmmul(const Matrix& B){
        return modmul(B, MOD);
    }
 
    Matrix powWithoutMod(unsigned long long b) const{
        size_t n = height();
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
        size_t n = height();
        assert(n == width());
        Matrix ret = identity(n);
        Matrix a = *this;
        while(b){
            if(b & 1) ret = ret.modmul(a, mod);
            a = a.modmul(a, mod);
            for(int i(0); i < n; ++i){
                for(int j(0); j < n; ++j){
                    if(ret[i][j] < 0) ret[i][j] += mod;
                    if(a[i][j] < 0) a[i][j] += mod;
                }
            }
            b /= 2;
        }
        return ret;
    }
 
    Matrix power(unsigned long long b) const{
        return power(b, MOD);
    }
 
    Matrix powXorAnd(unsigned long long b) const{
        size_t n = height();
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

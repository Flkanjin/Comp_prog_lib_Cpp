#include <string>
#include <unordered_set>
#include <vector>
#include <utility>


//一致する全ての部分の左端のインデックス
class RollingHash2DIndex{
    std::vector<std::string>field, purpose;
    const unsigned long long B1{9973};
    const unsigned long long B2{100'000'007};
public:
    RollingHash2DIndex(){}
    RollingHash2DIndex(std::vector<std::string> T, std::vector<std::string> P): field{T}, purpose{P}{}
private:
    unsigned long long sthash(std::vector<std::string> s){
        int R{int(purpose.size())}, C{int(purpose[0].length())};
        std::vector<unsigned long long> tmp(R, 0ull);
        //行方向
        unsigned long long b1p{1};
        for(int i{0}; i < R; ++i) for(int j{0}; j < C; ++j) tmp[i] = tmp[i] * B1 + s[i][j];
        unsigned long long b2p{1}, hashed{0};
        for(int i{0}; i < R; ++i){
            b2p *= B2;
            hashed = hashed * B2 + tmp[i];
        }
        return hashed;
    }
public:
    void setPurpose(std::vector<std::string> s){
        purpose = s;
    }
    void setField(std::vector<std::string> s){
        field = s;
    }

    std::vector<std::pair<int, int>> getCommonIdx(){
        std::vector<std::pair<int, int>> ret;
        int H{int(field.size())}, W{int(field[0].length())}, R{int(purpose.size())}, C{int(purpose[0].length())};
        if(H < R || W < C) return ret;
        unsigned long long b1p{1}, b2p{1};
        for(int i{0}; i < C; ++i) b1p *= B1;
        for(int i{0}; i < R; ++i) b2p *= B2;
        unsigned long long fh{sthash(field)}, ph{sthash(purpose)}, prvRowLeft{fh};
        for(int i{0}, i_len{H-R}; i <= i_len; ++i){
            if(i){
                fh = prvRowLeft*B2;
                unsigned long long p1{1};
                for(int j{C-1}; j >= 0; --j){
                    fh += (-field[i-1][j] * b2p + field[i+R-1][j]) * p1;
                    p1 *= B1;
                }
                prvRowLeft = fh;
            }
            for(int j{0}, j_len{W-C}; j <= j_len; ++j){
                if(j){
                    unsigned long long p2{1};
                    fh *= B1;
                    for(int k{R-1}; k >= 0; --k){
                        fh += (-field[i+k][j-1]*b1p + field[i+k][j+C-1]) * p2;
                        p2 *= B2;
                    }
                }
                if(fh == ph) ret.emplace_back(i, j);
            }
        }
        return ret;
    }
};

//含まれるかどうかのみ
class RollingHash2DContained{
    std::vector<std::string> field, purpose;
    const unsigned long long B1{9973}, B2{100'000'007};
    std::unordered_set<unsigned long long> sset;
public:
    RollingHash2DContained(){}
    RollingHash2DContained(std::vector<std::string> T, std::vector<std::string> P): field{T}, purpose{P}{
        setSet();
    }
private:
    void setSet(){
        sset.clear();
        int H{int(field.size())}, W{int(field[0].length())}, R{int(purpose.size())}, C{int(purpose[0].length())};
        if(H >= R && W >= C){
            unsigned long long b1p{1}, b2p{1};
            for(int i{0}; i < C; ++i) b1p *= B1;
            for(int i{0}; i < R; ++i) b2p *= B2;
            unsigned long long fh{sthash(field)}, prvRowLeft{fh};
            for(int i{0}, i_len(H-R); i <= i_len; ++i){
                if(i){
                    fh = prvRowLeft*B2;
                    unsigned long long p1{1};
                    for(int j{C-1}; j >= 0; --j){
                        fh += (-field[i-1][j] * b2p + field[i+R-1][j]) * p1;
                        p1 *= B1;
                    }
                    prvRowLeft = fh;
                }
                for(int j{0}, j_len{W-C}; j <= j_len; ++j){
                    if(j){
                        unsigned long long p2{1};
                        fh *= B1;
                        for(int k{R-1}; k >= 0; --k){
                            fh += (-field[i+k][j-1]*b1p + field[i+k][j+C-1]) * p2;
                            p2 *= B2;
                        }
                    }
                    sset.insert(fh);
                }
            }
        }
    }
public:
    void setPurpose(std::vector<std::string> s){
        int prvh{int(purpose.size())}, prvw{int(purpose[0].length())};
        purpose = s;
        if(s.size() != prvh || s[0].length() != prvw) setSet();
    }
    void setField(std::vector<std::string> s){
        field = s;
        setSet();
    }
private:
    unsigned long long sthash(std::vector<std::string> s){
        int R{int(purpose.size())}, C{int(purpose[0].length())};
        std::vector<unsigned long long> tmp(R, 0ull);
        //行方向
        unsigned long long b1p{1};
        for(int i{0}; i < R; ++i){
            for(int j{0}; j < C; ++j){
                tmp[i] = tmp[i] * B1 + s[i][j];
            }
        }
        unsigned long long b2p{1}, hashed{0};
        for(int i{0}; i < R; ++i){
            b2p *= B2;
            hashed = hashed * B2 + tmp[i];
        }
        return hashed;
    }
public:
    bool contain(){
        return sset.find(sthash(purpose)) != sset.end();
    }
};

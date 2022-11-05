#include <string>
#include <unordered_set>
#include <vector>


//一致する全ての部分の左端のインデックス
class RollingHash1DIndex{
    std::string field, purpose;
    const unsigned long long B{100'000'007};
public:
    RollingHash1DIndex(){}
    RollingHash1DIndex(std::string T, std::string P): field{T}, purpose{P}{}
private:
    unsigned long long sthash(std::string s){
        int pl{int(purpose.length())};
        unsigned long long bp{1};
        for(int i{0}; i < pl; ++i) bp *= B;
        unsigned long long hashed{0};
        for(int i{0}; i < pl; ++i) hashed = hashed*B + s[i];
        return hashed;
    }
public:
    void setPurpose(std::string s){
        purpose = s;
    }
    void setField(std::string s){
        field = s;
    }

    std::vector<int> getCommonIdx(){
        std::vector<int> ret;
        int fl{int(field.length())}, pl{int(purpose.length())};
        if(fl < pl) return ret;
        unsigned long long bp{1};
        for(int i{0}; i < pl; ++i) bp *= B;
        unsigned long long fh{sthash(field)}, ph{sthash(purpose)};
        for(int i{0}, i_len(fl-pl); i <= i_len; ++i){
            if(fh == ph) ret.push_back(i);
            if(i < fl-pl) fh = fh*B + field[i + pl] - field[i]*bp;
        }
        return ret;
    }
};


//含まれるかどうかのみ
//蛇足 普通にunordered_set<string>にsubstrを入れればいい
class RollingHash1DContained{
    std::string field, purpose;
    std::unordered_set<unsigned long long> sset;
    const unsigned long long B{100'000'007};
public:
    RollingHash1DContained(){}
    RollingHash1DContained(std::string T, std::string P): field{T}, purpose{P}{
        setSet();
    }
private:
    void setSet(){
        sset.clear();
        int fl{int(field.length())}, pl{int(purpose.length())};
        if(fl >= pl){
            unsigned long long bp{1};
            for(int i{0}; i < pl; ++i) bp *= B;
            unsigned long long hashed{sthash(field)};
            for(int i{0}, i_len{fl-pl}; i <= i_len; ++i){
                sset.insert(hashed);
                if(i < fl-pl) hashed = hashed*B + field[i + pl] - field[i]*bp;
            }
        }
    }
public:
    void setPurpose(std::string s){
        int prvln{int(purpose.length())};
        purpose = s;
        if(s.length() != prvln) setSet();
    }

    void setField(std::string s){
        field = s;
        setSet();
    }
private:
    unsigned long long sthash(std::string s){
        int pl{int(purpose.length())};
        unsigned long long bp{1};
        for(int i{0}; i < pl; ++i) bp *= B;
        unsigned long long hashed{0};
        for(int i{0}; i < pl; ++i) hashed = hashed*B + s[i];
        return hashed;
    }
public:
    bool contain(){
        return sset.find(sthash(purpose)) != sset.end();
    }
};

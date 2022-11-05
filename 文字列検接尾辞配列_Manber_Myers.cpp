/*
O(|S| log^2 (S))
検索は O(T log S)
*/
#include <string>
#include <algorithm>
#include <vector>


class suffixArray_MM{
    std::string field;
    std::vector<int> rank;
    std::vector<int> sa;
    int k;
public:
    suffixArray_MM(std::string s): field{s}, rank{int(s.length()) + 1}, sa{int(s.length()) + 1}{
        construct_sa();
    }
private:
    void construct_sa(){
        int n{int(field.length())};
        for(int i{0}; i <= n; ++i){
            sa[i] = i;
            rank[i] = ((i < n) ? field[i] : -1);
        }
        std::vector<int> tmp(n + 1);
        for(k = 1; k <= n; k *= 2){
            auto comp_sa{[&](int i, int j){
                if(this->rank[i] != this->rank[j]) return this->rank[i] < this->rank[j];
                int ri{((i+k <= int(field.size())) ? this->rank[i+k] : -1)};
                int rj{((j+k <= int(field.size())) ? this->rank[j+k] : -1)};
                return ri < rj;
            }};
            std::sort(std::begin(sa), std::end(sa), comp_sa);

            tmp[sa[0]] = 0;
            for(int i{1}; i <= n; ++i){
                tmp[sa[i]] = tmp[sa[i-1]] + (comp_sa(sa[i-1], sa[i]) ? 1 : 0);
            }
            for(int i{0}; i <= n; ++i) rank[i] = tmp[i];
        }
    }
public:
    bool contain(std::string purpose){
        int m{int(purpose.length())};
        int a{0}, b{int(field.length())};
        while(b-a > 1){
            int c{(a+b) / 2};
            (field.compare(sa[c], m, purpose) < 0 ? a : b) = c;
        }
        return !field.compare(sa[b], m, purpose);
    }
    std::vector<int> con_index(std::string purpose){
        std::vector<int> ret;
        int m{int(purpose.length())};
        int a{0}, b{int(field.length())};
        while(b-a > 1){
            int c{(a+b) / 2};
            (field.compare(sa[c], m, purpose) < 0 ? a : b) = c;
        }
        if(field.compare(sa[b], m, purpose)) return ret;
        int c{0}, d{int(field.length())};
        while(d-c > 1){
            int e{(c+d) / 2};
            (field.compare(sa[e], m, purpose) > 0 ? d : c) = e;
        }
        for(int i{b}; i <= c; ++i) ret.push_back(sa[i]);
        std::sort(std::begin(ret), std::end(ret));
        return ret;
    }

    int num(std::string purpose){
        std::vector<int> a{con_index(purpose)};
        return a.size();
    }
};

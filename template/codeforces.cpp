#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <concepts>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr int MOD{1'000'000'007};
constexpr int MOD2{998'244'353};
constexpr int INF{1'000'000'000}; //1e9
constexpr int NIL{-1};
constexpr long long LINF{1'000'000'000'000'000'000}; // 1e18
constexpr long double EPS{1E-10L};
using namespace std::literals;
namespace ranges = std::ranges;
namespace views = ranges::views;

template<class T, class S> bool chmax(T &a, const S &b){
    if(a < b){a = b; return true;}
    return false;
}
template<class T, class S> bool chmin(T &a, const S &b){
    if(b < a){a = b; return true;}
    return false;
}
template<class T> bool inside(T x, T lx, T rx){ //semi-open
    return (ranges::clamp(x, lx, rx-1) == x);
}
template<class T> bool inside(T x, T y, T lx, T rx, T ly, T ry){
    return inside(x, lx, rx) && inside(y, ly, ry);
}
template<class T, class S> std::istream &operator>>(std::istream &is, std::pair<T, S> &p){
    return is >> p.first >> p.second;
}
template<class T, class S> std::ostream &operator<<(std::ostream &os, const std::pair<T, S> &p){
    return os << p.first << " " << p.second;
}
template<class T> std::istream &operator>>(std::istream &is, std::vector<T> &v){
    {for(auto &e: v) is >> e;} return is;
}
template<class Container> void print_container(const Container &c, std::string sep = " "s, std::string end = "\n"s){
    for(int i{int(std::size(c))}; auto e: c) std::cout << e << (--i ? sep : end);
}
std::string yesno(bool x){return x ? "Yes"s : "No"s;}



int main(){
    
    return 0;
}

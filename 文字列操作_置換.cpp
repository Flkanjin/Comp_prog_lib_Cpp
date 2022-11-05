#include <string>


//ret内のfromをすべてtoに
std::string replaceAll(std::string &ret, std::string from, std::string to){
    std::size_t pos{ret.find(from)};
    int to_len{int(to.length())}, from_len{int(from.length())};
    if(from.empty()) return ret;
    while((pos = ret.find(from, pos)) != std::string::npos){
        ret.replace(pos, from_len, to);
        pos += to_len;
    }
    return ret;
}

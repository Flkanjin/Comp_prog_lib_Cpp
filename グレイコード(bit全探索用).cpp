inline int grayCode(int i){
    return i ^ (i >> 1);
}

inline int invGrayCode(int j){
    for(int k{0}; k < 5; ++k){// 2pow(5) = 32
        j = j ^ (j >> (1<<k));
    }
    return j;
}

#include <unordered_map>
#include <bit>

// std::unordered_map<int, int> twoPow{{1, 0}, {2, 1}, {4, 2}, {8, 3}, {16, 4}, {32, 5}, {64, 6}, {128, 7}, {256, 8}, {512, 9}, {1024, 10}, {2048, 11}, {4096, 12}, {8192, 13}, {16384, 14}, {32768, 15}, {65536, 16}, {131072, 17}, {262144, 18}, {524288, 19}};

void bitSearch(int n){
    // i = 0 の時の処理

    for(auto biti{1U}, biti_len{1U << n}; biti < biti_len; ++biti){
        auto bitj{biti ^ (biti >> 1)}; int j{std::countr_zero(biti)};
        // auto bitj{biti ^ (biti >> 1)}; int j{__builtin_ctz(biti)}; // C++17
        if(bitj & (1U << j)){// changeBit が立った
            
        }else{// changeBit がなくなった
            
        }
        //何か処理
        
    }
}
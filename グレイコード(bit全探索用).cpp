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

std::unordered_map<int, int> twoPow{{1, 0}, {2, 1}, {4, 2}, {8, 3}, {16, 4}, {32, 5}, {64, 6}, {128, 7}, {256, 8}, {512, 9}, {1024, 10}, {2048, 11}, {4096, 12}, {8192, 13}, {16384, 14}, {32768, 15}, {65536, 16}, {131072, 17}, {262144, 18}, {524288, 19}};

void bitSearch(int n){
    int prvj(0);
    // i = 0 の時の処理

    for(int i{1}, i_len{1 << n}; i < i_len; ++i){
        int j = grayCode(i);
        int changebit = j ^ prvj;
        if(j & changebit){// changeBit が立った
            
        }else{// changeBit がなくなった
            
        }
        //何か処理

        prvj = j;
    }
}
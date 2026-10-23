#include "randnum.h"

//不放在.h 文件内，每个引用./h 文件的文件都会单独复制一份，导致报错

namespace sn {
    std::random_device rd;  //种子
    std::mt19937 gen(rd());  //随机引擎
}

int sn::random_number(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
}


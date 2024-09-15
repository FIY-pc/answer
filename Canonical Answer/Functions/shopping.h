//
// Created by lenovo on 2024/9/15.
//

#ifndef CANONICAL_ANSWER_SHOPPING_H
#define CANONICAL_ANSWER_SHOPPING_H

#include "Config.h"
#include "io.h"
#include "data.h"

struct shopping_cart{
    double total_money;
    //  goods_statistics二维数组用于统计商品数据,第一个index+1即为货道数,其中包含的每个数组表示某种商品,构成为{单价,购买数量,总金额}
    double goods_statistics[LANES][3];
};

struct shopping_cart *shopping();

#endif //CANONICAL_ANSWER_SHOPPING_H

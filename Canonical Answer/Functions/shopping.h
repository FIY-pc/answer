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
    //  goods_statistics��ά��������ͳ����Ʒ����,��һ��index+1��Ϊ������,���а�����ÿ�������ʾĳ����Ʒ,����Ϊ{����,��������,�ܽ��}
    double goods_statistics[LANES][3];
};

struct shopping_cart *shopping();

#endif //CANONICAL_ANSWER_SHOPPING_H

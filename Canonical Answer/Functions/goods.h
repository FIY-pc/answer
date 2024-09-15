#ifndef CANONICAL_ANSWER_GOODS_H
#define CANONICAL_ANSWER_GOODS_H

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "io.h"
#include "data.h"

struct goods{
    int lane;
    char name[GOODS_NAME_MAXIMUM_LENGTH];
    double price;
    int num;
};

void good_add();
void good_create(int lane);
void good_num_add(int lane);

void good_remove();
#endif //CANONICAL_ANSWER_GOODS_H
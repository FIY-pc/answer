//
// Created by lenovo on 2024/9/9.
//

#ifndef CANONICAL_ANSWER_GOODS_H
#define CANONICAL_ANSWER_GOODS_H

#endif //CANONICAL_ANSWER_GOODS_H

#include <stdio.h>
#include <stdlib.h>
#include "../Config.h"
struct goods {
    char name[100];
    int lane;
    float price;
    int nums;
};

int goods_add(){
    struct goods* pgood = (struct goods*) malloc(sizeof (struct goods));
    if(pgood==NULL){
        return -1;
    }
    // 输入
    printf("请输入商品名:");
    scanf("%99s",pgood->name);
    if(*(pgood->name)=='\0'){
        printf("名称不能为空!");
    }

    printf("货道:");
    scanf("%2d",&(pgood->lane));
    if(pgood->lane>LANES){
        printf("货道超出上限!");
    }
    if(pgood->lane<=0){
        printf("货道不能为0或负数!");
    }

    printf("价钱:");
    scanf("%f",&(pgood->price));
    if(pgood->price<0){
        printf("价钱不能为负!");
    }

    printf("数量:");
    scanf("%d",&(pgood->nums));
    if(pgood->nums<=0){
        printf("数量不能为0或负数!");
    }
    getchar();

    //测试
    //printf("%s,%d,%.2f,%d",pgood->name,pgood->lane,pgood->price,pgood->nums);

    free(pgood);
    return 0;
}
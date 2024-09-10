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
    // ����
    printf("��������Ʒ��:");
    scanf("%99s",pgood->name);
    if(*(pgood->name)=='\0'){
        printf("���Ʋ���Ϊ��!");
    }

    printf("����:");
    scanf("%2d",&(pgood->lane));
    if(pgood->lane>LANES){
        printf("������������!");
    }
    if(pgood->lane<=0){
        printf("��������Ϊ0����!");
    }

    printf("��Ǯ:");
    scanf("%f",&(pgood->price));
    if(pgood->price<0){
        printf("��Ǯ����Ϊ��!");
    }

    printf("����:");
    scanf("%d",&(pgood->nums));
    if(pgood->nums<=0){
        printf("��������Ϊ0����!");
    }
    getchar();

    //����
    //printf("%s,%d,%.2f,%d",pgood->name,pgood->lane,pgood->price,pgood->nums);

    free(pgood);
    return 0;
}
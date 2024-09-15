#include "goods.h"

void good_add(){
    int lane = 0;
    while (1){
        printf("货道:");
        input_i(&lane);
        // 特殊标记处理
        if(lane == io_back){
            return;
        }
        if (lane == io_error){
            printf("输入错误,请重新输入\n");
            continue;
        }

        if(errno==ERANGE){
            printf("输入错误\n");
            continue;
        }
        if(lane>LANES){
            printf("货道超出设计货道数,请重新输入\n");
            continue;
        }
        if(lane<=0){
            printf("货道不能为0或负数,请重新输入\n");
            continue;
        }
        // 货道可用检查
        int available_judge = lane_available_check(lane);
        if(available_judge == LANE_UNAVAILABLE){
            good_num_add(lane);
        }
        else if(available_judge == LANE_AVAILABLE){
            good_create(lane);
        }
        break;
    }
}

void good_create(int lane){
    setGBK();
    struct goods* pgood = (struct goods *)malloc(sizeof(struct goods));
    if(pgood==NULL){
        perror("Failed to allocate memory to pgood");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    char name[GOODS_NAME_MAXIMUM_LENGTH];
    double price = 0;
    int num = 0;

    // 输入
    pgood->lane = lane;

    while (1){
        printf("请输入商品名:");
        scanf("%99s",name);
        // 特殊标记处理
        if(strcmp(name,BACK_WORD) == 0){
            return;
        }

        if(*name =='\0'){
            printf("名称不能为空,请重新输入\n");
            continue;
        }
        int length = (int)strlen(name);
        if (length > GOODS_NAME_MAXIMUM_LENGTH){
            printf("名称长度超出最大范围");
            continue;
        }

        strcpy(pgood->name,name);
        getchar();
        break;
    }

    while (1){
        printf("单价:");
        input_f(&price);
        // 特殊标记处理
        if(price == io_back){
            return;
        }

        if(errno==ERANGE){
            printf("输入错误\n");
            continue;
        }
        if(price<0){
            printf("单价不能为负,请重新输入\n");
            continue;
        }
        pgood->price = price;
        break;
    }

    while (1){
        printf("数量:");
        input_i(&num);
        // 特殊标记处理
        if(num == io_back){
            return;
        }
        if(errno==ERANGE){
            printf("输入错误\n");
            continue;
        }
        if(num<=0){
            printf("数量不能为0或负数,请重新输入\n");
            continue;
        }
        pgood->num = num;
        break;
    }
    // 将商品信息写入数据库
    good_update(pgood->lane,pgood->name,pgood->price,pgood->num);

    printf("\n成功添加货物,\n商品名:%s\n货道:%d\n单价:%.2f\n数量:%d\n",name,lane,price,num);
    free(pgood);
}

void good_num_add(int lane){
    struct goods *good = return_good_one(lane);
    int add_num = 0;
    printf("你将对货道 %d 名称 %s 单价 %lf 数量 %d 的商品进行添加\n",good->lane,good->name,good->price,good->num);
    printf("请输入添加数量:");
    input_i(&add_num);
    // 特殊标记处理
    if(add_num == io_back){
        return;
    }
    good_num_update(lane,(good->num)+add_num);
    printf("添加完成!当前 %s 商品数量为 %d\n",good->name,(good->num)+add_num);
    free(good);
}

void good_remove(){
    int lane;
    while (1){
        printf("请输入要下架的商品所在的货道:");
        input_i(&lane);
        // 特殊标记处理
        if(lane == io_back){
            return;
        }
        if(errno==ERANGE){
            printf("输入错误\n");
            continue;
        }
        if(lane>LANES){
            printf("货道超出设计货道数,请重新输入\n");
            continue;
        }
        if(lane<=0){
            printf("货道不能为0或负数,请重新输入\n");
            continue;
        }
        int available_judge = lane_available_check(lane);
        if(available_judge == LANE_AVAILABLE){
            printf("该货道无商品,请重新输入");
            continue;
        }
        break;
    }
    good_delete_one(lane);
}
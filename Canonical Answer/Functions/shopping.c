//
// Created by lenovo on 2024/9/15.
//

#include "shopping.h"

struct shopping_cart *shopping(){
    setGBK();
    // 此函数在任意输入场合时输入BACK_WORD均会退出
    struct shopping_cart * cart = (struct shopping_cart *) malloc(sizeof (struct shopping_cart));

    for (int i = 0; i < LANES; i++) {
        for (int j = 0; j < 3; j++) {
            cart->goods_statistics[i][j] = 0.0;
        }
    }
    divider();

    while (1) {
        int lane = 0;
        int num = 0;
        while (1) {
            printf("请输入商品所在的货道:");
            input_i(&lane);
            // 特殊标记处理
            if (lane == io_back) {
                return NULL;
            }
            // 常规检查
            if (errno == ERANGE) {
                printf("输入错误\n");
                continue;
            }
            if (lane > LANES) {
                printf("货道超出设计货道数,请重新输入\n");
                continue;
            }
            if (lane <= 0) {
                printf("货道不能为0或负数,请重新输入\n");
                continue;
            }
            // 空货道检查
            int available_judge = lane_available_check(lane);
            if (available_judge == LANE_AVAILABLE) {
                printf("该货道无商品,请重新选择\n");
                continue;
            }
            break;
        }

        while (1){
            printf("请输入购买数量:");
            input_i(&num);
            // 特殊标记处理
            if(num == io_back){
                return NULL;
            }
            // 常规检查
            if(errno==ERANGE){
                printf("输入错误\n");
                continue;
            }
            if(num<=0){
                printf("数量不能为0或负数,请重新输入\n");
                continue;
            }
            if (num > return_num_one(lane)){
                printf("购买数量超出剩余货物数量,请重新输入\n");
                continue;
            }
            break;
        }
        // 更新购物车
        cart->goods_statistics[lane][0] = return_price_one(lane);
        cart->goods_statistics[lane][1] = num;

        printf("商品添加完成,当前购物车:\n");
        printf("货道\t名称\t单价\t数量\t金额\n");
        for (int i = 0; i < LANES; i++) {
            if(cart->goods_statistics[i][0] == 0){
                continue;
            }
            cart->goods_statistics[i][2] = cart->goods_statistics[i][0]*(int)cart->goods_statistics[i][1];

            goods_fix_information_one(lane);
            printf("\t%d\t%.2lf\n",(int)cart->goods_statistics[i][1],cart->goods_statistics[i][2]);
        }

        double money = 0;
        for (int i = 0; i < LANES; i++) {
            money = money + cart->goods_statistics[i][2];
        }
        cart->total_money = money;
        printf("总金额:%.2lf\n",cart->total_money);

        // 完成一次购买
        printf("按下回车继续购买,输入 %s 确定结账\n(请注意:确定之后若输入back强制退出将损失购物车信息和已付金额)\n",FINISH_WORD);
        char judge[BUFFER_MAXIMUM_LENGTH];
        fgets(judge,sizeof (judge),stdin);
        judge[strcspn(judge, "\n")] = 0;
        // 特殊标记处理
        if(strcmp(judge,FINISH_WORD)==0){
            printf("确定结账\n");
            return cart;
        }
        if (strcmp(judge,BACK_WORD)==0){
            return NULL;
        }
    }

}

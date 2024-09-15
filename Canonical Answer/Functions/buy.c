//
// Created by lenovo on 2024/9/15.
//

#include "buy.h"

int coin_buy(struct shopping_cart * cart){
    int total_money = (int)cart->total_money;

    if(total_money != cart->total_money){
        total_money++;
    }

    printf("应收:%d\n",total_money);

    int coin = 0;
    int receive = 0;
    // 付款
    while (receive < total_money){
        printf("请投币(输入数字即可):\n1元\t2元\t5元\n");
        input_i(&coin);
        if(errno==ERANGE){
            printf("输入错误\n");
            continue;
        }
        switch (coin) {
            case io_back:
                return io_back;
            case 1:
                receive++;
                break;
            case 2:
                receive = receive + 2;
                break;
            case 5:
                receive = receive + 5;
                break;
            default:
                printf("无效投币,请重新输入\n");
                continue;
        }
        printf("投币成功!请继续投币\n");
    }

    // 完成购买,更新商品数据
    for (int i = 0; i < LANES; i++) {
        if (cart->goods_statistics[i][0] == 0){
            continue;
        }
        int remain_num = return_num_one(i)-(int)cart->goods_statistics[i][1];
        good_num_update(i,remain_num);
    }

    // 打印账单
    printf("\t\t自助售货机账单\n");
    printf("货道\t名称\t单价\t数量\t金额\n");
    for (int i = 0; i < LANES; i++) {
        if(cart->goods_statistics[i][0] == 0){
            continue;
        }
        cart->goods_statistics[i][2] = cart->goods_statistics[i][0]*(int)cart->goods_statistics[i][1];

        goods_fix_information_one(i+1);
        printf("\t%d\t%.2lf\n",(int)cart->goods_statistics[i][1],cart->goods_statistics[i][2]);
    }
    printf("应收:%d\t实收:%d\t找零:%d\n",total_money,receive,receive-total_money);

    printf("购买完成!本界面将在%d秒后自动关闭\n",SLEEP_SECONDS);
    return 0;
}
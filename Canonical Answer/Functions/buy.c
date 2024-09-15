//
// Created by lenovo on 2024/9/15.
//

#include "buy.h"

int coin_buy(struct shopping_cart * cart){
    int total_money = (int)cart->total_money;

    if(total_money != cart->total_money){
        total_money++;
    }

    printf("Ӧ��:%d\n",total_money);

    int coin = 0;
    int receive = 0;
    // ����
    while (receive < total_money){
        printf("��Ͷ��(�������ּ���):\n1Ԫ\t2Ԫ\t5Ԫ\n");
        input_i(&coin);
        if(errno==ERANGE){
            printf("�������\n");
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
                printf("��ЧͶ��,����������\n");
                continue;
        }
        printf("Ͷ�ҳɹ�!�����Ͷ��\n");
    }

    // ��ɹ���,������Ʒ����
    for (int i = 0; i < LANES; i++) {
        if (cart->goods_statistics[i][0] == 0){
            continue;
        }
        int remain_num = return_num_one(i)-(int)cart->goods_statistics[i][1];
        good_num_update(i,remain_num);
    }

    // ��ӡ�˵�
    printf("\t\t�����ۻ����˵�\n");
    printf("����\t����\t����\t����\t���\n");
    for (int i = 0; i < LANES; i++) {
        if(cart->goods_statistics[i][0] == 0){
            continue;
        }
        cart->goods_statistics[i][2] = cart->goods_statistics[i][0]*(int)cart->goods_statistics[i][1];

        goods_fix_information_one(i+1);
        printf("\t%d\t%.2lf\n",(int)cart->goods_statistics[i][1],cart->goods_statistics[i][2]);
    }
    printf("Ӧ��:%d\tʵ��:%d\t����:%d\n",total_money,receive,receive-total_money);

    printf("�������!�����潫��%d����Զ��ر�\n",SLEEP_SECONDS);
    return 0;
}
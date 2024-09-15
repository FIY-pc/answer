//
// Created by lenovo on 2024/9/15.
//

#include "shopping.h"

struct shopping_cart *shopping(){
    setGBK();
    // �˺������������볡��ʱ����BACK_WORD�����˳�
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
            printf("��������Ʒ���ڵĻ���:");
            input_i(&lane);
            // �����Ǵ���
            if (lane == io_back) {
                return NULL;
            }
            // ������
            if (errno == ERANGE) {
                printf("�������\n");
                continue;
            }
            if (lane > LANES) {
                printf("����������ƻ�����,����������\n");
                continue;
            }
            if (lane <= 0) {
                printf("��������Ϊ0����,����������\n");
                continue;
            }
            // �ջ������
            int available_judge = lane_available_check(lane);
            if (available_judge == LANE_AVAILABLE) {
                printf("�û�������Ʒ,������ѡ��\n");
                continue;
            }
            break;
        }

        while (1){
            printf("�����빺������:");
            input_i(&num);
            // �����Ǵ���
            if(num == io_back){
                return NULL;
            }
            // ������
            if(errno==ERANGE){
                printf("�������\n");
                continue;
            }
            if(num<=0){
                printf("��������Ϊ0����,����������\n");
                continue;
            }
            if (num > return_num_one(lane)){
                printf("������������ʣ���������,����������\n");
                continue;
            }
            break;
        }
        // ���¹��ﳵ
        cart->goods_statistics[lane][0] = return_price_one(lane);
        cart->goods_statistics[lane][1] = num;

        printf("��Ʒ������,��ǰ���ﳵ:\n");
        printf("����\t����\t����\t����\t���\n");
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
        printf("�ܽ��:%.2lf\n",cart->total_money);

        // ���һ�ι���
        printf("���»س���������,���� %s ȷ������\n(��ע��:ȷ��֮��������backǿ���˳�����ʧ���ﳵ��Ϣ���Ѹ����)\n",FINISH_WORD);
        char judge[BUFFER_MAXIMUM_LENGTH];
        fgets(judge,sizeof (judge),stdin);
        judge[strcspn(judge, "\n")] = 0;
        // �����Ǵ���
        if(strcmp(judge,FINISH_WORD)==0){
            printf("ȷ������\n");
            return cart;
        }
        if (strcmp(judge,BACK_WORD)==0){
            return NULL;
        }
    }

}

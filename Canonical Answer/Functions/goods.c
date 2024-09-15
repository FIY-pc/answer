#include "goods.h"

void good_add(){
    int lane = 0;
    while (1){
        printf("����:");
        input_i(&lane);
        // �����Ǵ���
        if(lane == io_back){
            return;
        }
        if (lane == io_error){
            printf("�������,����������\n");
            continue;
        }

        if(errno==ERANGE){
            printf("�������\n");
            continue;
        }
        if(lane>LANES){
            printf("����������ƻ�����,����������\n");
            continue;
        }
        if(lane<=0){
            printf("��������Ϊ0����,����������\n");
            continue;
        }
        // �������ü��
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

    // ����
    pgood->lane = lane;

    while (1){
        printf("��������Ʒ��:");
        scanf("%99s",name);
        // �����Ǵ���
        if(strcmp(name,BACK_WORD) == 0){
            return;
        }

        if(*name =='\0'){
            printf("���Ʋ���Ϊ��,����������\n");
            continue;
        }
        int length = (int)strlen(name);
        if (length > GOODS_NAME_MAXIMUM_LENGTH){
            printf("���Ƴ��ȳ������Χ");
            continue;
        }

        strcpy(pgood->name,name);
        getchar();
        break;
    }

    while (1){
        printf("����:");
        input_f(&price);
        // �����Ǵ���
        if(price == io_back){
            return;
        }

        if(errno==ERANGE){
            printf("�������\n");
            continue;
        }
        if(price<0){
            printf("���۲���Ϊ��,����������\n");
            continue;
        }
        pgood->price = price;
        break;
    }

    while (1){
        printf("����:");
        input_i(&num);
        // �����Ǵ���
        if(num == io_back){
            return;
        }
        if(errno==ERANGE){
            printf("�������\n");
            continue;
        }
        if(num<=0){
            printf("��������Ϊ0����,����������\n");
            continue;
        }
        pgood->num = num;
        break;
    }
    // ����Ʒ��Ϣд�����ݿ�
    good_update(pgood->lane,pgood->name,pgood->price,pgood->num);

    printf("\n�ɹ���ӻ���,\n��Ʒ��:%s\n����:%d\n����:%.2f\n����:%d\n",name,lane,price,num);
    free(pgood);
}

void good_num_add(int lane){
    struct goods *good = return_good_one(lane);
    int add_num = 0;
    printf("�㽫�Ի��� %d ���� %s ���� %lf ���� %d ����Ʒ�������\n",good->lane,good->name,good->price,good->num);
    printf("�������������:");
    input_i(&add_num);
    // �����Ǵ���
    if(add_num == io_back){
        return;
    }
    good_num_update(lane,(good->num)+add_num);
    printf("������!��ǰ %s ��Ʒ����Ϊ %d\n",good->name,(good->num)+add_num);
    free(good);
}

void good_remove(){
    int lane;
    while (1){
        printf("������Ҫ�¼ܵ���Ʒ���ڵĻ���:");
        input_i(&lane);
        // �����Ǵ���
        if(lane == io_back){
            return;
        }
        if(errno==ERANGE){
            printf("�������\n");
            continue;
        }
        if(lane>LANES){
            printf("����������ƻ�����,����������\n");
            continue;
        }
        if(lane<=0){
            printf("��������Ϊ0����,����������\n");
            continue;
        }
        int available_judge = lane_available_check(lane);
        if(available_judge == LANE_AVAILABLE){
            printf("�û�������Ʒ,����������");
            continue;
        }
        break;
    }
    good_delete_one(lane);
}
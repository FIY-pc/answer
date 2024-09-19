#include "level2-2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void transition(State **head,State **tail,Event event){
    switch (event) {
        case event_next:
            (*tail)++;
            **tail = *(*tail-1);
            if(*tail-*head == 3){
                (*head)++;
            }
            break;
        case event_back:
            if(*tail!=*head && (*tail)->type!=type_finish){
                state_init(*tail);
                (*tail)--;
            }
            break;
        case event_stay:
            break;
        case event_end:
            (*tail)++;
            **tail = *(*tail-1);
            (*tail)->type = type_end;
            break;
    }
}

Event handleState(State **state){
    Event event;
    switch ((*state)->type) {
        case type_add:
            event = add(*state);
            return event;
        case type_buy:
            event = buy(*state);
            return event;
        case type_pay:
            event = pay(*state);
            return event;
        case type_end:
            switch ((*state-1)->type) {
                case type_add:
                    (*state)++;
                    **state = *(*state-1);
                    (*state)->type = type_buy;
                    return event_stay;
                case type_buy:
                    (*state)++;
                    **state = *(*state-1);
                    (*state)->type = type_pay;
                    return event_stay;
                case type_pay:
                    (*state)++;
                    **state = *(*state-1);
                    (*state)->type = type_finish;
                    return event_stay;
            }
            break;
        case type_finish:
            non_goods_check(*state);
            (*state)++;
            **state = *(*state-1);
            (*state)->type = type_buy;

            (*state)->receive = 0;
            for (int i = 0; i < 249; i++) {
                for (int j = 0; j < 1; j++) {
                    (*state)->shopping_cart[i][j] = 0;
                }
            }
            return event_stay;
    }
}

int main(){
    State process[500];
    State *head = process;
    state_init(head);
    State *tail = head;
    Event event;

    while (1){
        event = handleState(&tail);
        transition(&head,&tail,event);
    }
}

void state_init(State *state){
    state->type = type_add;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; ++j) {
            state->goods[i][j] = 0;
        }
    }
    for (int i = 0; i < 249; i++) {
        for (int j = 0; j < 1; j++) {
            state->shopping_cart[i][j] = 0;
        }
    }
    state->receive = 0;
}

void non_goods_check(State *tail){
    for (int i = 0; i < 5; i++) {
        if (tail->goods[i][2] > 0) {
            return;
        }
    }
    printf("货架上已无商品\n");
    exit(0);

}

Event add(State *tail){
    printf("请添加商品\n");
    printf("名称\t通道\t单价\t数量\n");
    char input[256];
    fgets(input,sizeof (input),stdin);
    input[strcspn(input,"\n")] = 0;
    if(strcmp(input,BACK_WORD) == 0){
        return event_back;
    }
    if(strcmp(input,END_WORD) == 0){
        return event_end;
    }
    add_to_state(input,tail);
    return event_next;
}

Event buy(State *tail){
    printf("请购买商品\n");
    printf("名称\t通道\t数量\n");
    char input[256];
    fgets(input,sizeof (input),stdin);
    input[strcspn(input,"\n")] = 0;
    if(strcmp(input,BACK_WORD) == 0){
        return event_back;
    }
    if(strcmp(input,END_WORD) == 0){
        return event_end;
    }
    buy_update_state(input,tail);
    return event_next;
}

Event pay(State *tail){
    int total_money = 0;
    for (int i = 0; i < 250; i++) {
        if(tail->shopping_cart[i][0] == 0){
            break;
        }
        total_money = total_money + tail->shopping_cart[i][2];
    }
    if(tail->receive >= total_money){
        printf("找零:%d\n",tail->receive - total_money);
        return event_end;
    }
    printf("应收%d元\n",total_money);
    printf("请投币\n1元\t3元\t5元\n");
    char input[256];
    fgets(input,sizeof (input),stdin);
    input[strcspn(input,"\n")] = 0;
    if(strcmp(input,BACK_WORD) == 0){
        return event_back;
    }
    if((int )*input == 49 || (int )*input == 50 || (int )*input == 53){
        tail->receive = tail->receive +((int )*input - 48);
    }
    return event_next;
}

void buy_update_state(char *input,State *tail){
    int name;
    int lane;
    int num = 0;

    if((int )*input >=65 && (int )*input <=90){
        name = (int )*input;
    }else{
        printf("名称错误");
        return;
    }
    input++;
    if(*input != ' '){
        printf("格式错误!");
        return;
    }
    input++;
    if((int )*input >=49 && (int )*input <=53){
        lane = (int )*input - 48;
    } else{
        printf("通道错误\n");
        return;
    }
    input++;
    if(*input != ' '){
        printf("格式错误!\n");
        return;
    }
    input++;
    int judge = sscanf(input,"%d",&num);
    if(judge!=1){
        printf("数量错误\n");
        return;
    }
    if(num > tail->goods[lane][2]){
        printf("超出可购买数量\n");
        return;
    }

    // 更新架上数量
    tail->goods[lane][2] = tail->goods[lane][2] - num;
    // 添加购买记录
    int i;
    for (i = 0; i < 249; i++) {
        if(tail->shopping_cart[i][0] == 0){
            break;
        }
    }

    tail->shopping_cart[i][0] = lane;
    tail->shopping_cart[i][1] = num;
    tail->shopping_cart[i][2] = tail->goods[lane][1] * num;
}

void add_to_state(char *input,State *tail){
    int name;
    int lane;
    int price;
    int num = 0;

    if((int )*input >=65 && (int )*input <=90){
        name = (int )*input;
    }else{
        printf("名称错误");
        return;
    }
    input++;
    if(*input != ' '){
        printf("格式错误!");
        return;
    }
    input++;
    if((int )*input >=49 && (int )*input <=53){
        lane = (int )*input - 48;
    } else{
        printf("通道错误\n");
        return;
    }
    input++;
    if(*input != ' '){
        printf("格式错误!\n");
        return;
    }
    input++;
    if((int )*input >=49 && (int )*input <=57){
        price = (int )*input - 48;
    } else{
        printf("单价错误\n");
        return;
    }
    input++;
    if(*input != ' '){
        printf("格式错误!\n");
        return;
    }
    input++;
    int judge = sscanf(input,"%d",&num);
    if(judge!=1){
        printf("数量错误\n");
        return;
    }
    if(num >50){
        printf("数量错误\n");
        return;
    }

    tail->goods[lane][0] = name;
    tail->goods[lane][1] = price;
    tail->goods[lane][2] = num;
}
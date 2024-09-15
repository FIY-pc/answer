#include "Functions.h"
#include "version.h"
#include "Config.h"
#include <unistd.h>
// 状态转换示意图
//    <-------------------------------^
//    |                               |
//    |                               |
// begin-->manage_begin-->manage_1    |
//      |              |->manage_2    |
//      |              |->manage_3    |
//      |              |->manage_4    |
//      |              |->manage_5--->|
//      |              |->manage_6-------->exit()
//      |
//      |->user_1_shopping-->user_2_pay-->user_3_finish
//
// 当发生back事件时，返回上一个状态(可通过输入back来触发back事件)

// 事件示意图
//
//
//
//
//                                      |->enter_manage_1
//    |----->enter_manager              |->enter_manage_2
//    |                                 |->enter_manage_3
// [begin]                      [manage]-->enter_manage_4
//    |                                 |->enter_manage_5
//    |----->enter_user                 |->enter_manage_6
//
//  [user_1_shopping]-->user_next-->[user_2_pay]-->user_next-->[user_3_finish]

// 全局变量cart:实现购物车功能,用于在user_1_shopping和user_2_pay状态之间传递商品总金额与购买商品信息
struct shopping_cart * cart;

// 定义状态
typedef enum {
    begin,
    manage_begin,
    manage_1,
    manage_2,
    manage_3,
    manage_4,
    manage_5,
    manage_6,
    
    user_1_shopping,
    user_2_pay,
    user_3_finish
} State;

// 定义事件
typedef enum {
    back,
    stay,
    enter_manager,
    enter_manage_1,
    enter_manage_2,
    enter_manage_3,
    enter_manage_4,
    enter_manage_5,
    enter_manage_6,
    
    enter_user,
    user_next,
    back_to_begin
} Event;

// 状态转换
State transition(State currentState, Event event) {
    switch (currentState) {
        case begin:
            switch (event) {
                case enter_manager:
                    return manage_begin;
                case enter_user:
                    return user_1_shopping;
            }
        case user_1_shopping:
            switch (event) {
                case stay:
                    return currentState;
                case back:
                    return begin;
                case user_next:
                    return user_2_pay;
            }
        case user_2_pay:
            switch (event) {
                case stay:
                    return currentState;
                case back:
                    return user_1_shopping;
                case user_next:
                    return user_3_finish;
            }
        case user_3_finish:
            switch (event) {
                case back_to_begin:
                    return begin;
            }
        case manage_begin:
            switch (event) {
                case stay:
                    return currentState;
                case back:
                    return begin;
                case enter_manage_1:
                    return manage_1;
                case enter_manage_2:
                    return manage_2;
                case enter_manage_3:
                    return manage_3;
                case enter_manage_4:
                    return manage_4;
                case enter_manage_5:
                    return manage_5;
                case enter_manage_6:
                    return manage_6;
            }
        case manage_1:
        case manage_2:
        case manage_3:
        case manage_4:
            return manage_begin;
        case manage_5:
            return begin;
        case manage_6:
            break;
    }
    return currentState;
}

// 状态处理
Event handleState(State state) {
    switch (state) {
        case begin:
            divider();
            screen();
            printf("按下回车键开始购物\n(输入秘钥进入管理模式)\n");
            char judge[BUFFER_MAXIMUM_LENGTH];
            fgets(judge,sizeof (judge),stdin);
            judge[strcspn(judge, "\n")] = 0;
            if(strcmp(judge,SECRET_PASSWORD)==0){
                printf("进入管理者模式\n");
                return enter_manager;
            }
            return enter_user;
        case user_1_shopping:
            cart = shopping();
            if(cart == NULL){
                return back;
            }
            return user_next;
        case user_2_pay:
            divider();
            while (1) {
                printf("请选择:\n");
                char *choice_text_buy[] = {"1 投币购买",
                };
                for (int i = 0; i < sizeof(choice_text_buy) / sizeof(choice_text_buy[0]); i++) {
                    printf("%s\n", choice_text_buy[i]);
                }
                int choice_buy = 0;
                input_i(&choice_buy);
                if(errno==ERANGE){
                    printf("输入错误\n");
                    continue;
                }
                if (choice_buy == 0) {
                    return back;
                }

                int judge_buy;
                switch (choice_buy) {
                    case 1:
                        judge_buy = coin_buy(cart);
                        if (judge_buy == 1) {
                            return back;
                        }
                        free(cart);
                        cart = NULL;
                        return user_next;
                    default:
                        printf("选择错误,请重新选择\n");
                        continue;
                }
            }
        case user_3_finish:
            for (int i = SLEEP_SECONDS; i > 0; i--) {
                printf("%d\n",i);
                sleep(1);
            }
            return back_to_begin;
        case manage_begin:
            divider();
            while (1) {
                printf("请选择:\n");
                char *choice_text[] = {"1 添加货物",
                                       "2 删除货物",
                                       "3 查看所有商品",
                                       "4 重置数据库",
                                       "5 退出管理者模式",
                                       "6 关机"};

                for (int i = 0; i < sizeof(choice_text) / sizeof(choice_text[0]); i++) {
                    printf("%s\n", choice_text[i]);
                }
                int choice_manager = 0;
                input_i(&choice_manager);
                if(errno==ERANGE){
                    printf("输入错误\n");
                    continue;
                }
                if (choice_manager == 0) {
                    return back;
                }
                switch (choice_manager) {
                    case 1:
                        return enter_manage_1;
                    case 2:
                        return enter_manage_2;
                    case 3:
                        return enter_manage_3;
                    case 4:
                        return enter_manage_4;
                    case 5:
                        return enter_manage_5;
                    case 6:
                        exit(NORMAL);
                    default:
                        printf("选择有误,请重新选择");
                        continue;
                }
            }
        case manage_1:
            good_add();
            break;
        case manage_2:
            good_remove();
            break;
        case manage_3:
            goods_print_all();
            break;
        case manage_4:
            database_init();
            break;
        case manage_5:
            break;
        case manage_6:
            break;
    }
}

int main() {
    version();
    State currentState = begin;
    Event event;

    while (1){
        event = handleState(currentState);
        currentState = transition(currentState,event);
    }
}

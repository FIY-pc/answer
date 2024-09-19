#ifndef CANONICAL_ANSWER_LEVEL2_2_H
#define CANONICAL_ANSWER_LEVEL2_2_H

#define BACK_WORD "back"
#define END_WORD "END"

#define ADD 1
#define BUY 2
#define PAY 3
#define END 4
#define FINISH 5

typedef enum {
    type_add,
    type_buy,
    type_pay,
    type_end,
    type_finish
}Type;

typedef struct {
    //标记状态种类
    Type type;
    //goods用于存储架上商品信息 goods[a]第a个通道商品信息 {名字 单价 数量}
    int goods[5][3];
    //shopping_cart存储购物车信息 shopping_cart[a]第a条购买记录 {通道 购买数量 总金额}
    int shopping_cart[250][3];
    int receive;
}State;

typedef enum {
    event_end,
    event_back,
    event_next,
    event_stay
}Event;

void transition(State **head,State **tail,Event event);
Event handleState(State **state);

void state_init(State *state);
Event add(State *tail);
void add_to_state(char *input,State *tail);
Event buy(State *tail);
void buy_update_state(char *input,State *tail);
Event pay(State *tail);

void non_goods_check(State *tail);

#endif //CANONICAL_ANSWER_LEVEL2_2_H

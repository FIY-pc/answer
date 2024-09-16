#ifndef CANONICAL_ANSWER_DATA_H
#define CANONICAL_ANSWER_DATA_H

#include "Config.h"
#include "sqlite3.h"
#include "../Functions/goods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

void database_exists();
void database_init();
void rc_check(sqlite3 *db , int rc);

void good_update(int lane , char *name , double price , int num);
int lane_available_check(int lane);
void goods_print_all();
void goods_print_one(int lane);
void goods_fix_information_one(int lane);
void good_num_update(int lane, int num);


struct goods *return_good_one(int lane);
double return_price_one(int lane);
char *return_name_one(int lane);
int return_num_one(int lane);

void good_delete_one(int lane);
#endif //CANONICAL_ANSWER_DATA_H

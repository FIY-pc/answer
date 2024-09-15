#ifndef CANONICAL_ANSWER_CONFIG_H
#define CANONICAL_ANSWER_CONFIG_H


// Config

// Utility library
#include <errno.h>

// basic setting
#define NAME "自助售货机模拟程序"
#define WIDTH 4
#define HEIGHT 5
#define LANES WIDTH*HEIGHT

#define BACK_WORD "back"
#define FINISH_WORD "OK"

#define SECRET_PASSWORD "123456"
#define SLEEP_SECONDS 5
//data setting
#define LANE_AVAILABLE 0
#define LANE_UNAVAILABLE 1
#define BUFFER_MAXIMUM_LENGTH 256
#define GOODS_NAME_MAXIMUM_LENGTH 10

// error status setting

#define NORMAL 0
#define VALUE_ERROR (-1)
#define FILE_OPENING_ERROR 2
#define MEMORY_ALLOCATION_ERROR 3
#define DATABASE_ERROR 4

// output setting
#define DIVIDER_LENGTH 30

#endif //CANONICAL_ANSWER_CONFIG_H

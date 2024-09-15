#ifndef CANONICAL_ANSWER_IO_H
#define CANONICAL_ANSWER_IO_H

#define io_ok 0
#define io_finish (-3)
#define io_back (-1)
#define io_error (-2)

#include "Config.h"
#include <stdio.h>
#include <windows.h>
#include <float.h>
#include <string.h>

// encoding set
void setGBK();
char* utf8_to_gbk(const char* utf8_str);
// input
int input_i(int * in);
int input_f(double * in);
// output
void divider();

#endif //CANONICAL_ANSWER_IO_H
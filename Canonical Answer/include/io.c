#include "io.h"

void setGBK(){
    SetConsoleCP(936);
    SetConsoleOutputCP(936);
}

int input_i(int * in){
    setGBK();
    char input[BUFFER_MAXIMUM_LENGTH];
    char *endptr;
    long result;
    char *ret;
    ret = fgets(input,sizeof (input),stdin);
    if(ret==NULL){
        errno = ERANGE;
        printf("输入读取错误!");
        return io_error;
    }

    // 特殊标记检查
    if (strcmp(ret,BACK_WORD) == 0){
        return io_back;
    }
    if (strcmp(ret,FINISH_WORD) == 0){
        return io_finish;
    }

    input[strcspn(input,"\n")] = 0;

    // 非空检查
    if(strcmp(input,"") == 0){
        return io_error;
    }

    errno = 0;
    result = strtol(input, &endptr, 10);

    // 检查转换是否成功
    if (errno == ERANGE) {
        // 检查是否超出int范围
        if (result > INT_MAX) {
            printf("输入超出上限!\n");
        } else if (result < INT_MIN) {
            printf("输入超出下限!\n");
        }
        return io_error;
    } else if (*endptr != '\0') {
        errno = ERANGE;
        printf("有非数字字符!\n");
        return io_error;
    }

    *in = (int)result;
    return io_ok;
}

int input_f(double * in){
    setGBK();
    char input[BUFFER_MAXIMUM_LENGTH];
    char *endptr;
    double result;
    char *ret;
    ret = fgets(input,sizeof (input),stdin);
    if(ret==NULL){
        errno = ERANGE;
        printf("输入读取错误!");
        return io_error;
    }

    // 特殊标记检查
    if (strcmp(ret,BACK_WORD) == 0){
        return io_back;
    }
    if (strcmp(ret,FINISH_WORD) == 0){
        return io_finish;
    }

    input[strcspn(input,"\n")] = 0;

    errno = 0;
    result = strtod(input, &endptr);

    // 检查转换是否成功
    if (errno == ERANGE) {
        if (result == DBL_MAX || result == -DBL_MAX) {
            printf("输入超出上限!\n");
        } else if (result == 0 && input[0] != '0') {
            // 当输入非常小，以至于转换结果为0，但输入不是0时
            printf("输入太小，无法表示!\n");
        } else if (result == -0.0 && input[0] != '-') {
            // 处理负零的情况
            printf("输入为负零，但表示有误!\n");
        }
        return io_error; // 在超出范围时退出函数
    } else if (*endptr != '\0') {
        errno = ERANGE;
        printf("有非数字字符!\n");
        return io_error;
    }

    *in = result;
    return io_ok;
}

void divider(){
    for(int i = 1;i<=DIVIDER_LENGTH;i++){
        printf("-");
    }
    printf("\n");
}
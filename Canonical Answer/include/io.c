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
        printf("�����ȡ����!");
        return io_error;
    }

    // �����Ǽ��
    if (strcmp(ret,BACK_WORD) == 0){
        return io_back;
    }
    if (strcmp(ret,FINISH_WORD) == 0){
        return io_finish;
    }

    input[strcspn(input,"\n")] = 0;

    // �ǿռ��
    if(strcmp(input,"") == 0){
        return io_error;
    }

    errno = 0;
    result = strtol(input, &endptr, 10);

    // ���ת���Ƿ�ɹ�
    if (errno == ERANGE) {
        // ����Ƿ񳬳�int��Χ
        if (result > INT_MAX) {
            printf("���볬������!\n");
        } else if (result < INT_MIN) {
            printf("���볬������!\n");
        }
        return io_error;
    } else if (*endptr != '\0') {
        errno = ERANGE;
        printf("�з������ַ�!\n");
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
        printf("�����ȡ����!");
        return io_error;
    }

    // �����Ǽ��
    if (strcmp(ret,BACK_WORD) == 0){
        return io_back;
    }
    if (strcmp(ret,FINISH_WORD) == 0){
        return io_finish;
    }

    input[strcspn(input,"\n")] = 0;

    errno = 0;
    result = strtod(input, &endptr);

    // ���ת���Ƿ�ɹ�
    if (errno == ERANGE) {
        if (result == DBL_MAX || result == -DBL_MAX) {
            printf("���볬������!\n");
        } else if (result == 0 && input[0] != '0') {
            // ������ǳ�С��������ת�����Ϊ0�������벻��0ʱ
            printf("����̫С���޷���ʾ!\n");
        } else if (result == -0.0 && input[0] != '-') {
            // ����������
            printf("����Ϊ���㣬����ʾ����!\n");
        }
        return io_error; // �ڳ�����Χʱ�˳�����
    } else if (*endptr != '\0') {
        errno = ERANGE;
        printf("�з������ַ�!\n");
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
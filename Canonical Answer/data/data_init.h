#ifndef CANONICAL_ANSWER_DATA_INIT_H
#define CANONICAL_ANSWER_DATA_INIT_H

#endif //CANONICAL_ANSWER_DATA_INIT_H

#include "../Config.h"

int goods_init(){
    FILE* fp = fopen(".goods","w");
    if(fp==NULL){
        return -1;
    }



    fclose(fp);
    return 0;
}
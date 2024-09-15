#include "data.h"

// 数据库初始化函数
void database_init(){

    sqlite3 *db = NULL;
    char *err_msg = NULL;
    int rc;
    rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    // 重置
    rc = sqlite3_exec(db,"DROP TABLE IF EXISTS goods", NULL, NULL, &err_msg);
    rc_check(db,rc);

    // 建表
    const char *goods_table_create_sql = "CREATE TABLE goods  ("
                                         "id INTEGER PRIMARY KEY, "
                                         "name TEXT DEFAULT '',"
                                         "price DOUBLE DEFAULT 0.00 CHECK (price >= 0), "
                                         "num INT DEFAULT 0 CHECK (num >= 0)"
                                         ");";

    rc = sqlite3_exec(db, goods_table_create_sql , NULL, NULL, &err_msg);
    rc_check(db,rc);

    // goods表初始化
    const char *goods_table_init_sql = "INSERT INTO goods(num) VALUES (0)";
    for(int i = 1;i<=LANES;i++){
        rc = sqlite3_exec(db, goods_table_init_sql , NULL, NULL, &err_msg);
        rc_check(db,rc);
    }

    sqlite3_close(db);
    printf("数据库初始化完成\n");
}

// rc检查函数
void rc_check(sqlite3 *db , int rc){
    if (rc == SQLITE_OK || rc == SQLITE_ROW || rc == SQLITE_DONE) {
        return;
    } else{
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(DATABASE_ERROR);
    }
}

void good_update(int lane , char *name , double price , int num){
    sqlite3 *db = NULL;
    char *err_msg = NULL;
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE goods SET name = ?, price = ?, num = ? WHERE id = ?";
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db, rc);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, price);
    sqlite3_bind_int(stmt, 3, num);
    sqlite3_bind_int(stmt, 4, lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void good_num_update(int lane,int num){
    sqlite3 *db = NULL;
    char *err_msg = NULL;
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE goods SET num = ? WHERE id = ?";
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db, rc);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,num);
    sqlite3_bind_int(stmt,2,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int lane_available_check(int lane){
    sqlite3 *db = NULL;
    char *err_msg = NULL;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    char good_sql[50];
    snprintf(good_sql, sizeof(good_sql), "SELECT name FROM goods WHERE id = %d", lane);
    // 准备stmt
    rc = sqlite3_prepare_v2(db,good_sql,-1,&stmt,NULL);
    rc_check(db,rc);
    // 查询名字是否为空，若是，设置num为0
    rc = sqlite3_step(stmt);
    rc_check(db,rc);
    char *name = (char*)sqlite3_column_text(stmt,0);
    if(strcmp(name,"") == 0){
        snprintf(good_sql, sizeof(good_sql), "UPDATE goods SET num = 0 WHERE id = %d", lane);
        rc = sqlite3_exec(db,good_sql,NULL,NULL,&err_msg);
        rc_check(db,rc);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return LANE_AVAILABLE;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return LANE_UNAVAILABLE;
}

void goods_print_all(){
    setGBK();
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT id,name,price,num FROM goods";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    printf("货道\t名称\t单价\t数量\n");
    while (sqlite3_step(stmt) == SQLITE_ROW){
        struct goods *good =(struct goods *) malloc(sizeof (struct goods));
        good->lane = sqlite3_column_int(stmt,0);
        strcpy(good->name,(const char *)sqlite3_column_text(stmt,1));
        good->price = sqlite3_column_double(stmt,2);
        good->num = sqlite3_column_int(stmt,3);

        if(*good->name == '\0'){
            strcpy(good->name,"无");
        }
        printf("%d\t%s\t%.2lf\t%d\n",good->lane,good->name,good->price,good->num);
        free(good);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void goods_print_one(int lane){
    setGBK();
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT id,name,price,num FROM goods";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    struct goods *good =(struct goods *) malloc(sizeof (struct goods));
    good->lane = sqlite3_column_int(stmt,0);
    strcpy(good->name,(const char *)sqlite3_column_text(stmt,1));
    good->price = sqlite3_column_double(stmt,2);
    good->num = sqlite3_column_int(stmt,3);

    if(*good->name == '\0'){
        strcpy(good->name,"无");
    }
    printf("货道:%d 名称:%s 单价:%.2lf 数量:%d\n",good->lane,good->name,good->price,good->num);
    free(good);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void goods_fix_information_one(int lane){
    setGBK();
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT id,name,price,num FROM goods";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    struct goods *good =(struct goods *) malloc(sizeof (struct goods));
    good->lane = sqlite3_column_int(stmt,0);
    strcpy(good->name,(const char *)sqlite3_column_text(stmt,1));
    good->price = sqlite3_column_double(stmt,2);
    good->num = sqlite3_column_int(stmt,3);

    if(*good->name == '\0'){
        strcpy(good->name,"无");
    }
    printf("%d\t%s\t%.2lf",good->lane,good->name,good->price);
    free(good);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

struct goods *return_good_one(int lane){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT name,price,num FROM goods WHERE id = ?";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    struct goods *good = (struct goods *) malloc(sizeof (struct goods));
    good->lane = lane;
    strcpy(good->name,(const char *)sqlite3_column_text(stmt,0));
    good->price = sqlite3_column_double(stmt,1);
    good->num = sqlite3_column_int(stmt,2);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return good;
}

double return_price_one(int lane){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT price FROM goods WHERE id = ?";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    double price = sqlite3_column_double(stmt,0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return price;
}

char *return_name_one(int lane){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT name FROM goods WHERE id = ?";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    char *name = (char *)sqlite3_column_text(stmt,0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return name;
}

int return_num_one(int lane){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "SELECT num FROM goods WHERE id = ?";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    int num = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return num;
}


void good_delete_one(int lane){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = NULL;
    int rc = sqlite3_open("../data/database.db", &db);
    rc_check(db,rc);

    const char *goods_select_sql = "UPDATE goods SET name = '', price = 0.00, num = 0 WHERE id = ?";

    rc = sqlite3_prepare_v2(db, goods_select_sql, -1, &stmt, NULL);
    rc_check(db, rc);

    sqlite3_bind_int(stmt,1,lane);

    rc = sqlite3_step(stmt);
    rc_check(db,rc);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    printf("成功删除货道 %d 上的商品\n",lane);
}
#include "db_handler.hpp"
#include <mysql.h>
#include <string>
#include <iostream>

DBHandler::DBHandler(std::string user, std::string passwd, std::string db_name){
    con = mysql_init(NULL);
    if (con == NULL)
        fprintf(stderr, "%s\n", mysql_error(con));
    if (mysql_real_connect(con, DB_ADDR, user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL)
        finishWithError();
}

DBHandler::~DBHandler(){
    mysql_close(con);
}

void DBHandler::finishWithError(){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
}

void DBHandler::writeToDB(char* query){
    if (mysql_query(con, query)) {
        finishWithError();
    }
}

void DBHandler::readFromDB(char* query, MYSQL_RES** res){
    if (mysql_query(con, query)) {
        finishWithError();
    }
    *res = mysql_store_result(con);
    if (res == NULL)
        std::cout << "Yayay!\n";
}

#include "db_handler.hpp"
#include <mysql.h>
#include <string>

DBHandler::DBHandler(std::string user, std::string passwd, std::string db_name){
    con = mysql_init(NULL);
    if (con == NULL)
        fprintf(stderr, "%s\n", mysql_error(con));
    if (mysql_real_connect(con, DB_ADDR, user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL)
        finishWithError();
}

void DBHandler::finishWithError(){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
}

void DBHandler::queryDB(char* query){
    if (mysql_query(con, query)) {
        finishWithError();
    }
}

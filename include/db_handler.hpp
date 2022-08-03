#ifndef _DB_HANDLER_
#define _DB_HANDLER_

#include <string>
#include <mysql.h>

#define DB_ADDR "localhost"

class DBHandler{
private:
    MYSQL* con;

public:
    DBHandler(std::string user, std::string passwd, std::string db_name);
    ~DBHandler();
    void finishWithError();
    void writeToDB(char* query);
    void readFromDB(char* query, MYSQL_RES** res);
};

#endif // _DB_HANDLER_
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
    void finishWithError();
    void queryDB(char* query);
};

#endif // _DB_HANDLER_
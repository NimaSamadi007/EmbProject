#ifndef _GEN_HTML_HPP_
#define _GEN_HTML_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "db_handler.hpp"

class genHTML{
public:
    static bool generate(std::string table_type, int n);
};

#endif // _GEN_HTML_HPP_
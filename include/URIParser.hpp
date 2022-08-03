#ifndef __URI_PARSER_HPP_
#define __URI_PARSER_HPP_

#include <vector>
#include <string>

class URIParser {
private:
    std::string path;
    std::vector<std::string> keys;
    std::vector<std::string> values;    
public:
    URIParser(std::string uri);
    std::string getValue(std::string key);
    std::string getPath();
};

#endif // __URI_PARSER_HPP_

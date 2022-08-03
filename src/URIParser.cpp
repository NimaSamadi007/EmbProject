#include "URIParser.hpp"
#include <string>
#include <vector>
#include <iostream>

URIParser::URIParser(std::string uri) {
    int i = uri.find("?");    
    path = uri.substr(0, i);
    std::string query = uri.substr(i+1);
    while(query.find("&") != std::string::npos) { // there is more than 1 parameter
        int j = query.find("&");
        std::string current_param = query.substr(0, j);
        query = query.substr(j+1);
        keys.push_back(current_param.substr(0, current_param.find("=")));
        values.push_back(current_param.substr(current_param.find("=")+1));
    }
    // there is only 1 parameter
    keys.push_back(query.substr(0, query.find("=")));
    values.push_back(query.substr(query.find("=")+1));
}

std::string URIParser::getValue(std::string key) {
    for(int i = 0; i < keys.size(); i++)
        if(keys[i] == key)
            return values[i];
    return "";
}

std::string URIParser::getPath() {
    return path;
}


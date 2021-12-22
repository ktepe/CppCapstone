  
#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <jsoncpp/json/json.h>
#include <string>
#include <vector>
#include "util.hpp"
#include <iostream>

class Json_Parser:
{
      public:
       
       std::string to_string(Json::Value &value);
       void get(std::string req_string);



      private:
        Json::Value _value;
}

#endif //
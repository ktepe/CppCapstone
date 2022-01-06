  
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>

class Json_Parser
{
      public:
       Json_Parser();
       std::string to_string(Json::Value &value);
       void parse(std::string req_string);
       Json::Value get() {return _value;};
       std::string get_string();
      private:
        Json::Value _value;
};

#endif // JSON_PARSER_H

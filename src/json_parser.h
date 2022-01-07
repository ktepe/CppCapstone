  
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <jsoncpp/json/json.h>
#include <string>
#include <iostream>
#include "info_line.h"

class Json_Parser
{
      public:
       Json_Parser();
       std::string to_string(Json::Value &value);
       void parse_req(std::string req_string);
       Json::Value get() {return _value;};
       std::string get_string();
       std::string get_reply(std::string req_string);
      private:
        Json::Value _value;
        Info_Line _info_line;
};

#endif // JSON_PARSER_H

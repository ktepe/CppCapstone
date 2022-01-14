  
#include "json_parser.h"
#include "handler.h"
#include "utils.h"
#include "dbase.h"

#define DBG 0

Json_Parser::Json_Parser()
{
    Json::Value _value;
    Info_Line _info_line;
}

std::string Json_Parser::get_string()
{
   Json::FastWriter fastWriter;
   return(fastWriter.write(_value));
}

std::string Json_Parser::to_string(Json::Value &value)
{
    Json::FastWriter fastWriter;
    return fastWriter.write(value);
}

void Json_Parser::parse_req(std::string req_string)
{   
    auto arr2=Utils::split(req_string,"&");
    
    auto v1 = Utils::split(arr2[1], "=");
    auto v2 = Utils::split(arr2[2], "=");
    auto v3 = Utils::split(arr2[3], "=");

    // Json::Value data1;
    _value[v1[0]]= v1[1];
    _value[v2[0]]= v2[1];
    _value[v3[0]]= v3[1];

#if DBG
    std::cout << " v1's "<< v1[0] << " "<<v1[1]<< " "<< _value["make"] << std::endl;
    std::cout << " v2's "<< v2[0] << " "<<v2[1]<< " "<< _value["length"] << std::endl;
    std::cout << " v3's "<< v3[0] << " "<<v3[1]<< " "<< _value["year"] << std::endl;
#endif

    _info_line.make = _value.get("make", "Jenneau").asString();
    _info_line.length = std::stoi(_value.get("length", "40").asString());
    _info_line.year = std::stoi(_value.get("year", "1990").asString());
    
#if DBG
    std::cout << "in parse req make "<< _info_line.make << std::endl;
    std::cout << "in parse req length "<< _info_line.length << std::endl;
    std::cout << "in parse req year "<< _info_line.year << std::endl;
#endif

}


std::string Json_Parser::get_reply(std::string req_string)
{   
    parse_req(req_string);

    Dbase db;

    _value["price"]=std::to_string(db.run_db(_info_line));

    std::cout << " get_reply "<< _value["price"] << std::endl;

    return to_string(_value);
}

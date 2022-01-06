  
#include "json_parser.h"
#include "handler.h"
#include "utils.h"

Json_Parser::Json_Parser()
{
    Json::Value _value;
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

void Json_Parser::parse(std::string req_string)
{

    //auto arr=util::split(req_string,"?");
    //for(size_t i=0;i<arr.size();i++)
    //ucout << arr[i] << std::endl;
    //printf("%s\n",arr[i].c_str());
    
    auto arr2=Utils::split(req_string,"&");
    for(size_t i=0;i<arr2.size();i++)
    std::cout << arr2[i] << std::endl;

    std::cout << "size of arr2 :"<<arr2.size() << std::endl;
    
    auto v1 = Utils::split(arr2[1], "=");
    //std::cout << " v1's "<< v1[0] << " "<<v1[1]<< std::endl;

    auto v2 = Utils::split(arr2[2], "=");
    //std::cout << " v2's "<< v2[0] << " "<<v2[1]<< std::endl;

    auto v3 = Utils::split(arr2[3], "=");
    //std::cout << " v3's "<< v3[0] << " "<<v3[1]<< std::endl;

    //Json::Value data1;
    _value[v1[0]]= v1[1];
    _value[v2[0]]= v2[1];
    _value[v3[0]]= v3[1];
    //_value["price"] = "40000";
    
 //std::cout << "json out " << a << std::endl;
}



  
#include "json_parser.h"

Json_Parser::Json_Parser()
{
    Json::Value _value;
}

std::vector<std::string> Json_Parser::split(std::string str, std::string sep)
{
        char* cstr=const_cast<char*>(str.c_str());
        char* current;
        std::vector<std::string> arr;
        current=strtok(cstr,sep.c_str());
        while(current!=NULL)
        {
            //arr.push_back(current);
            arr.emplace_back(current);
            current=strtok(NULL,sep.c_str());
        }
            
        return arr;
}

//Json::Value get() {return _value;};

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
    
    auto arr2=split(req_string,"&");
    for(size_t i=0;i<arr2.size();i++)
    std::cout << arr2[i] << std::endl;

    std::cout << "size of arr2 :"<<arr2.size() << std::endl;
    
    auto v1 = split(arr2[1], "=");
    //std::cout << " v1's "<< v1[0] << " "<<v1[1]<< std::endl;

    auto v2 = split(arr2[2], "=");
    //std::cout << " v2's "<< v2[0] << " "<<v2[1]<< std::endl;

    auto v3 = split(arr2[3], "=");
    //std::cout << " v3's "<< v3[0] << " "<<v3[1]<< std::endl;



    //Json::Value data1;
    _value[v1[0]]= v1[1];
    _value[v2[0]]= v2[1];
    _value[v3[0]]= v3[1];
    //_value["price"] = "40000";
    
 //std::cout << "json out " << a << std::endl;
}



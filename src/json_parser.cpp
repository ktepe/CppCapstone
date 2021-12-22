  
#include "json_parser.h"

std::string Json_Parcer::to_string(Json::Value &value)
{
    Json::FastWriter fastWriter;
    return fastWriter.write(data1);

}

void Json_Parcer::get(std::string req_string)
{


}


    auto arr=util::split(path1,"?");
    for(size_t i=0;i<arr.size();i++)
        ucout << arr[i] << std::endl;
        //printf("%s\n",arr[i].c_str());
    auto arr2=util::split(path1,"&");
    for(size_t i=0;i<arr2.size();i++)
        ucout << arr2[i] << std::endl;

    ucout << "size of arr2 :"<<arr2.size() << std::endl;
    
    auto v1 = util::split(arr2[1], "=");
    std::cout << " v1's "<< v1[0] << " "<<v1[1]<< std::endl;

    auto v2 = util::split(arr2[2], "=");
    std::cout << " v2's "<< v2[0] << " "<<v2[1]<< std::endl;

    auto v3 = util::split(arr2[3], "=");
    std::cout << " v3's "<< v3[0] << " "<<v3[1]<< std::endl;



    Json::Value data1;
    data1[v1[0]]= v1[1];
    data1[v2[0]]= v2[1];
    data1[v3[0]]= v3[1];
    data1["price"] = "40000";
    


    std::cout << "json out " << a << std::endl;



#endif //
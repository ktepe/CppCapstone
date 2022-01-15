#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <string>
//
#include <jsoncpp/json/json.h>
#include "info_line.h"

//using namespace std;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

#define DBG 1

Info_Line enter_req()
{
    int len, year;
    Info_Line _line;
    std::string m;
    
    do {
        std::cout<<"Enter Maker of the sailboat 'ben' for Beneteau and 'jen' for Jenneau: ";
        std::cin>>m;
        if (m == "ben") 
            m = "Beneteau";
        else if (m == "jen")
            m ="Jeanneau";
        else
		    m = "invalid";
	
    } while (m == "invalid");

  do {  
  	std::cout<<"Enter Lenght of the sailboat in feet (40-50): ";
  	std::cin>>len;

	} while (!(len > 39 && len < 51));

  do {  
      std::cout<<"Enter Year that the sailboat was built 1980-2020: ";
      std::cin>>year;

	} while (!(year >= 1980 && year <=2021));

  _line.make = m;
  _line.length = len;
  _line.year = year;

  return _line;
}

//int _client(int argc, char* argv[])
int _client(Info_Line _input)
{
    auto fileStream = std::make_shared<ostream>();
    std::string length, year, make;

    make = _input.make;
    length = std::to_string(_input.length);
    year = std::to_string(_input.year);

    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;
        // get the ip address of the server
        http_client client(U("http://127.0.0.1:8080"));

        // Build request URI and start the request.

        uri_builder builder(U("/search"));
        builder.append_query(U("&make="+make+"&year="+year+"&length="+length+"&"));
        std::cout << "builder to string: " << builder.to_string() << std::endl;
        return client.request(methods::GET, builder.to_string());
        
    })
    // Handle response headers arriving.
    .then([=](http_response response)
    {
#if DBG
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        std::cout << "responce body " << response.body() << std::endl;
        std::cout << "responce string " << response.to_string() << std::endl;
        std::cout << "responce lenght " << response.to_string().length() << std::endl;
#endif   

        Json::Value data1;
        Json::Reader reader;
        
        stringstreambuf buffer;
        response.body().read_to_end(buffer).get();
        printf("Response body: \n %s", buffer.collection().c_str());

        auto t=buffer.collection().c_str();
        bool parsingSuccessful = reader.parse(t, data1);
        if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }

        Json::FastWriter fastWriter;
        std::cout << "Returned JSON string: "<< fastWriter.write(data1) << std::endl;
        auto pr = std::stoi(data1.get("price", "0").asString());
        if (pr != 0)
        {
            std::cout << "Price: "<< pr << std::endl;
        }
        else
        {
            std::cout << "No data found for this boat " << std::endl;
        }

        return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

    return 0;
}

int main(int argc, char* argv[])
{ 
   
   std::string select;

   do {
        
       auto ben = enter_req();
       // Info_Line ben("Beneteau", 50, 1999);
       std::cout<<"In main:: You entered "<<ben.make<< " "<< ben.length << " ft.  "<< ben.year <<" model" <<std::endl;
 
       _client(ben);
       
       std::cout<< std::endl << "Press Q to quit " << std::endl;
       std::cout<< std::endl << "Press Any other key to continue " << std::endl;
       
       std::cin>>select;

   }while(!(select == "q" || select == "Q") );
   
   std::cout<<"Client Quited" << std::endl;
    
   return 0;
}
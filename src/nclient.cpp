#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <string>
//
#include <jsoncpp/json/json.h>
#//include "utils.h"
//using namespace std;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


int client(int argc, char* argv[])
{
    auto fileStream = std::make_shared<ostream>();
    std::string data2 = "hh";
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;
        // get the ip address of the server
        http_client client(U("http://127.0.0.1:8080"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        builder.append_query(U("&make=Ben&year=2000&leng=40&"));
        std::cout << "builder to string: " << builder.to_string() << std::endl;
        return client.request(methods::GET, builder.to_string());
        
    })
    // Handle response headers arriving.
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        std::cout << "responce body " << response.body() << std::endl;
        std::cout << "responce string " << response.to_string() << std::endl;
        std::cout << "responce lenght " << response.to_string().length() << std::endl;
        

        //auto t = response.extract_json();
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
        std::cout << "json data "<< fastWriter.write(data1) << std::endl;
        std::cout << "json data[]len "<< data1["leng"] << std::endl;



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
    auto fileStream = std::make_shared<ostream>();
    std::string data2 = "hh";
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // Create http_client to send the request.
        //http_client client(U("http://www.google.com/"));
        //http_client client(U("http://www.bing.com/"));
        http_client client(U("http://127.0.0.1:8080"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        //uri_builder builder(U("index.html"));
        //uri_builder builder(U(""));
        //uri_builder builder(U("%7B%22make%22%3A%20%22ben%22%2C%20%22year%22%3A%202020%2C%20%22lenght%22%3A%2040%20%7D"));
        //std::string data1 = "{'make': 'ben', 'model': '40', 'year': '2010' }";
        //builder.append_query(U("q"), U("cpprestsdk github"));
        //builder.append_query(U("q"), U("benneteau 40 oceanis"));
        //builder.append_query(U("make=Ben&year=2000&leng=40"));
        builder.append_query(U("&make=Ben&year=2000&leng=40&"));
        std::cout << "builder to string: " << builder.to_string() << std::endl;
        return client.request(methods::GET, builder.to_string());
        //return client.request(methods::GET, data1);
        
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        std::cout << "responce body " << response.body() << std::endl;
        std::cout << "responce string " << response.to_string() << std::endl;
        std::cout << "responce lenght " << response.to_string().length() << std::endl;
        

        //auto t = response.extract_json();
        Json::Value data1;
        Json::Reader reader;
        /*
        //bool parsingSuccessful = reader.parse(t, data1);
        //if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }
        */
        
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
        std::cout << "json data "<< fastWriter.write(data1) << std::endl;
        std::cout << "json data[]len "<< data1["leng"] << std::endl;



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
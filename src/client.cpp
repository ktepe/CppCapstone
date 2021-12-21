//g++ -o client client.cpp -lcpprest -lpthread -lcrypto -lboost_system
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

#include <iostream>
using namespace std;

void make_request( http_client & client, method mtd )
{
	//client.request(mtd, "/restdemo").then([](http_response response)
    client.request(mtd, "").then([](http_response response)

			{
				cout << __LINE__<<" here in get request \n";
				if (response.status_code() == status_codes::OK)
				{
					cout << __LINE__<<" here in get request \n";
					cout << "this is body "<< response.body().read_to_end() << endl;
				}
				else
				{
					cout << __LINE__<<" here in get request \n";
				}
				return pplx::task_from_result(json::value());
			}).then([](pplx::task<json::value> previousTask)
				{
				}).wait();

}


void make_request2( http_client & client, method mtd )
{
	//client.request(mtd, "/restdemo").then([](http_response response)
    client.request(mtd, "").then([](http_response response)

			{
				cout << __LINE__<<" here in get request \n";
				if (response.status_code() == status_codes::OK)
				{
					cout << __LINE__<<" here in get request \n";
					cout << "this is body "<<response.body() << endl;
				}
				else
				{
					cout << __LINE__<<" here in get request \n";
				}
				
			}).wait();

}

int main()
{
	http_client client( "http://0.0.0.0:8080" );
    //http_client client( "http://localhost" );
	make_request2( client, methods::GET );
	return 0;
}
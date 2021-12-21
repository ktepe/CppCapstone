//g++ -o server server.cpp -lcpprest -lpthread -lcrypto -lboost_system
#include <cpprest/http_listener.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
using namespace std;

void handle_get(http_request request)
{
	cout << __LINE__<<" here in get request \n";
	request.reply(status_codes::OK, "GET Method result ");
}

int main()
{
   http_listener listener("http://localhost/restdemo");

   listener.support(methods::GET,  handle_get);
   try
   {
      listener
         .open()
         .then([&listener]() { cout<<"\nstarting to listen\n"; })
         .wait();

      while (true);
   }
   catch (exception const & e)
   {
      cout << e.what() << endl;
   }

   return 0;
}
#include "handler.h"
#include <jsoncpp/json/json.h>

handler::handler()
{
    //ctor
}
handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

}
handler::~handler()
{
    //dtor
}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{
    ucout << " handler message: " << message.to_string() << endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    ucout << "path " << message.relative_uri().to_string() << std::endl;
    std::string path1 = message.relative_uri().to_string();
    ucout << "path data string" << message.relative_uri().to_string() << std::endl;
    auto arr=split(path1,"?");
    for(size_t i=0;i<arr.size();i++)
        ucout << arr[i] << std::endl;
        //printf("%s\n",arr[i].c_str());
    auto arr2=split(path1,"&");
    for(size_t i=0;i<arr2.size();i++)
        ucout << arr2[i] << std::endl;

    ucout << "size of arr2 :"<<arr2.size() << std::endl;
    
    auto v1 = split(arr2[1], "=");
    std::cout << " v1's "<< v1[0] << " "<<v1[1]<< std::endl;

    auto v2 = split(arr2[2], "=");
    std::cout << " v2's "<< v2[0] << " "<<v2[1]<< std::endl;

    auto v3 = split(arr2[3], "=");
    std::cout << " v3's "<< v3[0] << " "<<v3[1]<< std::endl;



    Json::Value data1;
    data1[v1[0]]= v1[1];
    data1[v2[0]]= v2[1];
    data1[v3[0]]= v3[1];
    data1["price"] = "40000";
    Json::FastWriter fastWriter;
    std::string a = fastWriter.write(data1);



    std::cout << "json out " << a << std::endl;

    //if request is legit read the database file and return the price

	//Dbms* d  = new Dbms();
    //d->connect();
    //ucout<< " concurrency "<< (concurrency::streams::fstream:: open_istream(U("."+message.relative_uri().path()),std::ios::in).get() )<< std::endl;  
    concurrency::streams::fstream::open_istream(U("../data/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
    // concurrency::streams::fstream::open_istream(U("."+message.relative_uri().path()), std::ios::in).then([=](concurrency::streams::istream is)
    {
        
        message.reply(status_codes::OK, U(a), U("application/json"))
        //message.reply(status_codes::OK, is,  U("text/htmls"))
		.then([](pplx::task<void> t)
		{
			try{
                ucout << " handler message in the get: " << std::endl << std::endl;
				t.get();
                
			}
			catch(...){
				//
			}
	});
    }).then([=](pplx::task<void>t)
	{
		try{
			t.get();
		}
		catch(...){
			message.reply(status_codes::InternalError,U("INTERNAL ERROR "));
		}
	});
    return;

};

/*
void handler::handle_get(http_request message)
{
    ucout << " handler message: " << message.to_string() << endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    ucout << "path " << message.relative_uri().to_string() << std::endl;
    std::string path1 = message.relative_uri().to_string();
    ucout << "path data string" << message.relative_uri().to_string() << std::endl;
    auto arr=split(path1,"?");
    for(size_t i=0;i<arr.size();i++)
        ucout << arr[i] << std::endl;
        //printf("%s\n",arr[i].c_str());
    auto arr2=split(path1,"&");
    for(size_t i=0;i<arr2.size();i++)
        ucout << arr2[i] << std::endl;

    ucout << "size of arr2 :"<<arr2.size() << std::endl;
    
    auto v1 = split(arr2[1], "=");
    std::cout << " v1's "<< v1[0] << " "<<v1[1]<< std::endl;

    auto v2 = split(arr2[2], "=");
    std::cout << " v2's "<< v2[0] << " "<<v2[1]<< std::endl;

    auto v3 = split(arr2[3], "=");
    std::cout << " v3's "<< v3[0] << " "<<v3[1]<< std::endl;

    Json::Value data1;
    data1[v1[0]]= v1[1];
    data1[v2[0]]= v2[1];
    data1[v3[0]]= v3[1];

    Json::FastWriter fastWriter;
    std::string a= fastWriter.write(data1);

    std::cout << "json out " << a << std::endl;
	//Dbms* d  = new Dbms();
    //d->connect();
    //ucout<< " concurrency "<< (concurrency::streams::fstream:: open_istream(U("."+message.relative_uri().path()),std::ios::in).get() )<< std::endl;  

    concurrency::streams::fstream::open_istream(U("./index.html"), std::ios::in).then([=](concurrency::streams::istream is)
    //concurrency::streams::fstream::open_istream(U("."+message.relative_uri().path()), std::ios::in).then([=](concurrency::streams::istream is)
    {
        
        message.reply(status_codes::OK, U("text/htmls"), U(a))
        //message.reply(status_codes::OK, is,  U("text/htmls"))
		.then([](pplx::task<void> t)
		{
			try{
                ucout << " handler message in the get: " << std::endl << std::endl;
				t.get();
                
			}
			catch(...){
				//
			}
	});
    }).then([=](pplx::task<void>t)
	{
		try{
			t.get();
		}
		catch(...){
			message.reply(status_codes::InternalError,U("INTERNAL ERROR "));
		}
	});

    return;

};
*/
//
// A POST request
//
void handler::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;


     message.reply(status_codes::OK,message.to_string());
    return ;
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
     ucout <<  message.to_string() << endl;

        string rep = U("WRITE YOUR OWN DELETE OPERATION");
      message.reply(status_codes::OK,rep);
    return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
    ucout <<  message.to_string() << endl;
     string rep = U("WRITE YOUR OWN PUT OPERATION");
     message.reply(status_codes::OK,rep);
    return;
};

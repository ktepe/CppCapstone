#include "handler.h"
#include "json_parser.h"

Handler::Handler()
{
    //ctor
}
Handler::Handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&Handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&Handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&Handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&Handler::handle_delete, this, std::placeholders::_1));

}
Handler::~Handler()
{
    //dtor
}

void Handler::handle_error(pplx::task<void>& t)
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
void Handler::handle_get(http_request message)
{
    ucout << " handler message: " << message.to_string() << std::endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    ucout << "path " << message.relative_uri().to_string() << std::endl;
    std::string path1 = message.relative_uri().to_string();
    ucout << "path data string" << message.relative_uri().to_string() << std::endl;
    
    concurrency::streams::fstream::open_istream(U("../data/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
    // concurrency::streams::fstream::open_istream(U("."+message.relative_uri().path()), std::ios::in).then([=](concurrency::streams::istream is)
    {
        Json_Parser json_obj;
        std::string json_valstr = json_obj.get_reply(path1);
        //json_obj.get_string();

        std::cout << "handle get reply "<< json_valstr << std::endl;

        message.reply(status_codes::OK, U(json_valstr), U("application/json"))
        //message.reply(status_codes::OK, is,  U("text/htmls"))
		.then([](pplx::task<void> t)
		{
			try{
                //ucout << " handler message in the get: "  << std::endl;
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

// A POST request
//
void Handler::handle_post(http_request message)
{
    ucout <<  message.to_string() << std::endl;


     message.reply(status_codes::OK,message.to_string());
    return ;
};

//
// A DELETE request
//
void Handler::handle_delete(http_request message)
{
     ucout <<  message.to_string() << std::endl;

        std::string rep = U("WRITE YOUR OWN DELETE OPERATION");
      message.reply(status_codes::OK,rep);
    return;
};


//
// A PUT request 
//
void Handler::handle_put(http_request message)
{
    ucout <<  message.to_string() <<std::endl;
     std::string rep = U("WRITE YOUR OWN PUT OPERATION");
     message.reply(status_codes::OK,rep);
    return;
};

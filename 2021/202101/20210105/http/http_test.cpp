#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>

#include "httplib.h"


void http_back_func(const httplib::Request& requ,httplib::Response& resp)
{
    (void) requ;
    std::string str = "<html><h1>linux-84</h1></html>";
    resp.set_content(str.c_str(),str.size(),"text/html");
    
}

int main()
{
    httplib::Server svr;
    svr.Get("/aa",http_back_func);
    svr.listen("0.0.0.0",16666);
    
    return 0;
}

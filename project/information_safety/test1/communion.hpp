#pragma  once
#include <string.h>
#include <string>
const size_t NICK_NAME_LENGH = 20;
enum Type 
{
    LOGIN = 1,
    REGISTER
};
struct User_info
{
    User_info() = default;
    User_info(std::string nick_name, int passwd, int type)
    {
        passwd_ = passwd;
        type_ = type;
        strcpy(nick_name_, nick_name.c_str());
    }
    char nick_name_[NICK_NAME_LENGH];
    int passwd_;
    int type_ = -1;
};

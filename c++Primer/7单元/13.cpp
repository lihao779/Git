#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

struct People
{
    std::string name;
    std::vector<std::string> phone;
};

int main()
{
    std::string line;
    std::vector<People> vec;
    while(getline(std::cin,line))
    {
        std::istringstream istr;
        istr.str(line);
        People p;
        istr >> p.name;
        std::string word;
        while(istr >> word)
        {
            p.phone.push_back(word);
        }
        vec.push_back(p);
        istr.str("");
        for(size_t i = 0;i < vec.size();i++)
        {
            std::cout << "name:" <<vec[i].name << " phone:";
            for(size_t j = 0;j < vec[i].phone.size();j++)
            {
                std::cout << vec[i].phone[j] << " ";
            }
            std::cout << std::endl;
        }
        break;
    }
    for(auto& entry : vec)
    {
        std::ostringstream ostrtrue,ostrfalse;
        for(auto& e : entry.phone)
        {
            if(e.size() ==  11)
                ostrtrue << e << " ";
            else
                ostrfalse << e << " ";
        }
        if(ostrfalse.str().empty())
        {
            std::cout << entry.name << " " << ostrtrue.str() << std::endl;
        }
        else
        {
            std::cout << "输入号码错误" <<std::endl;
            std::cout << entry.name << " " << ostrfalse.str() << std::endl;
        }
    }
    return 0;
}

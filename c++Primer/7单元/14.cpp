#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct People
{
    std::string name;
    std::vector<std::string> phone;
};

int main()
{
    std::vector<People> vec;
    std::ifstream ifs;
    ifs.open("test.txt");
    if(ifs)
    {
        std::string line;
        while(getline(ifs,line))
        {
            People people;
            std::istringstream istr; 
            istr.str(line);
            istr >> people.name;
            std::string temp;
            while(istr >> temp)
            {
                people.phone.push_back(temp);
            }
            vec.push_back(people);
        }
    }
    else
    {
        std::cerr << "test.txt open failed" << std::endl;
    }
    ifs.close();

    for(size_t i = 0;i < vec.size();i++)
    {
        std::cout << "name:" << vec[i].name << " phone:" ;
        for(size_t j = 0;j < vec[i].phone.size();j++)
        {
            std::cout << vec[i].phone[j] << " ";
        }
        std::cout << std::endl;
    }
    //判断电话号码正确性
    for(size_t i = 0;i < vec.size();i++)
    {
        std::string badnum,goodnum;
        for(size_t j = 0;j < vec[i].phone.size();j++)
        {
            if(vec[i].phone[j].size() != 11)
            {
                //错误
                badnum += vec[i].phone[j];
                badnum += " ";
            }
            else 
            {
                //正确
                goodnum += vec[i].phone[j];
                goodnum += " ";
            }
        }
        if(badnum.size() == 0)
        {
            std::cout << "信息正确" << std::endl;
            std::cout << "name:" << vec[i].name <<" phone:" << goodnum << std::endl;
        }
        else
        {
            std::cout << "信息错误" << std::endl;
            std::cout << "name:" << vec[i].name <<" bad-phone:" << badnum <<" good-phone:" << goodnum << std::endl;
        }
    }
    return 0;
}

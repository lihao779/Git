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
        std::istringstream istr; 
        People people;
        while(getline(ifs,line))
        {
            istr.str(line);
            istr >> people.name;
            std::string temp;
            while(istr >> temp)
            {
                people.phone.push_back(temp);
            }
        }
        vec.push_back(people);
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
    return 0;
}

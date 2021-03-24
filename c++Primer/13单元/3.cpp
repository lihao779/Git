#include <string>

using namespace std;

class Employee
{
    private:
        static int ns;

    public:
        Employee()
            :number_(ns++)
        {}
        Employee(const string& name)
            :name_(name)
             ,number_(ns++)
        {}
        
        Employee(const Employee& e)
            :name_(e.name_)
             ,number_(ns++)
        {}

        Employee& operator=(const Employee& e)
        {
            if(this != &e)
            {
                name_ = e.name_;
                number_ = ns++;
            }
            return *this;
        }
    private:
        string name_;
        size_t number_;
};  
int Employee::ns = 1;


int main()
{
    return 0;
}

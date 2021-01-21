#include <string>

struct Sales_date
{
    std::string isbn()const
    {
        return ISBN;
    }
    Sales_date& combine(const Sales_date&);
    std::string ISBN;
    unsigned units_sold;
    double revenue;
};
Sales_date& Sales_date::combine(const Sales_date& date)
{
    units_sold += date.units_sold;
    revenue += date.revenue;
    return *this;
}

struct Person
{
    std::string Name()const
    {
        return _name;
    }
    std::string Addr()const
    {
        return _addr;
    }
    std::string _name;
    std::string _addr;
};

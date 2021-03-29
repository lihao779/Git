#include <string>

class Sale_date
{
    friend std::ostream& operator<<(std::ostream&, const Sale_date&);
    friend std::istream& operator>>(std::istream&, Sale_date&);
    friend Sale_date operator+(const Sale_date& s1,const Sale_date& s2);
    friend bool operator==(const Sale_date& s1, const Sale_date& s2);
    friend bool operator!=(const Sale_date& s1, const Sale_date& s2);
    friend bool operator<(const Sale_date& s1, const Sale_date& s2);
    friend bool operator>(const Sale_date& s1, const Sale_date& s2);
    public:
        Sale_date(std::string s = "") :ISBN(s) {}
        Sale_date(const Sale_date& s) :ISBN(s.ISBN) {}
        Sale_date& operator=(const Sale_date& s)
        {
            if(this != &s)
            {
                ISBN = s.ISBN;
            }
            return *this;
        }
        ~Sale_date(){}
    
    Sale_date& operator+=(const Sale_date& s);
    private:
        std::string ISBN;
};

std::ostream& operator<<(std::ostream& os, const Sale_date& s)
{
    os << s.ISBN;
    return os;
}

std::istream& operator>>(std::istream& is, Sale_date& s)
{
    is >> s.ISBN;
    return is;
}

Sale_date operator+(const Sale_date& s1,const Sale_date& s2)
{
    //std::string temp = s1.ISBN;
    //temp += s2.ISBN;
    //return Sale_date(temp);
    Sale_date temp = s1;
    temp += s2;
    return temp;
}

Sale_date& Sale_date::operator+=(const Sale_date& s)
{
    ISBN += s.ISBN;
    return *this;
}

bool operator==(const Sale_date& s1, const Sale_date& s2)
{
    return s1.ISBN == s2.ISBN;
}
 
bool operator!=(const Sale_date& s1, const Sale_date& s2)
{
    return !(s1 == s2);
}

bool operator<(const Sale_date& s1, const Sale_date& s2)
{
    return s1.ISBN < s2.ISBN;
}

bool operator>(const Sale_date& s1, const Sale_date& s2)
{
    return s1.ISBN > s2.ISBN;
}

#include <algorithm>
#include <string>
#include <iostream>
class Quote
{
    public:
        Quote() = default;
        Quote(std::string bookname, double p) : price(p), ISBN(bookname){}
        Quote(const Quote& q):price(q.price), ISBN(q.ISBN){}
        Quote(Quote&& q): price(q.price), ISBN(q.ISBN){}
        Quote& operator=( const Quote& q)
        {
            if(&q != this)
            {
                price = q.price;
                ISBN = q.ISBN;
            }
            return *this;
        }

        std::string Getname()
        {
            return ISBN;
        }
        virtual double net_price(size_t n)const
        {
            return n * price; 
        }
    
        virtual ~Quote(){}
        
        virtual void debug()
        {
            std::cout << "book_nake:" <<ISBN << " " << "book_price:" << price << std::endl;
        }
        std::string GetBookname()
        {
            return ISBN;
        }
    protected:
        double price;
    private:
        std::string ISBN;
};

class Bluck_Quote : public Quote
{
    using Quote::Quote;
    public:
        Bluck_Quote() = default;
        Bluck_Quote(std::string bookname, double book_price, size_t min_book_, double dis)
            :Quote(bookname, book_price), min_book_num(min_book_), discount(dis)
        {}
        Bluck_Quote(const Bluck_Quote& b)
            :Quote(b)
        {
            min_book_num = b.min_book_num;
            discount = b.discount;
        }
        Bluck_Quote& operator=(const Bluck_Quote& b)
        {
            if(&b != this)
            {
                Quote::operator=(b);
                min_book_num = b.min_book_num;
                discount = b.discount;
            }
            return *this;
        }
        
        virtual double net_price(size_t n)const override
        {
            if(n >= min_book_num)
                return n * price * discount;
            else 
                return n * price;
        }
        virtual void debug() override
        {
            std::cout << "book_name:" << Getname() << " " << "book_price:" << price << " " << "min_book_num:" << min_book_num << " "
                << "discount:" << discount << std::endl;
        }
    private:
        size_t min_book_num;
        double discount;

};

class Quote_Max: public Quote
{
    public:
        Quote_Max() = default;
        Quote_Max(std::string book_name, double book_price, size_t max_count, double discount)
            :Quote(book_name, book_price), max_count_(max_count), discount_(discount)
        {}

        virtual double net_price(size_t n)const override
        {
            if(n <= max_count_)
                return n * price * discount_;
            else
                return n * price;
        }
        virtual void debug() override
        {
            std::cout << "book_name:" << Getname() << " " << "book_price:" << price << " " << "max_count:" << max_count_ << " "
                << "discount:" << discount_ << std::endl;
        }
    private:
        size_t max_count_;
        double discount_;
};

double print_total(std::ostream& os, const Quote& q, size_t n)
{
    double ret = q.net_price(n);
    os << "sum price:" << ret;
    return ret;
}




int main()
{
    Quote a1("C", 10);
    Bluck_Quote a2("C", 10, 10, 0.8);
    print_total(std::cout, a1, 10);
    std::cout << std::endl;
    print_total(std::cout, a2, 20);
    std::cout << std::endl;
    return 0;
}

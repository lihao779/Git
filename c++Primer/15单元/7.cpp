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
    
        virtual ~Quote(){
            std::cout << "~Quote()" << std::endl;
        }
        
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
        virtual ~Bluck_Quote()
        {
            std::cout << "~Bluck_Quote()" << std::endl;
        }
    private:
        size_t min_book_num;
        double discount;

};

#include <memory>
#include <vector>
int main()
{
    std::vector<std::shared_ptr<Quote>> v;
    v.push_back(std::make_shared<Bluck_Quote>("C", 10, 10, 0.8));
    v.push_back(std::make_shared<Quote>("C", 10));
    double sum = 0;
    for(auto& e: v)
        sum += e->net_price(10);
    std::cout << sum << std::endl;
    return 0;
}

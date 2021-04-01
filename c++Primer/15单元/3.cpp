#include <iostream>
#include <string>
class Quote
{
    public:
        Quote() = default;
        Quote(std::string bookname, double p) : price(p), ISBN(bookname){}
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

class Disc_Quote: public Quote
{
    public:
        Disc_Quote() = default;
        Disc_Quote(std::string book_name, double price, size_t dis_count, double discount)
            :Quote(book_name, price), dis_count_(dis_count), discount_(discount)
        {}
        virtual double net_price(size_t)const override   = 0; 
    protected:
        size_t dis_count_;
        double discount_;
};

class Bluk_Quote: public Disc_Quote
{
    public:
        Bluk_Quote() = default;
        Bluk_Quote(std::string book_name, double price, size_t dis_count, double discount)
            :Disc_Quote(book_name, price, dis_count, discount)
        {}
        virtual double net_price(size_t n)const override
        {
            if(n >= dis_count_)
                return n * price * discount_;
            else
                return n* price;
        }
};
int main()
{
    return 0;
}

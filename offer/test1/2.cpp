#include <mutex>
class Singleton
{
    public:
        static Singleton* Get()
        {
            my_mutex.lock();
            if(my_sing == nullptr)
            {
                my_sing = new Singleton();
            }
            my_mutex.unlock();
            return my_sing;
        }



    
    private:
        Singleton()
        {}
        static Singleton* my_sing;
        static std::mutex my_mutex;
};

Singleton* Singleton::my_sing = nullptr;
std::mutex Singleton::my_mutex;

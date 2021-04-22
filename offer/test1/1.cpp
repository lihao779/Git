class Singleton
{
    public:
       Singleton& Get()
       {
           return my_sing;
       }
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
    private:
        Singleton()
        {}
        static Singleton my_sing;
};
Singleton Singleton::my_sing;

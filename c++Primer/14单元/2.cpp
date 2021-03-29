class A
{
    private:
        A() {}
    
        ~A() {}
    public:
        static A* Test()
        {
            return new A;
        }
};

int main()
{
    A* p = A::Test();
    delete p;
    return 0;
}

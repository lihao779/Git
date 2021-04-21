class A
{
    private:
        A() {}
    public:
    A* Get()
    {
        return ptr;
    }
    static A* ptr;
};

A* A::ptr = new A();

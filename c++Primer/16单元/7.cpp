class DeleteDebug
{
    public:
        template<typename T>
        void operator()(T* p)const 
        {
            delete p;
        }
};

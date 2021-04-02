#if 0
#include <iostream>
using namespace std;
class A
{
    public:
        A() { cout << "A()" << endl; }
        A(const A&) { cout << "A(const A&)" << endl; }
        ~A() { cout << "~A()" << endl; }
};
#endif

#include <iostream>
#include <pthread.h>
namespace bite
{

    template<class T>
    struct DFdef
    {
        void operator()(T* p)
        {
            delete p;
            p = nullptr;
        }
    };

    template<class T, class DF = DFdef<T>>
    class shared_ptr
    {
        public:
            shared_ptr(T* p = nullptr)
                :ptr(p), pCount(nullptr), mut(nullptr)
            {
                if(ptr)
                {
                    mut = new pthread_mutex_t;
                    pthread_mutex_init(mut, NULL);
                    pCount = new int(1);
                }
            }
            shared_ptr(const shared_ptr<T, DF>&);
            shared_ptr<T, DF>& operator=(const shared_ptr<T, DF>&);
            ~shared_ptr();

            int use_count()
            {
                pthread_mutex_lock(mut);
                return *pCount;
                pthread_mutex_unlock(mut);
            }
        private:
            void Free()
            {
                if(ptr && --*pCount == 0)
                {
                    DF()(ptr);
                    delete pCount;
                    pthread_mutex_destroy(mut);
                    delete mut;
                }
            }
        private:
            T* ptr;
            int* pCount;
            pthread_mutex_t* mut;
    };
    
    template<class T, class DF>
    shared_ptr<T, DF>::shared_ptr(const shared_ptr<T, DF>& s)
    {
        pCount = s.pCount;
        ptr = s.ptr;
        mut = s.mut;
        pthread_mutxe_lock(mut);
        ++*pCount;
        pthread_mutxe_unlock(mut);
    }
    
    template<class T, class DF>
    shared_ptr<T, DF>& shared_ptr<T, DF>::operator=(const shared_ptr<T, DF>& s)
    {
        if(this != &s)
        {
            if(ptr)
            {
                Free();
            }
            ptr = s.ptr;
            pCount = s.pCount;
            mut = s.mut;
            pthread_mutxe_lock(mut);
            ++*pCount;
            pthread_mutex_unlock(mut);
        }
        return *this;
    }

    template<class T, class DF>
    shared_ptr<T, DF>::~shared_ptr()
    {
        Free();
    }
}


using std::cout;
using std::endl;

int main()
{
    bite::shared_ptr<int> p1(new int(1));
    bite::shared_ptr<int> p2;
    p2 = p1;
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
    bite::shared_ptr<int> p3(new int(1));
    bite::shared_ptr<int> p4(p3);
    cout << p3.use_count() << endl;
    cout << p4.use_count() << endl;
    p3 = p1;
    p4 = p2;
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
    cout << p3.use_count() << endl;
    cout << p4.use_count() << endl;
    return 0;
}

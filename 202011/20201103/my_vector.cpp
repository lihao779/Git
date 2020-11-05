#include<assert.h>
#include<iostream>




template <class T>
class Vector
{
    typedef T* iterator;
    public:
        Vector()
            :start(nullptr)
             ,finish(nullptr)
             ,endofstorage(nullptr)
        {}
        
        Vector(int n,const T& date = T())
            :start(new T[n])
             ,finish(start)
             ,endofstorage(start+n)
         {
             while(finish!=endofstorage)
             *finish++ = date;
         }

        template <class Iterator>
        Vector( Iterator first ,Iterator last)
        {
            int count = last-first;
            start = new T[count];
            finish = start;
            endofstorage = start+count;
        
            while(first!=last)
            {
                *finish++ = *first++;
            }
        }


        Vector(const Vector<T>& v)
            :start(new T[v.size()])
             ,finish(start+v.size())
             ,endofstorage(finish)
    {
        for(int i = 0;i<v.size();++i)
        {
            start[i] = v[i];
        }
    }
        
        ~Vector()
        {
            if(start)
            {
                delete[] start;
                start = nullptr;
                finish = nullptr;
                endofstorage = nullptr;
            }
        }

        Vector& operator=(const Vector<T>& v)
        {
            size_t newsize = v.size();
            size_t oldcapacity = capacity();
            if(newsize>oldcapacity)
            {
                reserve(newsize);
            }
            for(size_t i = 0;i<newsize;++i)
            {
                start[i] = v[i];
            }
            finish = start+newsize;
        }

        //----------------------------------iterator-----------
        iterator begin()
        {
            return start;
        }
        iterator end()
        {
            return finish;
        }
        //-------------------------------capacity-----------
        size_t size()const 
        {
            return finish - start;
        }
        void resize(size_t newsize, T date = T())
        {
           size_t oldsize = size();
           size_t oldcapacity = capacity();
           if(newsize<=oldsize)
           {
               finish = start+newsize;
           }
           else
           {
               if(newsize>oldcapacity)
               {
                   reserve(newsize);
               }
               for(size_t i = oldsize;i<newsize;++i)
               {
                    start[i] = date;
               }
                    finish  = start+newsize;
           }
        }
        size_t capacity()const 
        {
            return endofstorage-start;
        }
        bool empty()
        {
            return start == finish;
        }
        void reserve(size_t n)
        {
            size_t oldcapacity = capacity();
            size_t oldsize = size();
            if(n>oldcapacity)
            {
                T* temp = new T[n];
                for(size_t i = 0;i<size();++i)
                {
                    temp[i] = start[i];
                }
                delete[] start;
                start = temp;
                finish = start+oldsize;
                endofstorage = start+n;
            }
        }

        //----------------------element access
        T& operator[](size_t index)
        {
            assert(index<size());
            return start[index];
        }

        const T& operator[](size_t index)const
        {  
            assert(index<size());
            return start[index];
        }
        T& at(size_t index)
        {
            assert(index<size());
            return start[index];
        }

        const T& at (size_t index)const 
        {
            assert(index<size());
            return start[index];
        }
        T& front()
        {
            return start[0];
        }
        const T& front()const
        {
            return start[0]; 
        }
        T& back()
        {
            return finish[-1];
        }
        const T& back()const
        {
            return finish[-1];
        }
        //-------------modifiers
        template<class Iterator>
        void assign(Iterator first,Iterator last)
        {
            size_t count = last-first;
            start = new T[count];
            finish = start;
            endofstorage = start+count;
            while(first!=last)
            {
               *finish++ = *first++; 
            }
        }
        void assign(size_t newsize,const T& date = T())
        {
            start = new T[newsize];
            finish = start+newsize;
            endofstorage = finish;

            for(size_t i = 0;i<newsize;++i)
            {
                start[i] = date;
            }
        }
        void push_back(const T& date)
        {
            if(size()==capacity())
                reserve(2*capacity()+2);
            *finish++ = date;
        }
        void pop_back()
        {
            if(!empty())
            {
                --finish;
            }
        }
        iterator insert(iterator pos,const T& date)
        {
            assert(pos<=finish);
            size_t oldsize = size();
            if(oldsize == capacity())
            {
                reserve(2*capacity());
            }
            iterator it = finish;
            while(it!=pos)
            {
                *it = *(it-1);
                --it;
            }
            *pos = date;
            finish++;
            return pos; 
            
        }
        void insert(iterator pos,int  n,const T& date)
        {
            assert(pos<=finish);
            int oldsize = size();
            int oldcapacity = capacity();
            if((oldcapacity-oldsize)<n)
                reserve(n+oldsize);
            auto it = finish;
            while(it!=pos)
            {
                *(it+n-1) = *(it-1);
                --it;
            }
        
            for(int i = 0;i<n;i++)
            {
                *(pos+i) = date;
            }
            finish +=n;
            return pos; 
        }
        /*
        template <class Iterator>
        void insert(iterator pos,Iterator first,Iterator last)
        {
            assert(pos>=start && pos<=finish);
            int oldsize = size();
            auto itfirst = first;
            auto itend = last;
            int count = itend - itfirst;
            if(oldsize+count>capacity())
            {
                reserve(oldsize+count);
            }
            auto it = finish;
            while(it!=pos)
            {
                *(it-1+count) = *(it-1);
                --it;
            }
            
            while(first!=last)
            {
                *pos = *first;
                first++;
                pos++;
            }
        }
        */
        iterator earse(iterator pos)
        {
            assert(pos<end() && pos>=begin());
            auto it = pos;
            while(it<end()-1)
            {
                *it = *(it+1);
                it++;
            }
            finish--;
            return pos;
        }
        iterator earse(iterator first,iterator last)
        {   
            assert(first>=start && first<=last && last<=finish);
            auto itfirst = first;
            auto itend = last;
            int count = 0;
            while(itend!=finish)
            {
                count++;
                itend++;
            }
            finish = first+count;
            while(count--)
            {
                *itfirst = *last;
                itfirst++;
                last++;
            }
            return first;
        }
        void swap( Vector<T>& v)
        {
            std::swap(start,v.start);
            std::swap(finish,v.finish);
            std::swap(endofstorage,v.endofstorage);
        }
        void clear()
        {
            finish = start;
        }
    private:
        iterator start;
        iterator finish;
        iterator endofstorage;
};
/*-------------------------------测试----------------
 */
#include<string>
using namespace std;
void TestVector1()
{
    Vector<int> v1;
    Vector<int> v2(2,10);
    for(size_t i = 0;i<v2.size();++i)
    {
        cout<<v2[i]<<" ";
    }
    cout<<endl;
    int array[] = {1,2,3,4,5,6};
    Vector<int> v3(array,array+6);
    auto it = v3.begin();
    while(it!=v3.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;

    std::string s("hello world");
    Vector<char> vc(s.begin(),s.end());
    Vector<int> v4(v2);
    for(auto e : v4)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

void TestVector2()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.pop_back();
    v.pop_back();
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.insert(v.begin(),0);
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.earse(v.begin());
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.clear();
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;

}

void TestVector3()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    cout<<v[0]<<endl;
    cout<<v.front()<<endl;
    cout<<v.back()<<endl;
    //capacity: 6
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    v.resize(10);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;

    v.resize(3);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;

    v.reserve(20);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    v.reserve(10);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e : v)
    {
        cout<<e<<" ";
    }
    cout<<endl;



}

int main()
{
    // TestVector1();
    // TestVector2();
    TestVector3();
    return 0;
}

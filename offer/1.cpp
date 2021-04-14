#include <string.h>

class MyString
{
    public:
        MyString(char* data = nullptr) : data_(data) {}
        MyString(const MyString& m) : data_(new char[strlen(m.data_) + 1])
        {
            strcpy(data_, m.data_);
        }
        ~MyString()
        {
            if(data_)
                delete[] data_;
        }

        MyString& operator=(const MyString& m)
        {
            char* temp = new char[strlen(m.data_) + 1];
            strcpy(temp, m.data_);
            delete[] data_;
            data_ = temp;
            return *this;
        }
    private:
        char* data_;
};

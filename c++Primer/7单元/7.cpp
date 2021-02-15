#include <iostream>
#include <vector>
#include <string>

class Screen;
class Window_mgr
{
    public:
        typedef std::vector<Screen>::size_type ScreenIndex;
    public:
        Window_mgr()
        {
            screen.clear();
        }
        ScreenIndex addScreen(Screen& s);
        void clear(ScreenIndex);
    private:
        std::vector<Screen> screen;
};
Window_mgr::ScreenIndex Window_mgr::addScreen(Screen& s)
{
    screen.push_back(s);
    return screen.size() - 1;
}
class Screen
{
    public:
        typedef std::string::size_type pos;
        typedef std::vector<Screen>::size_type ScreenIndex;
        friend void Window_mgr::clear(ScreenIndex);
    public:
        void some_member()const
        {
            ++access_ctr;
        }

    public:
        Screen() = default;
        Screen(pos ht,pos wd,char ch = ' ')
            :height(ht)
             ,width(wd)
             ,contents(ht * wd,ch)
        {}

        char get()
        {
            return contents[cursor];
        }
        inline char get(pos r,pos c);
        Screen& move(pos r,pos c);
        Screen& set(char ch);
        Screen& set(pos r,pos c,char ch);
        
        const Screen& display(std::ostream& os)const;
        Screen& display(std::ostream& os);
        pos size()const;
        void dummy_fuc(pos height);
    private:
        void do_display(std::ostream& os)const 
        {
            os << contents;
        }
    private:
        pos height,width;
        pos cursor = 0; //光标
        std::string contents;
        mutable size_t access_ctr = 0;
};
inline char Screen::get(pos r,pos c)
{
    pos row = r * width;
    return contents[row + c];
}
Screen& Screen::move(pos r,pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}
inline Screen& Screen::set(char ch)
{
    contents[cursor] = ch;
    return *this;
}
inline Screen& Screen::set(pos r,pos c,char ch)
{
    pos row = r * width;
    contents[row + c] = ch;
    return *this;
}
const Screen& Screen::display(std::ostream& os)const
{
    do_display(os);
    return *this;
}
Screen& Screen::display(std::ostream& os)
{
    do_display(os);
    return *this;
}
Screen::pos Screen::size()const
{
    return height * width;
}
void Screen::dummy_fuc(pos height)
{
    cursor = width * height;
}


void Window_mgr::clear(ScreenIndex i)
{
    Screen& s = screen[i];
    s.contents = std::string(s.height*s.width,' ');    
}

void Test()
{
    Screen myScreen(5,5,'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
}

int main()
{
    Test();
    return 0;
}

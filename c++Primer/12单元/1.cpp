#include <iostream>
#include <string>
#include <string>
#include <memory>

using namespace std;

int main()
{
    shared_ptr<int> p1 = make_shared<int>(10);
    shared_ptr<string> p2 = make_shared<string>("hello");
    cout << *p1 << " " << *p2 << endl;
    cout << p2->c_str() << endl;
    return 0;
}

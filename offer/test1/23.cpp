#include <vector>
#include <iostream>
using namespace std;


int remove_n(vector<int>& vec, int n)
{
    int slow = 0;
    for(int fast = 0; fast < vec.size(); fast++)
    {
        if(vec[fast] != n)
        {
            vec[slow++] = vec[fast];
        }
    }
    return slow;
}



int main()
{
    vector<int> vec{1,2,3,4,5,7,6,5,5,7,8};
    int size = remove_n(vec, 5);
    for(int i = 0; i < size; i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    return 0;
}

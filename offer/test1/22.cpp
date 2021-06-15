#include <iostream>
#include <vector>
using namespace std;


int remove_n(vector<int>& vec, int n)
{
    int size = vec.size();
    for(int i = 0; i < size; i++)
    {
        if(vec[i] == n)
        {
            for(int j = i + 1; j < size; j++)
            {
                vec[j - 1] = vec[j];
            }
            i--;
            size--;
        }
    }
    return size;
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

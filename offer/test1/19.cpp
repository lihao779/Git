#include <iostream>
#include <vector>
using namespace std;

vector<int> find1(const vector<int>& v, int num)
{
    int left = 0, right = v.size() - 1;
    vector<int> vec = {-1, -1};
    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if(v[mid] == num)
        {
            vec[0] = mid;
            vec[1] = mid;
            int temp = mid - 1;
            while(temp >= 0 && v[temp] == num)
            {
                vec[0] = temp;
                temp--;
            }
            temp = mid + 1;
            while(temp < v.size() && v[temp] == num)
            {
                vec[1] = temp;
                temp++;
            }
            return vec;
        }
        else if(v[mid] > num)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return vec;
}
vector<int> find2(const vector<int>& v, int num)
{
    int left = 0, right = v.size();
    vector<int> vec = {-1, -1};
    while(left < right)
    {
        int mid = left + ((right - left) >> 1);
        if(v[mid] == num)
        {
            vec[0] = vec[1] = mid;
            int temp = mid - 1;
            while(temp >= 0 && v[temp] == num)
            {
                vec[0] = temp;
                temp--;
            }
            temp = mid + 1;
            while(temp < v.size() && v[temp] == num)
            {
                vec[1] = temp;
                temp++;
            }
            return vec; 
        }
        else if(v[mid] > num)
            right = mid;
        else 
            left = mid + 1;
    }
    return vec;
}


int main()
{
    vector<int> vec = {1, 2, 3, 3, 4, 5, 6};
    vector<int> v = {0, 0};
    vector<int> vec1;
    v = find1(vec1, 3);
    cout << "begin: " << v[0] << " end: " << v[1] << endl;

    return 0;
}

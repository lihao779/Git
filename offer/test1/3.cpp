
#include <vector>
using namespace std;

int minArray(vector<int>& numbers) {
    if(numbers[0] <= numbers[numbers.size() - 1])
        return numbers[0];

    int left = 0;
    int right = numbers.size() - 1;

    while(right - left > 1)
    {
        int mid = left + (right - left) >> 1;
        if(numbers[mid] >= numbers[left])
            left = mid;
        else if(numbers[mid] <= numbers[right])
            right = mid;

    }
    return numbers[right];

}

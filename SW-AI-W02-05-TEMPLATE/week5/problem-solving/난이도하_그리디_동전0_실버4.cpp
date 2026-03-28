#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n, k;
    int count = 0;
    cin >> n >> k;

    vector <int> numbers(n);
    
    for(int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }

    for(int i = n - 1; i >= 0; i--) // 역순으로
    {
        while(true)
        {
            if(numbers[i] <= k)
            {
                k = k - numbers[i];
                count++;
                continue;
            }
            else 
            {
                break;
            }
        }
    }

    cout << count;

    return 0;
}
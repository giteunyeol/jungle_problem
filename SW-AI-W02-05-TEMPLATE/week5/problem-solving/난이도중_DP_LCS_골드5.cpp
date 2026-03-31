#include <iostream>
#include <string>

using namespace std;

string lcs1;
string lcs2;

int dp[1002][1002];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> lcs1 >> lcs2;
    
    for(int i = 1; i <= lcs1.size(); i++)
    {
        for(int j = 1; j <= lcs2.size(); j++)
        {
            if(lcs1[i - 1] == lcs2[j - 1]) { dp[i][j] = dp[i - 1][j-1] + 1;} //같으면 그냥 하나 더함
            else { dp[i][j] = max(dp[i-1][j], dp[i][j-1]);}
        }
    }
    cout << dp[lcs1.size()][lcs2.size()];
    
    return 0;
}
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int dp[10002][1002]; 
bool cant[10002]; //갈 수 없는 곳 저장할 돌

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; //n은 돌의 갯수, m갈 수 없는 돌
    cin >> n >> m;

    for(int i = 0; i < 10002; i++) //큰걸로 초기화
    {
        for(int j = 0; j < 1002; j++)
        {
            dp[i][j] = 1e9;
        }
    }

    for(int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        cant[k] = true; //못가는 곳은 트루로 표시
    }

    dp[1][0] = 0;
    
    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j <= 1000; j++)
        {
            if(!cant[i] && i - j >= 1) //갈 수 있는 곳이면
            {
                dp[i][j] = min({dp[i - j][j - 1], dp[i - j][j], dp[i - j][j + 1]}) + 1;
            }
        }
    }

    int ans = *min_element(dp[n], dp[n] + 1002);
    if(ans == 1e9)
    {
        cout << -1;
        return 0;
    }
    cout << ans;

    return 0;
}
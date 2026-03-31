#include <iostream>
using namespace std;

int n, k;
int d[102][100002];
int w[102];
int v[102];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 물건도 1번부터 저장
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            // 현재 물건을 못 담는 경우
            if (j < w[i])
                d[i][j] = d[i - 1][j];
            // 현재 물건을 담을 수 있는 경우
            else
                d[i][j] = max(d[i - 1][j], d[i - 1][j - w[i]] + v[i]);
        }
    }

    cout << d[n][k];
    return 0;
}
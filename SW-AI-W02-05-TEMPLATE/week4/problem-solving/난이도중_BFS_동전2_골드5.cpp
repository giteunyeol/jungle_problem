#include <iostream>
#include <queue>

using namespace std;

#define X first 
#define Y second 

int coins[102]; //동전의 가치들 저장
bool vis[10002]; //방문 여부 저장할 변수

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; // n: 동전의 갯수, k: 동전의 가치
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> coins[i];
    }
    
    queue <pair <int, int>> Q; //앞이 현재 가격, 뒤가 코인 갯수
    Q.push({0,0});
    vis[0] = true;

    while(!Q.empty())
    {
        pair<int, int> cur = Q.front();
        Q.pop();

        if(cur.X == k)
        {
            cout << cur.Y;
            exit(0);
        }
        
        for(int i = 0; i < n; i++) //동전의 갯수만큼 
        {
            int next = cur.X + coins[i]; //현재 모인 가격 + 현재 for문이 순회하고있는 코인의 가격
            if(next > k) { continue; }
            if(vis[next] != 0 ) { continue; } //가격이 차있으면 컨티뉴
            vis[next] = true;
            Q.push({next, cur.Y + 1});
        }

    }
    cout << "-1";

    return 0;
}
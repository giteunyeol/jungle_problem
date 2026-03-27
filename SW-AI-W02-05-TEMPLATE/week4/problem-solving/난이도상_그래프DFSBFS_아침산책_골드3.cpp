#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

bool vis[2000002]; // 방문여부 체크할 벡터, 새로운 시작점마다 초기화

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);    

    int node;  //node의 갯수
    int ans = 0; // 답
    cin >> node;
    vector <int> nodes[node + 1]; //노드들의 연결관계 저장할 벡터
    vector <bool> is_indoor(node + 1); //해당 노드가 실외인지, 야외인지 저장할 벡터
    string indoor;
    cin >> indoor;

    for(int i = 1; i <= node; i++)
    {
        if(indoor[i - 1] == '0')
        {
            is_indoor[i] = false;
        }
        else
        is_indoor[i] = true;
    }

    for(int i = 0; i < node - 1; i++) //node들 경로 저장
    {
        int a, b;
        cin >> a >> b;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }

    for(int i = 1; i <= node; i++) //전체 노드들 시작점으로 순회
    {
        memset(vis, 0, sizeof(vis)); //새로운 시작점 들어갈때마다 방문여부 초기화
        queue <int> Q; //현재 좌표 저장
        Q.push(i);
        vis[i] = true;

        while(!Q.empty())
        {
            int cur = Q.front();
            Q.pop();
            for(int nxt = 0; nxt < nodes[cur].size(); nxt++)
            {
                int nx = nodes[cur][nxt]; // nodes[cur][nxt] = 현재 순회하고 있는 노드에 연결된 노드들
                if(vis[nx]) { continue; }
                if(is_indoor[nx]) { continue; } //야외면 컨티뉴 
                vis[nx] = true;
                ans++;
                Q.push(nx);
            }
        }
        
    }

    cout << ans;

    return 0; 
}
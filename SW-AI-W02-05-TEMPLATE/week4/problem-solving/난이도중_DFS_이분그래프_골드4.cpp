#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define X first 
#define Y second

int colors[20002]; //해당 노드 방문여부, 현재 진영. 테스트케이스 바뀔때마다 -1로 리셋, -1 = 미방문, 0 = 1번진영, 1 = 2번진영

//이분 그래프니까 한칸 움직일때마다 이전것과 다른게 나오면 됨
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    for(int t = 0; t < tc; t++)
    {
        int v, e;
        cin >> v >> e; // vertex,edge
        vector <int> nodes[v + 1]; //vertex갯수 + 1만큼 생성 
        memset(colors, -1, sizeof(colors)); //새로운 테스트케이스가 됐으니 vis초기화
        bool nxt_tc = false; // while문 돌때 No출력되면 다음 테스트케이스로 넘어갈 변수

        for (int i = 0; i < e; i++) // edge번 만큼 벡터에 삽입, 엣지 생성
        {
            int a, b;
            cin >> a >> b;
            nodes[a].push_back(b); //문제 조건이 무방향 그래프인 것 같음
            nodes[b].push_back(a);
        }

        queue <int> Q;

        for(int i = 1; i <= v; i++)
        {
            //각 모든 노드에 대해 bfs
            if(colors[i] == -1) //만약 방문하지 않았다면 ! 큐에 푸쉬
            {
                Q.push(i);
                colors[i] = 0; //첫번째 색으로 저장
            }

            while(!Q.empty()) //Q가 빌때까지
            {
                int cur = Q.front(); //몇번째 벡터인지 셀렉. 그 후 nxt로 해당 벡터 인덱스들 순회
                Q.pop();
                for(int nxt = 0; nxt < nodes[cur].size(); nxt++)// nxt로 해당 인덱스 벡터 순회
                {
                    if (colors[nodes[cur][nxt]] == -1) // 방문 안한 노드면
                    {
                        colors[nodes[cur][nxt]] = 1 - colors[cur]; // 다른 컬러로 변경
                        Q.push(nodes[cur][nxt]);
                    }
                    else
                    {
                        if (colors[nodes[cur][nxt]] == colors[cur]) // 해당 컬러랑 현재컬러가 같으면 no출력하고 다음걸로
                        {
                            cout << "NO\n";
                            nxt_tc = true;
                            break;
                        }
                    }
                }
                if(nxt_tc) { break; }
            }
            if(nxt_tc) { break; }
        }
        if(nxt_tc) { continue; }

        //while문을 다 통과하면 이분그래프니까 YES출력하고 줄바꿈
        cout << "YES\n";
    }

    return 0;
}
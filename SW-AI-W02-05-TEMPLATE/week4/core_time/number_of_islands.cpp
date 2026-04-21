#include <queue>
#include <cstring>

#define X first
#define Y second

bool vis[302][302]; // 방문 여부를 판별하는 배열

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {

        int ans = 0;
        memset(vis, 0, sizeof(vis));
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (vis[i][j] == 0 && grid[i][j] == '1') // 만약 방문을 안했고, grid가 1이라면
                {
                    ans++; // 섬에 들어오면 답 더해줌
                    queue<pair<int, int>> Q;
                    Q.push({i, j});
                    vis[i][j] = 1;

                    while (!Q.empty())
                    {
                        pair<int, int> cur = Q.front();
                        Q.pop();

                        for (int dir = 0; dir < 4; dir++)
                        {
                            int nx = cur.X + dx[dir];
                            int ny = cur.Y + dy[dir];
                            if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                            {
                                continue;
                            }
                            if (vis[nx][ny] == 1 || grid[nx][ny] == '0')
                            {
                                continue;
                            } // 이미 방문했거나, 방문할 곳이 아니면(0이면 컨티뉴)
                            Q.push({nx, ny});
                            vis[nx][ny] = 1;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
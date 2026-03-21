#include <iostream>
#include <queue>

using namespace std;

#define X first
#define Y second

int dx[2] = {1, 0};
int dy[2] = {0, 1};

int board[4][4];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }
    queue<pair<int, int>> Q;
    Q.push({0, 0});

    while (!Q.empty())
    {
        pair<int, int> cur = Q.front();
        Q.pop();
        if (board[cur.X][cur.Y] == 0)
        {
            continue;
        }
        for (int dir = 0; dir < 2; dir++)
        {
            int nx = cur.X + (dx[dir] * board[cur.X][cur.Y]);
            int ny = cur.Y + (dy[dir] * board[cur.X][cur.Y]);
            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
            {
                continue;
            }
            if (board[nx][ny] == -1)
            {
                cout << "HaruHaru";
                exit(0);
            }
            Q.push({nx, ny});
        }
    }
    cout << "Hing";

    return 0;
}
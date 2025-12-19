#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int n = 5;
int mattrix[n][n];
int visited[n][n];
int result = 0;

const int dy[4] = { 0, 0, 1, -1 };
const int dx[4] = { 1, -1, 0, 0 };

void BFS(int sx, int sy)
{
    queue<pair<int, int>> q;
    visited[sy][sx] = 1;
    q.push({ sy, sx });
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if (mattrix[ny][nx] == 0) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = visited[y][x] + 1;
            q.push({ ny, nx });
        }
    }
}

int main()
{
    int sx, sy, gx, gy;
    cin >> sy >> sx >> gy >> gx;
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> mattrix[i][j];
        }
    }

    BFS(sx, sy);

    cout << visited[gy][gx] - 1;
}

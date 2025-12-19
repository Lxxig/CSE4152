/*#include <iostream>
#include <queue>

using namespace std;

struct Color
{
    int r, g, b;

    bool operator==(const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Color& other) const
    {
        return !(*this == other);
    }
};

const int MAX = 1004;
Color grid[MAX][MAX];
bool visited[MAX][MAX];
int N, M;

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

void BFS(int sy, int sx)
{
    visited[sy][sx] = true;
    queue<pair<int, int>> q;
    q.push({sy, sx});

    while (!q.empty())
    {
        int Y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 8; ++i)
        {
            int ny = Y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny > N || nx < 0 || nx >= M) continue;
            if (visited[ny][nx]) continue;
            if (grid[ny][nx] != grid[Y][x]) continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
    
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> grid[i][j].r >> grid[i][j].g >> grid[i][j].b;
        }
    }

    int result = 0;
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < M; ++x)
        {
            if (visited[y][x] == false)
            {
                ++result;
                BFS(y, x);
            }
        }
    }

    cout << result << "\n";
}*/

#include <iostream>

using namespace std;

struct Color
{
    int r, g, b;

    bool operator==(const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Color& other) const
    {
        return !(*this == other);
    }
};

const int MAX = 1004;
Color grid[MAX][MAX];
bool visited[MAX][MAX];
int N, M;

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

void DFS(int y, int x)
{
    visited[y][x] = true;

    for (int i = 0; i < 8; ++i)
    {
        int next_y = y + dy[i];
        int next_x = x + dx[i];

        if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= M) continue;
        if (visited[next_y][next_x]) continue;
        if (grid[next_y][next_x] != grid[y][x]) continue;
        DFS(next_y, next_x);
    }
    
    return;
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> grid[i][j].r >> grid[i][j].g >> grid[i][j].b;
        }
    }

    int result = 0;
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < M; ++x)
        {
            if (visited[y][x] == false)
            {
                ++result;
                DFS(y, x);
            }
        }
    }

    cout << result << "\n";
}
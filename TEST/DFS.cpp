#include <iostream>

using namespace std;

const int n = 5, m = 5;
int mattrix[n][m];
bool visited[n][m];

int direct_x[4] = { 0, 0, 1, -1 };
int direct_y[4] = { 1, -1, 0, 0 };

void DFS(int y, int x)
{
    visited[y][x] = true;

    for (int i = 0; i < 4; ++i)
    {
        int next_y = y + direct_y[i];
        int next_x = x + direct_x[i];

        if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n) continue;
        if (visited[next_y][next_x]) continue;
        if (mattrix[next_y][next_x] == 1)
        {
            DFS(next_y, next_x);
        }
    }

    return;
}

int main()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> mattrix[i][j];
        }
    }

    int reuslt = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (visited[y][x] == false && mattrix[y][x] == 1)
            {
                DFS(y, x);
                ++reuslt;
            }
        }
    }

    cout << reuslt << endl;
    return 0;
}
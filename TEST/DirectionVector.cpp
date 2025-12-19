#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mattrix[3][3];
bool visited[3][3];
const int direct_x[4] = { 0, 0, 1, -1 };
const int direct_y[4] = { 1, -1, 0, 0 };

void Solve(int y, int x)
{
    if (visited[y][x]) return;
    cout << x << " "<< y << "\n";
    visited[y][x] = true;
    
    for (int i = 0; i < 4; ++i)
    {
        int next_y = y + direct_y[i];
        int next_x = x + direct_x[i];

        if (next_x < 0 || next_x >= 3 || next_y < 0 || next_y >= 3) continue;
        if (mattrix[next_y][next_x] == 0) continue;
        if (visited[next_y][next_x]) continue;
        Solve(next_y, next_x);
    }
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> mattrix[i][j];
        }
    }

    Solve(0, 0);
    
    return 0;
}

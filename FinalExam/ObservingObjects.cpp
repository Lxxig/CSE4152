#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 픽셀의 색상 정보를 저장할 구조체
struct Color {
    int r, g, b;

    // 두 색상이 같은지 비교하기 위한 연산자 오버로딩
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    
    // 색상이 다를 경우를 위한 연산자 (필요 시)
    bool operator!=(const Color& other) const {
        return !(*this == other);
    }
};

// 최대 크기 설정 (문제 조건 N, M <= 1000)
const int MAX = 1005;

int N, M;
Color grid[MAX][MAX];
bool visited[MAX][MAX];

// 8방향 탐색을 위한 배열 (상, 하, 좌, 우, 대각선 4방향)
/*int di[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};*/

int di[8] = {0, 0, 1, -1};
int dj[8] = {1, -1, 0, 0};

void bfs(int start_i, int start_j) {
    queue<pair<int, int>> q;
    q.push({start_i, start_j});
    visited[start_i][start_j] = true;
    
    // 현재 시작점의 색상 저장
    Color targetColor = grid[start_i][start_j];

    while (!q.empty()) {
        int ci = q.front().first;
        int cj = q.front().second;
        q.pop();

        for (int k = 0; k < 8; k++) {
            int ni = ci + di[k];
            int nj = cj + dj[k];

            // 1. 격자 범위를 벗어나는지 확인
            if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

            // 2. 이미 방문했는지 확인
            if (visited[ni][nj]) continue;

            // 3. 색상이 같은지 확인
            if (grid[ni][nj] == targetColor) {
                visited[ni][nj] = true;
                q.push({ni, nj});
            }
        }
    }
}

int main() {
    // 입출력 속도 향상 (대량의 입력 처리에 필수)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M)) return 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // cin은 공백과 줄바꿈을 무시하고 순서대로 입력을 받으므로
            // 한 줄에 3*M개의 정수가 있어도 순서대로 R, G, B에 저장됨
            cin >> grid[i][j].r >> grid[i][j].g >> grid[i][j].b;
        }
    }

    int objectCount = 0;

    // 모든 좌표를 순회하며 탐색
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 아직 방문하지 않은 픽셀이라면 새로운 물체의 시작점
            if (!visited[i][j]) {
                objectCount++;
                bfs(i, j); // 해당 물체와 연결된 모든 픽셀 방문 처리
            }
        }
    }

    cout << objectCount << "\n";

    return 0;
}
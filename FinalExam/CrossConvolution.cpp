#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K, S;
    
    if (!(cin >> N >> M >> K >> S)) return 0;

    vector<vector<long long>> matrix(N, vector<long long>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }

    // 결과 행렬의 크기 계산
    // (N - K) / S + 1
    int outH = (N - K) / S + 1;
    int outW = (M - K) / S + 1;

    if (outH <= 0 || outW <= 0) {
        return 0; // 출력할 것이 없음
    }

    int center = K / 2; // 커널의 중심 오프셋 (0-indexed)

    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            // 현재 커널의 좌상단 위치 (r, c)
            int r = i * S;
            int c = j * S;

            long long sum = 0;

            // 1. 가로축 더하기 (Row: r + center)
            // 범위: (r + center, c) ~ (r + center, c + K - 1)
            int rowIdx = r + center;
            for (int k = 0; k < K; k++) {
                sum += matrix[rowIdx][c + k];
            }

            // 2. 세로축 더하기 (Col: c + center)
            // 범위: (r, c + center) ~ (r + K - 1, c + center)
            int colIdx = c + center;
            for (int k = 0; k < K; k++) {
                sum += matrix[r + k][colIdx];
            }

            // 3. 중복 제거 (중심점은 가로, 세로에서 두 번 더해졌으므로 한 번 뺌)
            sum -= matrix[rowIdx][colIdx];

            cout << sum << (j == outW - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
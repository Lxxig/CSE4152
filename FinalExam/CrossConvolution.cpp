#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 입출력 속도 향상 (필수)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K, S;
    if (!(cin >> N >> M >> K >> S)) return 0;

    // 원본 데이터를 저장할 필요 없이 입력받으면서 누적 합을 바로 계산해도 되지만,
    // 이해를 돕기 위해 matrix에 받고 누적합을 계산하겠습니다.
    vector<vector<long long>> matrix(N, vector<long long>(M));
    
    // 1-based index처럼 사용하여 계산을 편하게 하기 위해 크기를 +1로 잡습니다.
    // psum_row[i][j]: i행의 0~j-1열까지의 합
    vector<vector<long long>> psum_row(N, vector<long long>(M + 1, 0));
    
    // psum_col[i][j]: j열의 0~i-1행까지의 합
    vector<vector<long long>> psum_col(N + 1, vector<long long>(M, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];

            // 가로 누적 합 계산 (i행)
            psum_row[i][j + 1] = psum_row[i][j] + matrix[i][j];
            
            // 세로 누적 합 계산 (j열)
            psum_col[i + 1][j] = psum_col[i][j] + matrix[i][j];
        }
    }

    int outH = (N - K) / S + 1;
    int outW = (M - K) / S + 1;
    int center = K / 2; // 커널 내 중심 오프셋

    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            // 현재 커널의 좌상단 (r, c)
            int r = i * S;
            int c = j * S;

            // 십자가 모양의 중심 좌표 (전체 행렬 기준)
            int midR = r + center;
            int midC = c + center;

            // 1. 가로축 합 구하기 (Row: midR)
            // 범위: [c, c + K - 1] -> 누적합 인덱스로는 [c+K] - [c]
            long long rowSum = psum_row[midR][c + K] - psum_row[midR][c];

            // 2. 세로축 합 구하기 (Col: midC)
            // 범위: [r, r + K - 1] -> 누적합 인덱스로는 [r+K] - [r]
            long long colSum = psum_col[r + K][midC] - psum_col[r][midC];

            // 3. 중복 제거 (중심점은 두 번 더해졌으므로 한 번 뺌)
            // 십자가 합 = 가로줄 합 + 세로줄 합 - 중심값
            long long result = rowSum + colSum - matrix[midR][midC];

            cout << result << (j == outW - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
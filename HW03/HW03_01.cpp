/*#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // 빠른 입출력
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 초기 행렬 A 입력
    vector<vector<double>> A(N, vector<double>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    int Q;
    cin >> Q;

    // 1. 차분 배열 생성 (경계 처리를 위해 N+1 크기로 생성)
    vector<vector<double>> diff(N + 1, vector<double>(N + 1, 0.0));

    // 2. 쿼리 처리
    for (int q = 0; q < Q; ++q) {
        int R1, R2, C1, C2;
        double V;
        cin >> R1 >> R2 >> C1 >> C2 >> V;

        // 1-based 인덱스를 0-based로 변환
        int r1 = R1 - 1, r2 = R2 - 1, c1 = C1 - 1, c2 = C2 - 1;

        diff[r1][c1] += V;
        if (c2 + 1 < N) {
            diff[r1][c2 + 1] -= V;
        }
        if (r2 + 1 < N) {
            diff[r2 + 1][c1] -= V;
        }
        if (r2 + 1 < N && c2 + 1 < N) {
            diff[r2 + 1][c2 + 1] += V;
        }
    }

    // 3. 최종 결과 계산 (2D 누적합)
    // 가로 누적합
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            diff[i][j] += diff[i][j - 1];
        }
    }
    // 세로 누적합
    for (int j = 0; j < N; ++j) {
        for (int i = 1; i < N; ++i) {
            diff[i][j] += diff[i - 1][j];
        }
    }

    // 4. 원본 행렬에 적용 및 출력
    cout << fixed << setprecision(12);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] += diff[i][j];
            cout << A[i][j] << (j == N - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct query {
    int R1, R2, C1, C2;
    double V;
};

void matrix_addition(int N, vector<vector<double>>& A, int Q, vector<query>& queries) {
    //TODO:

    for (query& q : queries)
    {
        q = {q.R1 - 1, q.R2 - 1, q.C1 - 1, q.C2 - 1, q.V};
    }
    
    vector<vector<double>> DifferenceMatrix(N + 1, vector<double>(N + 1, 0.0));

    for (int q = 0; q < Q; ++q)
    {
        DifferenceMatrix[queries[q].R1][queries[q].C1] += queries[q].V;

        if (queries[q].R2 + 1 < N)
        {
            DifferenceMatrix[queries[q].R2 + 1][queries[q].C1] -= queries[q].V;
        }

        if (queries[q].C2 + 1 < N)
        {
            DifferenceMatrix[queries[q].R1][queries[q].C2 + 1] -= queries[q].V;
        }

        if (queries[q].R1 + 1 < N && queries[q].C2 + 1 < N)
        {
            DifferenceMatrix[queries[q].R2 + 1][queries[q].C2 + 1] += queries[q].V;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 1; j < N; ++j)
        {
            DifferenceMatrix[i][j] += DifferenceMatrix[i][j - 1];
        }
    }
    
    for (int i = 0; i < N; ++i)
    {
        for (int j = 1; j < N; ++j)
        {
            DifferenceMatrix[j][i] += DifferenceMatrix[j - 1][i];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            A[i][j] += DifferenceMatrix[i][j];
        }
    }
}

int main() {
    // Do NOT delete these lines unless you know what you are doing:
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<double>> A(N, vector<double>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    int Q;
    cin >> Q;

    vector<query> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].R1 >> queries[i].C1 >> queries[i].R2 >> queries[i].C2 >> queries[i].V;
    }

    matrix_addition(N, A, Q, queries);

    cout << fixed << setprecision(12);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
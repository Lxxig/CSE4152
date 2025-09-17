#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int GetMaxArea(const vector<int>& Heights)
{
    stack<int> S;
    int N = static_cast<int>(Heights.size());
    int MaxArea = 0;

    for(int i = 0; i <= N; ++i)
    {
        // 스택 마지막까지 막대 높이가 계속 커지면 Stack을 비울 수 없기때문에 i == N이면 0d으로 해줘야 함.
        int CurrentHeight = (i == N) ? 0 : Heights[i];

        while(!S.empty() && Heights[S.top()] >= CurrentHeight)
        {
            int Height = Heights[S.top()];
            S.pop();

            int Width = S.empty() ? i : i - S.top() - 1;
            MaxArea = max(MaxArea, Width * Height);
        }

        S.push(i);
    }

    return MaxArea;
}

int maximalRectangle(const vector<vector<int>>& mat) {
    
    int area = 0;
    
    // TODO
    vector<int> Heights(static_cast<int>(mat[0].size()), 0);
    for(const auto& vec : mat)
    {
        for(int i = 0; i < static_cast<int>(vec.size()); ++i)
        {
            Heights[i] = (vec[i] == 0) ? 0 : Heights[i] + 1;
        }

        area = max(area, GetMaxArea(Heights));
    }

    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> mat(N, vector<int> (N));
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            
            cin >> mat[i][j];
        
        }
    }
    
    cout << maximalRectangle(mat) << "\n";
}
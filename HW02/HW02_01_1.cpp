#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <functional>
using namespace std;

int GetLargestNumber(const vector<int>& Numbers, int& OutCurrentRow)
{
    int LargestNumber = numeric_limits<int>::min();
    for (int i = 0; i < static_cast<int>(Numbers.size()); ++i)
    {
        if (Numbers[i] > LargestNumber)
        {
            LargestNumber = Numbers[i];
            OutCurrentRow = i;
        }
    }

    return LargestNumber;
}

int GetLargestNumberOfRow(const vector<int>& RowOfMatrix, int PivotNumber)
{
    int LargestNumber = numeric_limits<int>::min();
    for (int i = 0; i < static_cast<int>(RowOfMatrix.size()); ++i)
    {
        if (RowOfMatrix[i] > LargestNumber && RowOfMatrix[i] < PivotNumber)
        {
            LargestNumber = RowOfMatrix[i];
        }
    }

    return LargestNumber;
}

vector<int> findNLargestElements(const vector<vector<int>>& matrix, int n) {
    vector<int> largestElements;
    // TODO:
    vector<int> Result(n);
    
    for (int i = 0; i < n; ++i)
    {
        int LargestNumber = numeric_limits<int>::min();
        for (int j = 0; j < n; ++j)
        {
            LargestNumber = std::max(matrix[i][j], LargestNumber);
        }
        largestElements.push_back(LargestNumber);
    }

    for (int i = 0; i < n; ++i)
    {
        // 가장 큰 N개의 값 중에서 가장 큰 값을 Result에 저장.
        int CurrentRow = 0;
        Result[i] = GetLargestNumber(largestElements, CurrentRow);

        // CurrentRow에서 LargestNumber로 확정된 수를 제외한 가장 큰 수 찾기.
        largestElements[CurrentRow] = GetLargestNumberOfRow(matrix[CurrentRow], Result[i]);
    }
    
    sort(Result.begin(), Result.end(), greater<int>());
    
    return Result;
}

int main() {
    // Do NOT delete these lines unless you know what you are doing:
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> M(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> M[i][j];
        }
    }

    vector<int> largestElements = findNLargestElements(M, n);

    for (int element : largestElements) {
        cout << element << "\n";
    }

    return 0;
}

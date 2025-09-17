#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

vector<int> findNLargestElements(const vector<vector<int>>& matrix, int n) {
    vector<int> largestElements;
    // TODO:
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            largestElements.push_back(matrix[i][j]);
        }
    }
    
    nth_element(
        largestElements.begin(),
        largestElements.begin() + n - 1,
        largestElements.end(),
        greater<int>()
    );
    
    vector<int> result(largestElements.begin(), largestElements.begin() + n);
    
    sort(result.begin(), result.end(), greater<int>());

    return result;
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

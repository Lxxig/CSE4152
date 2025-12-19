#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting {
    long long s, e, p;
};

// 종료 시간 기준 정렬, 종료 시간 같으면 시작 시간 기준
bool compareMeetings(const Meeting& a, const Meeting& b) {
    if (a.e != b.e) return a.e < b.e;
    return a.s < b.s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<Meeting> meetings(N);
    for (int i = 0; i < N; i++)
    {
        cin >> meetings[i].s >> meetings[i].e >> meetings[i].p;
    }

    sort(meetings.begin(), meetings.end(), compareMeetings);

    // dp[i]: i번째 회의(정렬된 순서)까지 고려했을 때 최대 이익
    // dp 배열 크기를 N+1로 하여 1-based indexing 처럼 사용하거나
    // 별도의 배열에 '종료 시간'만 저장해서 이분 탐색을 편하게 함
    
    vector<long long> dp(N);
    vector<long long> end_times(N); // 이분 탐색용 종료 시간 배열

    for(int i=0; i<N; i++) {
        end_times[i] = meetings[i].e;
    }

    // 첫 번째 회의 초기화
    dp[0] = meetings[0].p;

    for (int i = 1; i < N; i++) {
        // 1. 현재 회의(i)를 선택하지 않는 경우: 이전까지의 최대값 유지
        long long currentProfit = meetings[i].p;
        
        // 2. 현재 회의(i)를 선택하는 경우: 
        // 현재 회의 시작 시간(s)보다 작거나 같은 종료 시간을 가진 회의 중 가장 마지막 것을 찾음
        // upper_bound는 초과하는 첫 위치를 반환하므로, 시작지점부터 그 위치 직전까지가 후보
        
        auto it = upper_bound(end_times.begin(), end_times.begin() + i, meetings[i].s);
        int prevIdx = distance(end_times.begin(), it) - 1;

        if (prevIdx >= 0) {
            currentProfit += dp[prevIdx];
        }

        dp[i] = max(dp[i-1], currentProfit);
    }

    cout << dp[N-1] << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
long long N, L, R, arr[40005][3];

// 4개의 함수의 "함수 원형(인자/반환형/이름)"은 절대 바꾸면 안됩니다.
// 전역 변수/함수/클래스 정의 등은 자유롭게 수정하거나 추가해도 됩니다.
// 정답을 최종 제출할 때 I/O(입출력)는 진행하면 안됩니다. 채점기는 이 4개의 함수만 호출하며 I/O는 엄격히 금지합니다.
// 디버그, 테스트 목적의 출력은 허용됩니다. (e.g. printf, cout)
// I/O를 조작하여 부당한 점수를 얻은 경우, 향후 재채점에서 0점 처리됩니다.
using int64 = long long;
vector<vector<pair<int64, int64>>> Memo;

vector<pair<int64, int64>> Normalize(vector<pair<int64, int64>>& Intervals)
{
    if (Intervals.empty())
    {
        return {};
    }

    sort(Intervals.begin(), Intervals.end());

    vector<pair<int64, int64>> Merged;
    Merged.push_back(Intervals[0]);

    for (size_t i = 1; i < Intervals.size(); ++i) {
        if (Merged.back().second == LONG_MAX || Intervals[i].first <= Merged.back().second + 1)
        {
            Merged.back().second = max(Merged.back().second, Intervals[i].second);
        }
        else
        {
            Merged.push_back(Intervals[i]);
        }
    }
    
    return Merged;
}

// 두 구간 목록의 교집합을 구하는 함수
vector<pair<int64, int64>> IntersectIntervals(const vector<pair<int64, int64>>& V1, const vector<pair<int64, int64>>& V2)
{
    vector<pair<int64, int64>> Result;
    
    size_t i = 0, j = 0;
    while (i < V1.size() && j < V2.size())
    {
        int64 start = max(V1[i].first, V2[j].first);
        int64 end = min(V1[i].second, V2[j].second);

        if (start <= end)
        {
            Result.emplace_back(start, end);
        }

        if (V1[i].second < V2[j].second)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return Result;
}

// 여러 구간 목록의 합집합을 구하는 함수
vector<pair<int64, int64>> UnionIntervals(vector<pair<int64, int64>>& V1, vector<pair<int64, int64>>& V2)
{
    vector<pair<int64, int64>> AllIntervals;
    AllIntervals.insert(AllIntervals.end(), V1.begin(), V1.end());
    AllIntervals.insert(AllIntervals.end(), V2.begin(), V2.end());
    
    return Normalize(AllIntervals);
}

// 오버플로우/언더플로우를 방지하는 안전한 덧셈/뺄셈
int64 SafeOp(int64 Value, int64 Offset, bool IsAdd)
{
    if (IsAdd)
    {
        if (Offset > 0 && Value > LLONG_MAX - Offset)
        {
            return LLONG_MAX;
        }
        
        if (Offset < 0 && Value < LLONG_MIN - Offset)
        {
            return LLONG_MIN;
        }
        
        return Value + Offset;
    }

    if (Offset > 0 && Value < LLONG_MIN + Offset)
    {
        return LLONG_MIN;
    }
        
    if (Offset < 0 && Value > LLONG_MAX + Offset)
    {
        return LLONG_MAX;
    }
        
    return Value - Offset;
}


// 구간을 특정 값만큼 shift시키는 함수
vector<pair<int64, int64>> ShiftIntervals(const vector<pair<int64, int64>>& Intervals, int64 Card)
{
    vector<pair<int64, int64>> Shifted;
    for (const auto& p : Intervals)
    {
        Shifted.emplace_back(SafeOp(p.first, Card, false), SafeOp(p.second, Card, false));
    }

    return Shifted;
}

// 특정 값이 구간에 포함되는지 확인하는 함수
bool IsInIntervals(int64 Sum, const vector<pair<int64, int64>>& Intervals)
{
    auto it = upper_bound(Intervals.begin(), Intervals.end(), make_pair(Sum, LLONG_MAX));
    if (it == Intervals.begin()) {
        return false;
    }
    
    --it;
    
    return Sum >= it->first && Sum <= it->second;
}

bool need_debug() {

    // 이 함수는 딱 한번 호출됩니다.
    // 실제 게임이 어떻게 되었는지 확인하고 싶으면 true를 return하면 됩니다. 이외에는 false를 return하면 됩니다.
    // true를 return해도 채점이 되긴 하지만, 정답을 최종 제출할 땐 false를 return하는 상태로 제출하는것을 권장합니다.

    // return false; // 정답을 제출할 때에는 false로 바꿔주세요.
    return false;
    
}

void alice_init(long long n, long long l, long long r, const std::vector<std::vector<long long>>& v) {
    
    N = n, L = l, R = r;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) arr[i][j] = v[i][j];
    }

    // 이 함수는 딱 한번 호출됩니다. 
    // 여기서 입력을 보관하고, 필요한 무거운 연산들인 전처리/사전 계산 등을 모두 끝내야 합니다.
    // 이후 alice_ban()를 반복적으로 실행할 때, 충분히 빠르게 동작해야 합니다.
    // 총 수행시간 중 채점기와 Bob의 코드의 총 수행시간은 5초 미만임을 보장합니다.
    // 즉 alice_init, is_alice_win을 한번 실행하고 alice_ban을 N번 실행하는 시간의 총 합은 15초 미만이어야 합니다.
    Memo.assign(N + 1, {});
    // N턴이 끝난 후, 밥이 이기는 합계 구간은 [L, R]
    Memo[N] = {{L, R}};

    for (int i = N - 1; i >= 0; --i) {
        const int64 CardA = arr[i][0];
        const int64 CardB = arr[i][1];
        const int64 CardC = arr[i][2];

        const auto& NextWinningIntervals = Memo[i + 1];
        auto ShiftedA = ShiftIntervals(NextWinningIntervals, CardA);
        auto ShiftedB = ShiftIntervals(NextWinningIntervals, CardB);
        auto ShiftedC = ShiftIntervals(NextWinningIntervals, CardC);
        
        auto WinIfCardCBanned = UnionIntervals(ShiftedA, ShiftedB);
        auto WinIfCardBBanned = UnionIntervals(ShiftedA, ShiftedC);
        auto WinIfCardABanned = UnionIntervals(ShiftedB, ShiftedC);
        
        // Bob이 i턴에 필승하려면, Alice의 모든 밴에 대해 이길 수 있어야 함.
        // 즉, 세 시나리오의 필승 구간의 교집합
        auto Temp = IntersectIntervals(WinIfCardABanned, WinIfCardBBanned);
        Memo[i] = IntersectIntervals(Temp, WinIfCardCBanned);
    }
}

bool is_alice_win() {

    // 이 함수는 alice_init 이후에 딱 한번 호출됩니다. 
    // 앨리스가 승리할 수 있으면 true, 아니면 false를 return해야 합니다.
    // 정답과 다른 값을 return하면 오답으로 판정됩니다.
    return !IsInIntervals(0, Memo[0]);
}

int alice_ban(int turn, long long S) { //turn은 0-base로 들어옵니다.

    // is_alice_win()에서 true를 return하면 호출되는 함수이며, 정확히 N번 호출되는 함수입니다.
    // 매 호출시 현재 진행중인 턴수와 S값이 주어집니다. 이번 턴에 앨리스가 밴할 인덱스를 return해야 합니다.
    // main함수에서는 alice_ban과 bob_pick함수가 서로 번갈아가면서 실행됩니다. 
    // turn은 0-base로 들어옵니다. 즉 turn = [0..N-1]이 순차적으로 들어옵니다.
    // 즉 현재 밴한 결과는 다음 bob_pick 함수 호출때 영향을 미치며 다음 alice_ban 함수에도 연쇄적으로 영향을 끼칩니다.
    // indx는 0-base입니다. 즉 [0..2]사이의 int를 return해야합니다.
    // 그 외의 값을 return할 시 채점 결과는 오답으로 판정되고 프로그램을 즉시 종료합니다.
    // 최종 S값이 [L..R]사이에 들어오면 오답으로 판정됩니다, 들어오지 않는다면 정답으로 판정됩니다.
    const auto& next_winning_intervals = Memo[turn + 1];
    int64 CardA = arr[turn][0];
    int64 CardB = arr[turn][1];
    int64 CardC = arr[turn][2];

    bool BobCanWinIfCardCBanned = IsInIntervals(S + CardA, next_winning_intervals) || IsInIntervals(S + CardB, next_winning_intervals);
    if (!BobCanWinIfCardCBanned) {
        return 2;
    }

    bool BobCanWinIfBBanned = IsInIntervals(S + CardA, next_winning_intervals) || IsInIntervals(S + CardC, next_winning_intervals);
    if (!BobCanWinIfBBanned) {
        return 1;
    }
    
    return 0;
}
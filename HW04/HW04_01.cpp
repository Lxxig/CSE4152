//#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

struct Coordinate
{
    long long X, Y;
};

long long ask(long long y, long long x) {
    cout << '?' << ' ' << y << ' ' << x << endl;
    long long ret;
    cin >> ret;
    return ret;
}

int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    // write your code here
    int BallsFound = 0;
    long long W = 10000000;
    
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> Distribution(0, W - 1);

    while (BallsFound < N)
    {
        Coordinate RandomPoint;
        RandomPoint.Y = Distribution(rng);
        RandomPoint.X = Distribution(rng);
        
        long long Distance1Square = ask(RandomPoint.Y, RandomPoint.X);
        
        // 만약 거리가 0이면, 마스터볼을 찾은 것임.
        if (Distance1Square == 0)
        {
            ++BallsFound;
            continue;
        }
        
        Coordinate NeighborPoint;
        NeighborPoint.X = (RandomPoint.X == W - 1) ? RandomPoint.X - 1 : RandomPoint.X + 1;
        NeighborPoint.Y = (RandomPoint.Y == W - 1) ? RandomPoint.Y - 1 : RandomPoint.Y + 1;
        
        long long Distance2Square = ask(RandomPoint.Y, NeighborPoint.X);
        long long Distance3Square = ask(NeighborPoint.Y, RandomPoint.X);

        Coordinate Distance;
        Distance.X = NeighborPoint.X - RandomPoint.X;
        Distance.Y = NeighborPoint.Y - RandomPoint.Y;

        // TODO: 연립 방정식을 풀어 마스터볼의 상대 좌표 RelativeCoordinate를 구해야함.
        Coordinate Numerator, Denominator;
        Numerator.X  = Distance1Square - Distance2Square + (Distance.X * Distance.X);
        Denominator.X = 2 * Distance.X;

        Numerator.Y = Distance1Square - Distance3Square + (Distance.Y * Distance.Y);
        Denominator.Y = 2 * Distance.Y;
        
        // 만약 계산된 좌표가 정수가 아니라면, 3개의 쿼리가 서로 다른 마스터볼을
        // 참조했을 가능성 높음, 즉, 이 시도는 실패이므로 다른 임의의 점에서 다시 시작해야함.
        if (Numerator.X  % Denominator.X != 0 || Numerator.Y % Denominator.Y != 0)
        {
            continue;
        }

        Coordinate RelativeCoordinate;
        RelativeCoordinate.X = Numerator.X  / Denominator.X;
        RelativeCoordinate.Y = Numerator.Y / Denominator.Y;

        Coordinate AbsoluteCoordinate;
        AbsoluteCoordinate.Y = RandomPoint.Y + RelativeCoordinate.Y;
        AbsoluteCoordinate.X = RandomPoint.X + RelativeCoordinate.X;
        
        if (AbsoluteCoordinate.Y >= 0 && AbsoluteCoordinate.Y < W && AbsoluteCoordinate.X >= 0 && AbsoluteCoordinate.X < W)
        {
            if (ask(AbsoluteCoordinate.Y, AbsoluteCoordinate.X) == 0)
            {
                BallsFound++;
            }
        }
    }

    return 0;
}

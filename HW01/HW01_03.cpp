#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

bool IsMinCalculation(vector<int>& Powers, int Target, int MaxDepth)
{
    if(static_cast<int>(Powers.size()) > MaxDepth)
    {
        return false;
    }

    int CurrentMaxValue = Powers.back();
    if(CurrentMaxValue == Target)
    {
        return true;
    }

    // 남은 횟수로는 Target에 도달할 수 없을 때는 굳이 더 할 필요 없음.
    int RemainingDepth = MaxDepth - static_cast<int>(Powers.size());
    if(CurrentMaxValue * (1 << RemainingDepth) < Target)
    {
        return false;
    }

    for(int i = static_cast<int>(Powers.size()) - 1; i >= 0; --i)
    {
        for(int j = i; j >= 0; --j)
        {
            int NextValue = Powers[i] + Powers[j];

            if(NextValue <= Target && NextValue > CurrentMaxValue)
            {
                Powers.push_back(NextValue);
                
                if(IsMinCalculation(Powers, Target, MaxDepth))
                {
                    return true;
                }

                Powers.pop_back();
            }
        }
    }

    return false;
}

vector<int> min_multiplications(int n) {
    vector<int> powers;

    //TODO : complete min multiplication
    if(n == 1)
    {
        powers.push_back(1);
        return powers;
    }

    for(int Depth = floor(log2(n)); ; ++Depth)
    {
        powers.clear();
        powers.push_back(1);

        if(IsMinCalculation(powers, n, Depth + 1))
        {
            return powers;
        }
    }
}

int main(){

    int n;
    cin >> n;

    
    vector<int> steps = min_multiplications(n);
    cout << steps.size() - 1 << " ";
    for (int step : steps) {
        cout << step << " ";
    }

    return 0;
}
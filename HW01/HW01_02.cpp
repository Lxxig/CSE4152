#include <iostream>

int PrimeFactorization(int N)
{
    // TODO: N이 0이나 1일 때도 다로 처리해야하나?
    
    int Operations = 0;
    
    for (int i = 2; i * i <= N; ++i)
    {
        while (N % i == 0)
        {
            Operations += i;
            N /= i;
        }
    }

    // N이 소인수인 경우.
    if (N >= 2)
    {
        return N;
    }

    return Operations;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;

    std::cout << PrimeFactorization(N) << "\n";

    return 0;
}
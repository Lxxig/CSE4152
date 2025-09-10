#include <iostream>

int PrimeFactorization(int N)
{
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
        return N + Operations;
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
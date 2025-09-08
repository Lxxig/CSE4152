#include <iostream>

using int64 = long long;

int64 Power(int64 Base, int64 Exponent)
{
    int64 Result = 1;
    
    while (Exponent > 0)
    {
        if (Exponent % 2 == 1)
        {
            Result *= Base;
        }

        Base = Base * Base;
        Exponent /= 2;
    }

    return Result;
}

int main()
{
    int64 Base, Exponent;

    std::cin >> Base >> Exponent;
    std::cout << Power(Base, Exponent) << "\n";
    
    return 0;
}
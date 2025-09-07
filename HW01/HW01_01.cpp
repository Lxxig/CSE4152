#include <iostream>

static bool IsValid(int& OutValue, int InValueA, int InValueB)
{
    if (OutValue == 0 or OutValue == 1)
    {
        return true;
    }
    else
    {
        OutValue = -1;
        return false;
    }
}

/**
 * @brief Asks person A if they know person B.
 * @param a The number of person A.
 * @param b The number of person B.
 * @return true if A knows B, otherwise returns false.
 */
bool ask_a_to_know_b(int a, int b)
{
    int Input;
    std::cout << a << " knows " << b << " ? ";
    std::cin >> Input;
    if (IsValid(Input, a, b))
    {
        return Input;
    }

    return Input;
}


/**
 * @brief Verifies if person x is a celebrity.
 * @param x The number of the person to verify, or -1 if there is no celebrity.
 * @return true if the answer is correct, otherwise returns false.
 */
bool answer(int x)
{
    if (x == -1)
    {
        std::cout << "No celebrity" << std::endl;
        return false;
    }

    std::cout << "Celebrity is " << x << std::endl;
    return true;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    // TODO: write your logic here!
    // You can use the functions `ask_a_to_know_b` and `answer`.
    // Any invocation of print functions rather than `ask_a_to_know_b`
    // and `answer` will result in 0 points for this question.

    int Candidate = 1;
    for (int i = 2; i <= n; i++)
    {
        if (ask_a_to_know_b(Candidate, i))
        {
            Candidate = i;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (Candidate == i) continue;

        if (ask_a_to_know_b(Candidate, i))
        {
            Candidate = -1;
            break;
        }

        if (!ask_a_to_know_b(i, Candidate))
        {
            Candidate = -1;
            break;
        }
    }

    answer(Candidate);

    return 0;
}
#include <iostream>
#include <vector>

using int64 = long long;

int64 GetMaxSubsequenceSum(const std::vector<int>& Sequence)
{
	int64 MaxSubsequenceSum = 0;
	int64 CurrentSubsequenceSum = 0;

	for (int64 N : Sequence)
	{
		CurrentSubsequenceSum += N;

		if (CurrentSubsequenceSum < 0)
		{
			CurrentSubsequenceSum = 0;
		}

		if (CurrentSubsequenceSum > MaxSubsequenceSum)
		{
			MaxSubsequenceSum = CurrentSubsequenceSum;
		}
	}

	return MaxSubsequenceSum;
}

int main()
{
	int SequenceSize;
	std::cin >> SequenceSize;

	std::vector<int> Sequence(SequenceSize);

	for (int i = 0; i < SequenceSize; ++i)
	{
		std::cin >> Sequence[i];
	}

	std::cout << GetMaxSubsequenceSum(Sequence) << "\n";
}
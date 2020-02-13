#include <fstream>
#include <iostream>
using namespace std;


long long Merge(int *sorting, int left, int middle, int right)
{
	int i = 0, j = 0, k = 0, *L, *R;
	long long counter = 0;
	L = new int[middle - left + 1];
	R = new int[right - middle];
	for (i = 0; i < middle - left + 1; i++)
	{
		L[i] = sorting[left + i];
	}
	for (i = 0; i < right - middle; i++)
	{
		R[i] = sorting[middle + 1 + i];
	}
	i = 0;
	while ((j < middle - left + 1) && (k < right - middle))
	{
		if (L[j] <= R[k])
		{
			sorting[left + i] = L[j];
			j++;
			i++;
		}
		else
		{
			sorting[left + i] = R[k];
			k++;
			counter = counter + middle - left + 1 - j;
			i++;
		}

	}
	while (j < (middle - left + 1))
	{
		sorting[left + i] = L[j];
		i++;
		j++;
	}
	while (k < (right - middle))
	{
		sorting[left + i] = R[k];
		i++;
		k++;
	}
	delete[] L;
	delete[] R;
	return counter;
}

long long Merge_sort(int *sorting, int left, int right)
{
	if (right - left < 1)
	{
		return 0;
	}
	else
	{
		int middle = (left + right) / 2;
		return Merge_sort(sorting, left, middle) + Merge_sort(sorting, middle + 1, right) + Merge(sorting, left, middle, right);
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("inversions.in", std::ios::in);
	output.open("inversions.out", std::ios::out);
	
	int* numbers;
	int n;
	long long i;
	long long result;
	input >> n;
	numbers = new int[n];
	
	for (i = 0; i < n; i++)
	{
		input >> numbers[i];
	}
	result = Merge_sort(numbers, 0, n - 1);
	output << result << endl;
	delete[] numbers;
	input.close();
	output.close();
	return 0;

}
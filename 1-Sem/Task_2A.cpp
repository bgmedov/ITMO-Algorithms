#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

void Merge(int *sorting, int left, int middle, int right)
{
	int i = 0, j = 0, k = 0, *L, *R;
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
		while ((j < middle - left + 1)&&(k < right - middle))
		{
			if (L[j] <= R[k])
			{
				sorting[left + i] = L[j];
					j++;
			}
			else
			{
				sorting[left + i] = R[k];
					k++;
			}
			i++;
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
}

void Merge_sort(int *sorting, int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		Merge_sort(sorting, left, middle);
		Merge_sort(sorting, middle + 1, right);
		Merge(sorting, left, middle, right);
	}
}


int main()
{
	ifstream input;
	ofstream output;
	input.open("sort.in", std::ios::in);
	output.open("sort.out", std::ios::out);
	int n, *array, i;
	input >> n;
	array = new int[n];
	for (i = 0; i < n; i++)
		input >> array[i];
	Merge_sort(&array[0], 0, n-1);
	for (i = 0; i < n; i++)
		output << array[i] << ' ';
	output << '\n';

	delete[] array;
	input.close();
	output.close();
	return 0;

}
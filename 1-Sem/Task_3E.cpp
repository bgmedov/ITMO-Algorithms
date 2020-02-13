#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int m;
int n;


void Merge(string* sorting, int left, int middle, int right, int position)
{
	int i = 0, j = 0, k = 0;
	string *L, *R;
	L = new string[middle - left + 1];
	for (i = 0; i < middle - left + 1; i++)
	{

		L[i] = sorting[left + i];

	}
	R = new string[right - middle];
	for (i = 0; i < right - middle; i++)
	{

		R[i] = sorting[middle + 1 + i];

	}
	i = 0;
	while ((j < middle - left + 1) && (k < right - middle))
	{
		if (L[j][position] <= R[k][position])
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

void Merge_sort(string* sorting, int left, int right, int position)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		Merge_sort(sorting, left, middle, position);
		Merge_sort(sorting, middle + 1, right, position);
		Merge(sorting, left, middle, right, position);
	}
}



int main()
{
	ifstream input;
	ofstream output;
	input.open("radixsort.in", ios_base::in);
	output.open("radixsort.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int k;
	input >> n >> m >> k;
	string *lines = new string[n];
	char* buffer = new char[m + 1];
	for (int i = 0; i < n; i++) {
		input >> buffer;
		lines[i] = buffer;
	}
	for (int i = m - 1; i >= m - k; i--)
	{
		Merge_sort(lines, 0, n - 1, i);
		/*for (int i = 0; i < n; i++) {
			cout << lines[i] << '\n';
		}
		cout << "======" << '\n';*/
	}
	for (int i = 0; i < n; i++) {
		for (int z = 0; z < m; z++)
			buffer[z] = lines[i][z];
		output << buffer << '\n';
	}

	input.close();
	output.close();
	return 0;
}
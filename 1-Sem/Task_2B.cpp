#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Merge(string **sorting, int left, int middle, int right)
{
	int i = 0, j = 0, k = 0;
	string **L, **R;
	L = new string*[middle - left + 1];
	for (i = 0; i < middle - left + 1; i++)
	{
		L[i] = new string[2];
		L[i][0] = sorting[left + i][0];
		L[i][1] = sorting[left + i][1];
	}
	R = new string*[right - middle];
	for (i = 0; i < right - middle; i++)
	{
		R[i] = new string[2];
		R[i][0] = sorting[middle + 1 + i][0];
		R[i][1] = sorting[middle + 1 + i][1];
	}
		i = 0; 
		while ((j < middle - left + 1)&&(k < right - middle))
		{
			if (L[j][0] <= R[k][0])
			{
				sorting[left + i][0] = L[j][0];
				sorting[left + i][1] = L[j][1];
					j++;
			}
			else
			{
				sorting[left + i][0] = R[k][0];
				sorting[left + i][1] = R[k][1];
					k++;
			}
			i++;
		}
		while (j < (middle - left + 1))
		{
			sorting[left + i][0] = L[j][0];
			sorting[left + i][1] = L[j][1];
			i++;
			j++;
		}
		while (k < (right - middle))
		{
			sorting[left + i][0] = R[k][0];
			sorting[left + i][1] = R[k][1];
			i++;
			k++;
		}
	delete[] L;
	delete[] R;
}

void Merge_sort(string **sorting, int left, int right)
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
	input.open("race.in", std::ios::in);
	output.open("race.out", std::ios::out);
	string** runners;
	

	int n, i;
	input >> n;

	runners = new string*[n];
	for (i = 0; i < n; i++)
		runners[i] = new string[2];
	for (i = 0; i < n; i++)
		input >> runners[i][0] >> runners[i][1];

	Merge_sort(&*runners, 0, n-1);

	string current_country = runners[0][0];
	output << "=== " << runners[0][0] << " ===" << '\n';
	for (i = 0; i < n; i++)
	{
		if (current_country == runners[i][0])
			output << runners[i][1] << '\n';
		else
		{
			output << "=== " << runners[i][0] << " ===" << '\n';
			current_country = runners[i][0];
			output << runners[i][1] << '\n';
		}
		
	}
	for (i = 0; i < n; i++)
		delete[] runners[i];
	input.close();
	output.close();
	return 0;

}
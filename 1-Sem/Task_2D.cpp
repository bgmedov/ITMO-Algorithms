#include <iostream>
#include <fstream>
using namespace std;

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("antiqs.in");
	output.open("antiqs.out");
	int n, i, *numbers;
	input >> n;
	numbers = new int[n];
	for (i = 1; i <= n; i++)
		numbers[i-1] = i;
	for (i = 2; i < n; i++)
		swap(&numbers[i], &numbers[i/2]);
	for (i = 0; i < n; i++)
		output << numbers[i] << ' ';
	output << '\n';

	delete[] numbers;
	input.close();
	output.close();
	return 0;
}
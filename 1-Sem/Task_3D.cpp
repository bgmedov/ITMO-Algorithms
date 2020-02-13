#include <iostream>
#include <fstream>
using namespace std;

void Sift_down(int* , int , int);
void pyramid_search(int* array, int n) {
	int size = n;
	for (int i = size / 2; i >= 0; i--)
	{
		Sift_down(array, i, size);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(array[0], array[i]);
		Sift_down(array, 0, i);
	}
}

void Sift_down(int* input, int i, int size)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int ind = 0;
	if ((left < size) && (input[i] < input[left]))
	{
		ind = left;
	}
	else
	{
		ind = i;
	}
	if ((right < size) && (input[right] > input[ind]))
		ind = right;
	if (ind != i)
	{
		swap(input[i], input[ind]);
		Sift_down(input, ind, size);
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("sort.in", ios_base::in);
	output.open("sort.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	input >> n;
	int *array = new int[n];
	for (int i = 0; i < n; i++)
	{
		input >> array[i];
	}
	pyramid_search(array, n);
	for (int i = 0; i < n; i++)
	{
		output << array[i] << ' ';
	}
	output << '\n';
	delete(array);
	input.close();
	output.close();
	return 0;
}
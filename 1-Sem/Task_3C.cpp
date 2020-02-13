#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	ifstream input;
	ofstream output;
	input.open("isheap.in", ios_base::in);
	output.open("isheap.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	bool result = true;
	input >> n;
	int* array = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		input >> array[i];
	}
	for (int i = 0; i < n/2; i++)
	{
		if (((2*i + 1 < n)&&(array[i] > array[2 * i + 1])) || ((2*i + 2 < n)&&(array[i] > array[2 * i + 2]))) {
			result = false;
		}
	}
	if (result)
	{
		output << "YES" << '\n';
	}
	else
	{
		output << "NO" << '\n';
	}

	input.close();
	output.close();
	return 0;
}
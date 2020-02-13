#include <iostream>
#include <fstream>
using namespace std;

int binary_search(int* input, int left, int right, int n, bool type_of_search) {
	int right_end = right;
	int left_end = left;
	while (left < right - 1)
	{
		int middle = (right + left) / 2;
		if ((type_of_search) ? (input[middle] <= n) : (input[middle] < n))
		{
			left = middle;
		}
		else
			right = middle;
	}
	if (type_of_search ? input[right - 1] == n : input[right] == n)
	{
		return type_of_search ? right - 1: right;
	}
	return -1;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("binsearch.in", ios_base::in);
	output.open("binsearch.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	input >> n;
	int *array = new int[n];
	for (int i = 0; i < n; i++)
	{
		input >> array[i];
	}
	input >> m;
	int *requests = new int[m];
	for (int i = 0; i < m; i++)
	{
		input >> requests[i];
	}
	int first_enter;
	int last_enter;
	for (int i = 0; i < m; i++) {
		first_enter = binary_search(array, -1, n, requests[i], 0);
		last_enter = binary_search(array, -1, n, requests[i], 1);
		last_enter = (last_enter == -1) ? -1 : last_enter + 1;
		first_enter = (first_enter == -1) ? -1 : first_enter + 1;
		output << first_enter << ' ' << last_enter << '\n';
	}


	input.close();
	output.close();
	delete (array);
	delete (requests);
	return 0;
}
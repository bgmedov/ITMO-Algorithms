#include <iostream>
#include <fstream>
using namespace std;

int Search(int* search, int left, int right, int k)
{
	int i, j, x;
	while (left < right)
	{
		x = search[k];
		i = left;
		j = right;
		do
		{
			while (search[i] < x)
				i++;
			while (search[j] > x)
				j--;
			if (i <= j)
			{
				int buffer = search[i];
				search[i] = search[j];
				search[j] = buffer;
				i++;
				j--;
			}
		} while (i <= j);
		if (j < k)
			left = i;
		if (i > k)
			right = j;
		
	} 
	return search[k];

}

int main()
{
	ifstream input;
	ofstream output;
	input.open("kth.in", ios_base::in);
	output.open("kth.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int k, n, result;
	int	A, B, C, *elements;
	input >> n >> k >> A >> B >> C; 
	elements = new int[n];
	input >> elements[0] >> elements[1];
	for (int i = 2; i < n; i++)
	{
		elements[i] = A * elements[i - 2] + B * elements[i - 1] + C;
	}
	result = Search(elements, 0, n-1, k - 1);
	output << result << '\n';
	delete[] elements;
	input.close();
	output.close();
	return 0;
}
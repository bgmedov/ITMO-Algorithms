
#include <fstream>
using namespace std;

int main()
{
	ofstream output;
	ifstream input;
	output.open("smallsort.out", ios::out);
	input.open("smallsort.in");

	const int MAX_SIZE = 10000;
	int numbers[MAX_SIZE] = {}, i, n, key, j;

	input >> n;
	input >> numbers[0];
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		input >> key;
		numbers[i] = key;
		while((key < numbers[j]) && (j >= 0))
		{
			numbers[j + 1] = numbers[j];
			j--;
		}
		numbers[j + 1] = key;
	}
	for (i = 0; i < n; i++)
		output << numbers[i] << ' ';
	output << endl;

	output.close();
	input.close();
	return 0;
}

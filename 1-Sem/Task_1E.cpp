
#include <fstream>
using namespace std;

int main()
{
	ofstream output;
	ifstream input;
	output.open("sortland.out", ios::out);
	input.open("sortland.in");

	const int MAX_SIZE = 10000;
	int  i, n, j, index[MAX_SIZE] = {};
	float numbers[MAX_SIZE] = {}, key;

	input >> n;
	input >> numbers[0];
	index[0] = 1;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		input >> key;
		numbers[i] = key;
		index[i] = i + 1;
		while((key < numbers[j]) && (j >= 0))
		{
			index[j + 1] = index[j];
			numbers[j + 1] = numbers[j];
			j--;
		}
		index[j + 1] = i + 1;
		numbers[j + 1] = key;
	}
	//for (i = 0; i < n; i++)
		//output << numbers[i] << ' ';
	output << index[0] << ' ' << index[(n-1)/2] << ' ' << index[n-1] << endl;

	output.close();
	input.close();
	return 0;
}

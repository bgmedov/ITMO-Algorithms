
#include <fstream>
using namespace std;

int main()
{
	ofstream output;
	ifstream input;
	output.open("turtle.out", ios::out);
	input.open("turtle.in");

	const int MAX_SIZE = 1001;
	int h, w, i, j, line[MAX_SIZE][2] = {}, parity = 0, k = 0;

	input >> h >> w;
	for (i = 0; i < h; i++)
	{
		parity = i % 2;
		for (j = w ; j > 0; j--)
			input >> line[j][parity];
		if (i == 0)
		{
			for (k = 1; k <= w; k++)
				line[k][0] += line[k - 1][0];
		}
		else
			for (k = 1; k <= w; k++)
			{
				if (line[k][1 - parity] > line[k - 1][parity])
					line[k][parity] += line[k][1 - parity];
				else
					line[k][parity] += line[k - 1][parity];
			}
			
	}
	output << line[w][parity];

	output.close();
	input.close();
	return 0;
}

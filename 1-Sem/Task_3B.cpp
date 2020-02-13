#include <iostream>
#include <fstream>
using namespace std;

double* lightbulbs;
int n;

bool is_valid(double second_bulb) {
	lightbulbs[1] = second_bulb;
	for (int i = 2; i < n; i++)
	{
		lightbulbs[i] = 2 * lightbulbs[i - 1] - lightbulbs[i - 2] + 2;
		if (lightbulbs[i] < 0)
			return false;
	}
	return true;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("garland.in", ios_base::in);
	output.open("garland.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	input >> n;
	lightbulbs = new double[n];
	input >> lightbulbs[0];
	double right = 1000.0;
	double left = 0.0;
	while (right - left > 0.000000005)
	{
		double middle = (right + left) / 2.0;

		if (is_valid(middle))
		{
			right = middle;
		}
		else
		{
			left = middle;
		}
	}
	double result = lightbulbs[n - 1];
	output.precision(2);
	output << fixed << result << '\n';
	input.close();
	output.close();
	delete(lightbulbs);
	return 0;
}
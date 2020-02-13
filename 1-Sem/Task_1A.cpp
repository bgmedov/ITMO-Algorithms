#include <fstream>
using namespace std;

int main()
{
	ofstream output;
	ifstream input;
	output.open("aplusb.out", ios::out);
	input.open("aplusb.in");

	long int a, b;
	input >> a >> b;
	output << a + b << endl;
	output.close();
	input.close();
}

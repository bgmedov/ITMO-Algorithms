
#include <fstream>
using namespace std;

int main()
{
	ofstream output;
	ifstream input;
	output.open("aplusbb.out", ios::out);
	input.open("aplusbb.in");

	long long a, b;
	input >> a >> b;
	output << a + b*b << endl;
	output.close();
	input.close();
}

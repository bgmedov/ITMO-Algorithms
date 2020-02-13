#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int hash_function (long input){
	return (input + 1000000000) % 1000000;
}
vector<long> hash_table[1000001];

int main()
{
	ifstream input;
	ofstream output;
	input.open("set.in", ios_base::in);
	output.open("set.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true)
	{
		bool flag = false;
		string action;
		long operand;
		input >> action;
		input >> operand;
		if (action == "insert")
		{
			for (int i = 0; i < size(hash_table[hash_function(operand)]); i++)
				if (hash_table[hash_function(operand)][i] == operand)
					flag = true;
			if (!flag)
			{
				flag = false;
				hash_table[hash_function(operand)].push_back(operand);
			}
		}
		else
		{
			if (action == "delete")
			{
				for (int i = 0; i < size(hash_table[hash_function(operand)]); i++)
					if (hash_table[hash_function(operand)][i] == operand)
					{
						hash_table[hash_function(operand)].erase(hash_table[hash_function(operand)].begin() + i);
						break;
					}
			}
			else
				if (action == "exists")
				{
					for (int i = 0; i < size(hash_table[hash_function(operand)]); i++)
						if (hash_table[hash_function(operand)][i] == operand)
							flag = true;
					if (flag)
					{
						flag = false;
						output << "true" << '\n';
					}
					else
					{
						output << "false" << '\n';
					}
				}
		}
		if (input.eof())
			break;
	}
	
	input.close();
	output.close();
	return 0;
}


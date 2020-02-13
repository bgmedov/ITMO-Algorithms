#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int hash_function(string input) {
	unsigned int result = 0;
	int hash_helper1 = 1337;
	int hash_helper2 = 55;
	for (int i = 0; i < size(input); i++)
	{
		result += input.at(i) - 'a';
		result = result % hash_helper1;
		result *= hash_helper2;
		hash_helper2++;
		hash_helper1++;
	}
	return result % 100003;
}
vector<string> keys[100008];
vector<string> elements[100008];

int main()
{
	ifstream input;
	ofstream output;
	input.open("map.in", ios_base::in);
	output.open("map.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true)
	{
		bool key_flag = false;
		bool element_flag = false;
		int element_number;
		string action;
		string key;
		string element;
		input >> action;
		input >> key;
		if (action == "put")
		{
			input >> element;
			for (int i = 0; i < size(keys[hash_function(key)]); i++)
				if (keys[hash_function(key)][i] == key)
				{
					key_flag = true;
					if (elements[hash_function(key)][i] == element)
						element_flag = true;
					element_number = i;
					break;
				}
			if ((!key_flag && !element_flag))
			{
				elements[hash_function(key)].push_back(element);
				keys[hash_function(key)].push_back(key);
			}
			else
			{
				if (key_flag && !element_flag)
					elements[hash_function(key)][element_number] = element;
			}
		}
		else
		{
			if (action == "delete")
			{
				for (int i = 0; i < size(keys[hash_function(key)]); i++)
					if (keys[hash_function(key)][i] == key)
					{
						keys[hash_function(key)].erase(keys[hash_function(key)].begin() + i);
						elements[hash_function(key)].erase(elements[hash_function(key)].begin() + i);
						break;
					}
			}
			else
				if (action == "get")
				{
					for (int i = 0; i < size(keys[hash_function(key)]); i++)
						if (keys[hash_function(key)][i] == key)
						{
							key_flag = true;
							element_number = i;
							break;
						}
					if (key_flag)
					{
						key_flag = false;
						output << elements[hash_function(key)][element_number] << '\n';
					}
					else
					{
						output << "none" << '\n';
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


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const int Hash_Size = 220;

int hash_function(string input) {
	unsigned int result = 0;
	int hash_helper1 = 1337;
	int hash_helper2 = 55;
	for (int i = 0; i < size(input); i++)
	{
		result += input.at(i) - 'a';
		result = result % hash_helper1;
		result *= hash_helper2;
	}
	return result % (Hash_Size - 1);
}

struct A_Hash_Node {
	string A;
	vector<string> B_Hash_Node[Hash_Size];
};

vector<A_Hash_Node> Hash_Table[Hash_Size];
int main()
{
	ifstream input;
	ofstream output;
	input.open("multimap.in", ios_base::in);
	output.open("multimap.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true)
	{
		bool A_Key_flag = false;
		bool B_Key_flag = false;
		int element_number;
		int element_count = 0;
		int hash_result_A;
		int hash_result_B;
		vector<int> elements_positions;
		string action;
		string first_element;
		string second_element;
		string one_pair;
		input >> action;
		input >> first_element;
		hash_result_A = hash_function(first_element);
		if (action == "put")
		{
			input >> second_element;
			hash_result_B = hash_function(second_element);
			for (int i = 0; i < size(Hash_Table[hash_result_A]); i++)
			{
				if (Hash_Table[hash_result_A][i].A == first_element)
				{
					A_Key_flag = true;
					for (int j = 0; j < size(Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B]); j++)
						if (Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B][j] == second_element)
						{
							B_Key_flag = true;
							break;
						}
					element_number = i;
					break;

				}
			}
			if (!A_Key_flag && !B_Key_flag)
			{
				Hash_Table[hash_result_A].push_back({first_element});
				Hash_Table[hash_result_A].back().B_Hash_Node[hash_result_B].push_back(second_element);
			}
			else
				if (!B_Key_flag && A_Key_flag)
				{
					Hash_Table[hash_result_A][element_number].B_Hash_Node[hash_result_B].push_back(second_element);
				}

		}
		else
			if (action == "delete")
			{
				input >> second_element;
				hash_result_B = hash_function(second_element);
				for (int i = 0; i < size(Hash_Table[hash_result_A]); i++)
				{
					if (Hash_Table[hash_result_A][i].A == first_element)
					{
						A_Key_flag = true;
						for (int j = 0; j < size(Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B]); j++)
							if (Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B][j] == second_element)
							{
								Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B].erase(Hash_Table[hash_result_A][i].B_Hash_Node[hash_result_B].begin() + j);
								B_Key_flag = true;
								break;

							}
						for (int j = 0; j < Hash_Size; j++)
						{
							if (size(Hash_Table[hash_result_A][i].B_Hash_Node[j]) > 0)
							{
								element_count++;
								break;
							}
						}
						if (element_count == 0)
							Hash_Table[hash_result_A].erase(Hash_Table[hash_result_A].begin() + i);
						break;

					}
				}
			}
			else
			{
				if (action == "get")
				{
					vector<string> output_vector;
					for (int i = 0; i < size(Hash_Table[hash_result_A]); i++)
					{
						if (Hash_Table[hash_result_A][i].A == first_element)
						{
							for (int j = 0; j < Hash_Size; j++)
								if (size(Hash_Table[hash_result_A][i].B_Hash_Node[j]) > 0)
									for (int k = 0; k < size(Hash_Table[hash_result_A][i].B_Hash_Node[j]); k++)
										output_vector.push_back(Hash_Table[hash_result_A][i].B_Hash_Node[j][k]);
						}
					}
					output << size(output_vector);
					for (int i = 0; i < size(output_vector); i++)
						output << ' ' << output_vector[i];
					output << '\n';
				}
				else
					if (action == "deleteall")
					{
						for (int i = 0; i < size(Hash_Table[hash_result_A]); i++)
						{
							if (Hash_Table[hash_result_A][i].A == first_element)
							{
								Hash_Table[hash_result_A].erase(Hash_Table[hash_result_A].begin() + i);
								break;
							}
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


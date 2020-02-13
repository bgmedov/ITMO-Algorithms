#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
	string key;
	Node* prev;
	Node* next;
};

struct Hash_Node {
	string key;
	Node* element;
};

Node* last_element = NULL;
Node* first_element = NULL;
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
vector<Hash_Node> Hash_Table[100004];

void Remove(Node* current)
{
	Node* buffer;
	if (current != NULL)
	{
		buffer = current->next;
		if (current->next != NULL) {
			current->next->prev = current->prev;
		}
		else
			last_element = current->prev;
		if (current->prev != NULL)
		{
			current->prev->next = buffer;
		}
		else
			first_element = current->next;
		if (current->next == current->prev)
		{
			first_element = NULL;
			last_element = NULL;
		}
	}
	delete current;
}

Node* Add(string key) {
	if (last_element != NULL) {
		last_element->next = new Node;
		last_element->next->prev = last_element;
		last_element->next->next = NULL;
		last_element->next->key = key;
		last_element = last_element->next;
	}
	else
	{
		last_element = new Node;
		last_element->next = NULL;
		first_element = last_element;
		last_element->prev = NULL;
		last_element->key = key;
	}
	return last_element;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("linkedmap.in", ios_base::in);
	output.open("linkedmap.out", ios_base::out);
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
			for (int i = 0; i < size(Hash_Table[hash_function(key)]); i++)
				if (Hash_Table[hash_function(key)][i].key == key)
				{
					key_flag = true;
					if (Hash_Table[hash_function(key)][i].element->key == element)
						element_flag = true;
					element_number = i;
					break;
				}
			if ((!key_flag && !element_flag))
			{
				Hash_Table[hash_function(key)].push_back({key, Add(element)});
			}
			else
			{
				if (key_flag && !element_flag)
					Hash_Table[hash_function(key)][element_number].element->key = element;
			}
		}
		else
			if (action == "delete")
			{
				for (int i = 0; i < size(Hash_Table[hash_function(key)]); i++)
					if (Hash_Table[hash_function(key)][i].key == key)
					{
						Remove(Hash_Table[hash_function(key)][i].element);
						Hash_Table[hash_function(key)].erase(Hash_Table[hash_function(key)].begin() + i);
						break;
					}
			}
			else
			{
				if (action == "get")
				{
					for (int i = 0; i < size(Hash_Table[hash_function(key)]); i++)
						if (Hash_Table[hash_function(key)][i].key == key)
						{
							key_flag = true;
							element_number = i;
							break;
						}
					if (key_flag)
					{
						key_flag = false;
						output << Hash_Table[hash_function(key)][element_number].element->key << '\n';
					}
					else
					{
						output << "none" << '\n';
					}
				}
				else
					if (action == "prev")
					{
						for (int i = 0; i < size(Hash_Table[hash_function(key)]); i++)
							if (Hash_Table[hash_function(key)][i].key == key)
							{
								key_flag = true;
								element_number = i;
								break;
							}
						if (key_flag && (Hash_Table[hash_function(key)][element_number].element->prev != NULL))
						{
							key_flag = false;
							output << Hash_Table[hash_function(key)][element_number].element->prev->key << '\n';
						}
						else
						{
							output << "none" << '\n';
						}
					}
					else
						if (action == "next")
						{
							for (int i = 0; i < size(Hash_Table[hash_function(key)]); i++)
								if (Hash_Table[hash_function(key)][i].key == key)
								{
									key_flag = true;
									element_number = i;
									break;
								}
							if (key_flag && (Hash_Table[hash_function(key)][element_number].element->next != NULL))
							{
								key_flag = false;
								output << Hash_Table[hash_function(key)][element_number].element->next->key << '\n';
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


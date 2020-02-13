#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Node {
	int key;
	Node* left;
	Node* right;
};
Node* root = NULL;

Node* search(Node* x, int k) {
	if ((x == NULL) || (k == x->key))
		return x;
	if (k < x->key)
		return search(x->left, k);
	else
		return search(x->right, k);
}

Node* new_Node(int x) {
	Node* new_node = new Node;
	new_node->key = x;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Node* Add(Node* v, int x) {
	if (v == NULL)
		return new_Node(x);
	if (v->key < x)
		v->right = Add(v->right, x);
	else
		v->left = Add(v->left, x);
	return v;
}

Node* minimum(Node* x) {
	if (x->left == NULL)
		return x;
	return minimum(x->left);
}
Node* maximum(Node* x) {
	if (x->right == NULL)
		return x;
	return maximum(x->left);
}
Node* Next(int x) {
	Node* current = root;
	Node* successor = NULL;
	while (current != NULL)
	{
		if (current->key > x)
		{
			successor = current;
			current = current->left;
		}
		else
			current = current->right;
	}
	return successor;
}
Node* Prev(int x)
{
	Node* current = root;
	Node* successor = NULL;
	while (current != NULL)
	{
		if (current->key < x)
		{
			successor = current;
			current = current->right;
		}
		else
			current = current->left;
	}
	return successor;
}
Node* remove(Node* start, int z) {
	if (start == NULL)
		return start;
	if (z < start->key)
	{
		start->left = remove(start->left, z);
	}
	else
	{
		if (z > start->key)
			start->right = remove(start->right, z);
		else
			if ((start->left != NULL) && (start->right != NULL))
			{
				start->key = minimum(start->right)->key;
				start->right = remove(start->right, start->key);
			}
			else
				if (start->left != NULL)
					start = start->left;
				else
					if (start->right != NULL)
						start = start->right;
					else
					{
						delete start;
						start = NULL;
					}
	}
	return start;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("bstsimple.in", ios_base::in);
	output.open("bstsimple.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	bool flag = false;
	while (true) {
		string action;
		int operand;
		input >> action;
		input >> operand;
		if (action == "insert")
		{
			if (root != NULL)
			{
				if (search(root, operand) == NULL)
					Add(root, operand);
			}
			else
				root = Add(root, operand);
		}
		else
			if (action == "delete")
				root = remove(root, operand);
			else
				if (action == "exists")
				{
					flag = true;
					Node* result = search(root, operand);
					if (result == NULL)
						output << "false" << '\n';
					else
						output << "true" << '\n';
				}
				else
					if (action == "next")
					{
						flag = true;
						Node* result = Next(operand);
						if (result == NULL)
							output << "none" << '\n';
						else
						{
							int digital_result = result->key;
							output << digital_result << '\n';
						}
					}
					else
						if (action == "prev")
						{
							flag = true;
							Node* result = Prev(operand);
							if (result == NULL)
								output << "none" << '\n';
							else
							{
								int digital_result = result->key;
								output << digital_result << '\n';
							}
						}

		if (input.eof())
			break;
	}
	if (flag)
		output << '\n';
	input.close();
	output.close();
	return 0;
}


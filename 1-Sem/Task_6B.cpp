#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Node {
	int key;
	int left;
	int right;
};
struct Node* tree;
bool is_correct(Node *Node, int number, int max, int min) {
	if ((Node[number].left == 0) && (Node[number].right == 0) && (Node[number].key == 1000000001))
		return true;
	if (Node[number].key <= min)
		return false;
	if (Node[number].key >= max)
		return false;
	return is_correct(Node, Node[number].left, Node[number].key, min) && is_correct(Node, Node[number].right, max, Node[number].key);
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("check.in", ios_base::in);
	output.open("check.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	input >> N;
	tree = new struct Node[N + 1];
	tree[0] = { 1000000001, 0, 0};
	if (N != 0) {
		for (int i = 1; i <= N; i++)
		{
			input >> tree[i].key >> tree[i].left >> tree[i].right;
		}
		bool result = is_correct(&tree[0], 1, 1000000000, -1000000000);
		if (result)
			output << "YES" << '\n';
		else
			output << "NO" << '\n';
	}
	else
	{
		output << "YES" << '\n';
	}
	input.close();
	output.close();
	delete[] tree;
	return 0;
}


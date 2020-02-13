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

int height(Node *Node, int number)
{
	if ((Node[number].left == 0) && (Node[number].right == 0))
		return 1;
	else
	{
		int h1 = 0, h2 = 0;
		if(Node[number].left != 0)
			h1 = height(Node, Node[number].left);
		if (Node[number].right != 0)
			h2 = height(Node, Node[number].right);
		if (h1 > h2)
			return h1 + 1;
		else
			return h2 + 1;
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("height.in", ios_base::in);
	output.open("height.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	input >> N;
	struct Node *tree = new Node[N + 1];
	if (N != 0) {
		for (int i = 1; i <= N; i++)
		{
			input >> tree[i].key >> tree[i].left >> tree[i].right;
		}
		int result = height(&tree[0], 1);
		output << result << '\n';
	}
	else
	{
		output << "0" << '\n';
	}
	input.close();
	output.close();
	delete[] tree;
	return 0;
}


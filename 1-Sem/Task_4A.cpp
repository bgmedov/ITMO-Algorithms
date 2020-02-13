#include <iostream>
#include <fstream>
using namespace std;

struct list {
	list* previous;
	int key;
};

list* last_element = 0;

list* create(list* head, int key)
{
	list* pointer;
	pointer = (list*)malloc(sizeof(list));
	pointer->key = key;
	pointer->previous = head;
	return pointer;
}

void remove(list* head) {
	last_element = head->previous;
	free(head);
}

void stack_push(int value) {
	last_element = create(last_element, value);
}

int stack_pop() {
	int value = last_element->key;
	remove(last_element);
	return value;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("stack.in", ios_base::in);
	output.open("stack.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		int buffer;
		char action;
		input >> action;
		switch (action) {
		case '+':
			input >> buffer;
			stack_push(buffer);
			break;
		case '-':
			buffer = stack_pop();
			output << buffer << '\n';
			break;
		}
	}

	input.close();
	output.close();
	return 0;
}

#include <iostream>
#include <fstream>
using namespace std;

struct list {
	list* previous;
	int key;
	list* next;
};

list* last_element = 0;
list* first_element = 0;

list* create(list* head, int key)
{
	list* pointer;
	pointer = (list*)malloc(sizeof(list));
	pointer->key = key;
	pointer->previous = head;
	pointer->next = 0;
	//last_element->next = pointer;
	return pointer;
}

void remove(list* start) {
	if ((first_element->next != 0)&&(first_element != 0)) {
		first_element->next->previous = 0;
	}
	if (first_element == last_element)
	{
		last_element = 0;
		first_element = 0;
	}
	else
	{
		first_element = first_element->next;
	}
	free(start);
}

void queue_push(int value) {
	list* pointer;
	pointer = create(last_element, value);
	if (last_element != 0)
	{
		last_element->next = pointer;
	}
	last_element = pointer;
	if (first_element == 0)
	{
		first_element = last_element;
	}
}

int queue_pop() {
	int value = first_element->key;
	remove(first_element);
	return value;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("queue.in", ios_base::in);
	output.open("queue.out", ios_base::out);
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
			queue_push(buffer);
			break;
		case '-':
			buffer = queue_pop();
			output << buffer << '\n';
			break;
		}
	}

	input.close();
	output.close();
	return 0;
}

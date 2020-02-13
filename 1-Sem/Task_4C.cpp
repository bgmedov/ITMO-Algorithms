#include <iostream>
#include <fstream>
using namespace std;

enum bracket {
	NOTHING,
	OPEN_SQUARE,
	CLOSE_SQUARE,
	OPEN_ROUND,
	CLOSE_ROUND
};

struct list {
	list* previous;
	enum bracket key;
};

list* last_element = 0;

list* create(list* head, enum bracket key)
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

void stack_push(enum bracket value) {
	last_element = create(last_element, value);
}

enum bracket stack_pop() {
	if (last_element != 0)
	{
		enum bracket value = last_element->key;
		remove(last_element);
		return value;
	}
	else
	{
		return NOTHING;
	}
	
}

void stack_clear()
{
	while(stack_pop() != NOTHING)
	{ }
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("brackets.in", ios_base::in);
	output.open("brackets.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	//input >> n;
	char symbol;
	bool correct = true;
	while (true)
	{	
		symbol = input.get();
		enum bracket previous;
		switch (symbol)
		{
		case '[':
			stack_push(OPEN_SQUARE);
			break;
		case '(':
			stack_push(OPEN_ROUND);
			break;
		case ']':
			if (stack_pop() != OPEN_SQUARE)
				correct = false;
			break;
		case ')':
			if (stack_pop() != OPEN_ROUND)
				correct = false;
			break;
		case '\n':
		case '\r':
			if ((correct)&&(stack_pop() == NOTHING))
				output << "YES" << '\n';
			else
				output << "NO" << '\n';
			correct = true;
			stack_clear();
			break;
		}
		if (input.eof())
			break;
	}

	input.close();
	output.close();
	return 0;
}

#include <iostream>
#include <fstream>
using namespace std;


struct list {
	list* previous;
	long long key;
};

list* last_element = 0;

list* create(list* head, long long key)
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

void stack_push(long long value) {
	last_element = create(last_element, value);
}

long long stack_pop() {
		long long value = last_element->key;
		remove(last_element);
		return value;
}


int main()
{
	ifstream input;
	ofstream output;
	input.open("postfix.in", ios_base::in);
	output.open("postfix.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	//input >> n;
	char symbol;
	long long result;
	long long buffer;
	while (true)
	{	
		symbol = input.get();
		if (symbol == ' ')
			continue;
		if ((symbol >= '0') && (symbol <= '9'))
			stack_push(symbol - '0');
		else
		{
			if (symbol == '+')
			{
				buffer = stack_pop() + stack_pop();
				stack_push(buffer);
			}
			else
			{
				if (symbol == '-')
				{
					buffer = 0 - stack_pop() + stack_pop();
					stack_push(buffer);
				}
				else
				{
					if (symbol == '*')
					{
						buffer = stack_pop() * stack_pop();
						stack_push(buffer);
					}
				}
			}
		}
		if (input.eof())
			break;
	}
	result = stack_pop();
	output << result << '\n';
	input.close();
	output.close();
	return 0;
}

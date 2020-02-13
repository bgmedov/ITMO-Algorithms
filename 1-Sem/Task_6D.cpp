#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct list {
	list* previous;
	unsigned short key;
	list* next;
};

list* last_element = 0;
list* first_element = 0;

list* create(list* head, unsigned short key)
{
	list* pointer;
	pointer = (list*)malloc(sizeof(list));
	pointer->key = key;
	if (pointer != first_element)
		pointer->previous = head;
	else
		pointer->previous = 0;
	pointer->next = 0;
	return pointer;
}

void remove(list* start) {
	if (start != 0)
	{
		if (first_element->next != last_element) {
			if (first_element != last_element) {
				first_element = first_element->next;
				first_element->previous = 0;
				free(start);
			}
			else
			{
				free(start);
				first_element = 0;
				last_element = 0;
			}
		}
		else
		{
			first_element = last_element;
			first_element->previous = 0;
			free(start);
		}
	}
}

void queue_push(unsigned short value) {
	list* pointer;
	pointer = create(last_element, value);
	if (first_element == 0)
	{
		last_element = pointer;
		first_element = last_element;
		return;
	}
	if (last_element != 0)
	{
		last_element->next = pointer;
	}
	last_element = pointer;

}

unsigned short queue_pop() {
	if (first_element != 0) {
		unsigned short value = first_element->key;
		remove(first_element);
		return value;
	}
	else
		return 0;
}

struct command {
	char command_name;
	char operand_1;
	char operand_2;
	string operand_3;
	int number;
};
struct labels {
	string label;
	size_t position;
};
int main()
{
	ifstream input;
	ofstream output;
	input.open("quack.in", ios_base::in);
	output.open("quack.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	vector<command> code;
	vector<labels> labels;
	while (true) {
		string buffer;
		command current_command = {0,0,0, "", 0};
		input >> buffer;
		if (buffer == "")
			break;
		switch (buffer.at(0))
		{
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case 'Q':
				current_command = { buffer.at(0), 0, 0, "", 0};
				code.push_back(current_command);
				break;
			case 'P':
			case 'C':
				current_command.command_name = buffer.at(0);
				if (buffer.size() > 1)
					current_command.operand_1 = buffer.at(1);
				else
					current_command.operand_1 = 0;
				code.push_back(current_command);
				break;
			case '>':
			case '<':
				current_command = { buffer.at(0),  buffer.at(1), 0, "", 0 };
				code.push_back(current_command);
				break;
			case ':':
				current_command = { buffer.at(0), 0, 0, "" , 0};
				current_command.operand_3.append(buffer, 1, buffer.size() - 1);
				labels.push_back({ current_command.operand_3 , code.size()});
				break;
			case 'J':
				current_command = { buffer.at(0), 0, 0, "" , 0};
				current_command.operand_3.append(buffer, 1, buffer.size() - 1);
				code.push_back(current_command);
				break;
			case 'Z':
				current_command = { buffer.at(0), 0, 0, "", 0 };
				current_command.operand_1 = buffer.at(1);
				current_command.operand_3.append(buffer, 2, buffer.size() - 2);
				code.push_back(current_command);
				break;
			case 'G':
			case 'E':
				current_command = { buffer.at(0), 0, 0, "", 0 };
				current_command.operand_1 = buffer.at(1);
				current_command.operand_2 = buffer.at(2);
				current_command.operand_3.append(buffer, 3, buffer.size() - 3);
				code.push_back(current_command);
				break;
			default:
				if ((buffer.at(0) >= '0')&&(buffer.at(0) <= '9'))
				{
					current_command = { 'N', 0, 0, "",  atoi(buffer.c_str()) };
					code.push_back(current_command);
				}
				break;

		}
		if (input.eof())
			break;
	}
	unsigned short registers[26] = {};
	unsigned int i = 0;
	while (i < code.size())
	{
		command current_command = code[i];
		unsigned short buffer;
		unsigned short buffer_a;
		unsigned short buffer_b;
		switch (current_command.command_name) {
			case '+':
				buffer = (queue_pop() + queue_pop()) % 65536;
				queue_push(buffer);
				i++;
				break;
			case '-':
				buffer_a = queue_pop();
				buffer_b = queue_pop();
				buffer = (buffer_a - buffer_b)% 65536;
				queue_push(buffer);
				i++;
				break;
			case '*':
				 buffer = (queue_pop() * queue_pop())% 65536;
				queue_push(buffer);
				i++;
				break;
			case '/':
				buffer_a = queue_pop();
				buffer_b = queue_pop();
				if (buffer_b != 0)
					queue_push((buffer_a / buffer_b)% 65536);
				else
					queue_push(0);
				i++;
				break;
			case '%':
				buffer_a = queue_pop();
				buffer_b = queue_pop();
				if (buffer_b != 0)
					queue_push((buffer_a % buffer_b)% 65536);
				else
					queue_push(0);
				i++;
				break;
			case 'Q':
				i = code.size();
				break;
			case 'P':
				if (current_command.operand_1 == 0)
					buffer = queue_pop();
				else
					buffer = registers[current_command.operand_1 - 'a'];
				output << buffer << '\n';
				i++;
				break;
			case 'C':
				char letter;
				if (current_command.operand_1 == 0)
					buffer = queue_pop() % 256;
				else
					buffer = registers[current_command.operand_1 - 'a']%256;
				letter = buffer;
				output << letter;
				i++;
				break;
			case '>':
				registers[current_command.operand_1 - 'a'] = queue_pop();
				i++;
				break;
			case '<':
				queue_push(registers[current_command.operand_1 - 'a']);
				i++;
				break;
			case 'J':
				for (unsigned int j = 0; j < labels.size(); j++)
				{
					if (labels[j].label == current_command.operand_3)
					{
						i = labels[j].position - 1;
						break;
					}
				}
				i++;
				break;
			case 'Z':
				if (registers[current_command.operand_1 - 'a'] == 0)
				{
					for (unsigned int j = 0; j < labels.size(); j++)
					{
						if (labels[j].label == current_command.operand_3)
						{
							i = labels[j].position - 1;
							break;
						}
					}
				}
					i++;
					break;
			case 'E':
				if (registers[current_command.operand_1 - 'a'] == registers[current_command.operand_2 - 'a'])
				{
					for (unsigned int j = 0; j < labels.size(); j++)
					{
						if (labels[j].label == current_command.operand_3)
						{
							i = labels[j].position - 1;
							break;
						}
					}
				}
				i++;
				break;
			case 'G':
				if (registers[current_command.operand_1 - 'a'] > registers[current_command.operand_2 - 'a'])
				{
					for (unsigned int j = 0; j < labels.size(); j++)
					{
						if (labels[j].label == current_command.operand_3)
						{
							i = labels[j].position - 1;
							break;
						}
					}
				}
				i++;
				break;
			case 'N':
				queue_push(current_command.number % 65536);
				i++;
				break;
		}
	}
	input.close();
	output.close();
	return 0;
}


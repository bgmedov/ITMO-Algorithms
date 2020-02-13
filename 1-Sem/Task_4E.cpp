#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

long long queue[2000000];
long long order[2000000];
long long queue_size = 0;
void swap(long long*, long long*);
void Sift_down(long long i)
{
		long long left = 2 * i + 1;
		long long right = 2 * i + 2;
		long long ind = 0;
		if ((left < queue_size) && (queue[i] > queue[left]))
		{
			ind = left;
		}
		else
		{
			ind = i;
		}
		if ((right < queue_size) && (queue[right] < queue[ind]))
			ind = right;
		if (ind != i) {
			swap(queue[i], queue[ind]);
			swap(order[i], order[ind]);
			Sift_down(ind);
		}
}

int search(long long n) {
	for (int i = 0; i < queue_size; i ++)
	{
		if (order[i] == n)
			return i;
	}
	return -1;
}

void sift_up(long long i){
	while ((i > 0)&&(queue[i] < queue[(i - 1) / 2]))
	{
		swap(queue[i], queue[(i - 1) / 2]);
		swap(order[i], order[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
void swap(long long *a, long long *b) {
	long long *buffer = a;
	a = b;
	b = buffer;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("priorityqueue.in", ios_base::in);
	output.open("priorityqueue.out", ios_base::out);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	char buffer[14];
	long long i = 1;
	long long n;
	while (true)
	{
		input >> buffer;
		if (strcmp(buffer, "push") == 0)
		{
			long long a;
			input >> a;
			queue[queue_size] = a;
			order[queue_size] = i;
			sift_up(queue_size);
			queue_size++;
			i++;
		}
		else
		{
			if (strcmp(buffer, "decrease-key") == 0)
			{
				long long index;
				input >> index;
				long long number = search(index);
				if (number == -1)
					number = 2000000 - 1;
				long long y = 0;
				input >> y;
				queue[number] = y;
				sift_up(number);
				i++;
			}
			else
			{
				if (strcmp(buffer, "extract-min") == 0)
				{
					i++;
					if (queue_size > 0)
					{
						n = queue[0];
						output << n << '\n';
						if (size(queue) > 1) {
							swap(queue[0], queue[queue_size - 1]);
							swap(order[0], order[queue_size - 1]);
						}
						queue_size--;
						if (queue_size > 0)
						{
							Sift_down(0);
						}
					}
					else
					{
						output << '*' << '\n';
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


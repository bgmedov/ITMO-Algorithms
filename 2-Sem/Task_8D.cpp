#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Vertex {
    int connected_component = -1;
    vector<int> connected;
};
struct Node {
    Node* next = NULL;
    Node* previous = NULL;
    int key = -1;
};
class Queue {
private:
    Node* last_element;
    Node* first_element;
    Node* create(Node* head, int key)
    {
        Node* pointer;
        pointer = new Node;
        pointer->key = key;
        pointer->previous = head;
        pointer->next = 0;
        return pointer;
    }
    void remove_q(Node* start) {
        if ((first_element->next != 0) && (first_element != 0)) {
            first_element->next->previous = 0;
        }
        if (first_element == last_element)
        {
            last_element = NULL;
            first_element = NULL;
        }
        else
        {
            first_element = first_element->next;
        }
        delete start;
    }
public:
    Queue() {
        last_element = NULL;
        first_element = NULL;
    }
    ~Queue() {
        
    }

    void push(int value) {
    Node* pointer;
	pointer = create(last_element, value);
	if (last_element != 0)
	{
		last_element->next = pointer;
	}
	last_element = pointer;
	if (first_element == NULL)
	{
		first_element = last_element;
	}
    }
    int pop() {
        int value = first_element->key;
        remove_q(first_element);
        return value;
    }
    bool empty(){
        if (first_element == NULL)
            return true;
        else
            return false;
    }
};

int main()
{
    ifstream input;
    ofstream output;
    input.open("components.in", ios_base::in);
    output.open("components.out", ios_base::out);
    int n, m;
    input >> n >> m;
    Vertex* list = new Vertex[n];
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    for (int i = 0; i < m; i++) {
        int a, b;
        input >> a >> b;
        list[a - 1].connected.push_back(b - 1);
        list[b - 1].connected.push_back(a - 1);
    }
    Queue current_queue;
    int component = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i]){
            continue;
        }
        else {
            current_queue.push(i);
            visited[i] = true;
        }
        while (!current_queue.empty()){
            int current_vertex = current_queue.pop();
            list[current_vertex].connected_component = component;
            for (int j = 0; j < list[current_vertex].connected.size(); j++)
            {
                if (!visited[list[current_vertex].connected[j]]) {
                    current_queue.push(list[current_vertex].connected[j]);

                    visited[list[current_vertex].connected[j]] = true;
                    list[list[current_vertex].connected[j]].connected_component = component;
                }
            }
        }
        component++;
    }
    output << component - 1 << '\n';
    for (int i = 0; i < n; i++) {
        output << list[i].connected_component << ' ';
    }
    input.close();
    output.close();
    return 0;
}


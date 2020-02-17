#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Vertex {
    string Path = "";
    struct  {
        int left = -1;
        int right = -1;
        int up = -1;
        int down = -1;
    };
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
    input.open("input.txt", ios_base::in);
    output.open("output.txt", ios_base::out);
    int n, m;
    input >> n >> m;
    Vertex *list = new Vertex[n * m];
    char** labirinth = new char*[n + 1];
    for (int i = 0; i < n; i++) {
        labirinth[i] = new char[m + 1];
    }
    for (int i = 0; i < n; i++) {
        string buffer;
        input >> buffer;
        for (int j = 0; j < m; j++)
            labirinth[i][j] = buffer[j];
    }
    int startpoint = 0;
    int finish = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((labirinth[i][j] == '.')|| (labirinth[i][j] == 'S') || (labirinth[i][j] == 'T'))
            {
                if (j > 0)
                    if ((labirinth[i][j - 1] == '.')|| (labirinth[i][j - 1] == 'S') || (labirinth[i][j - 1] == 'T'))
                    list[i * m + j].left = i * m + j - 1;
                if (j < m - 1)
                    if ((labirinth[i][j + 1] == '.') || (labirinth[i][j + 1] == 'S') || (labirinth[i][j + 1] == 'T'))
                    list[i * m + j].right = i * m + j + 1;
                if (i > 0) 
                    if ((labirinth[i - 1][j] == '.') || (labirinth[i - 1][j] == 'S') || (labirinth[i - 1][j] == 'T'))
                    list[i * m + j].up = (i - 1) * m + j;
                if (i < n - 1) 
                    if ((labirinth[i + 1][j] == '.') || (labirinth[i + 1][j] == 'S') || (labirinth[i + 1][j] == 'T'))
                    list[i * m + j].down = (i + 1) * m + j;
            }
            if (labirinth[i][j] == 'S')
            {
                startpoint = i * m + j;
            }
            if (labirinth[i][j] == 'T')
            {
                finish = i * m + j;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        delete[] labirinth[i];
    }
    delete[] labirinth;
    bool* visited = new bool[n*m];
    for (int i = 0; i < n * m; i++)
        visited[i] = false;
    visited[startpoint] = true;
    Queue VertexQueue;
    VertexQueue.push(startpoint);
    while (!VertexQueue.empty())
    {
        int current = VertexQueue.pop();
        if (list[current].left != -1)
         if (!visited[list[current].left])
        {
            VertexQueue.push(list[current].left);
            visited[list[current].left] = true;
            list[list[current].left].Path = list[current].Path + "L";
        }
        if (list[current].right != -1)
        if (!visited[list[current].right])
        {
            VertexQueue.push(list[current].right);
            visited[list[current].right] = true;
            list[list[current].right].Path = list[current].Path + "R";
        }
        if (list[current].up != -1)
        if (!visited[list[current].up])
        {
            VertexQueue.push(list[current].up);
            visited[list[current].up] = true;
            list[list[current].up].Path = list[current].Path + "U";
        }
        if (list[current].down != -1)
        if (!visited[list[current].down])
        {
            VertexQueue.push(list[current].down);
            visited[list[current].down] = true;
            list[list[current].down].Path = list[current].Path + "D";
        }

    }
    if (!list[finish].Path.empty())
    {
        output << list[finish].Path.size() << '\n';
        output << list[finish].Path;
    }
    else
        output << -1;
    input.close();
    output.close();
    return 0;
}


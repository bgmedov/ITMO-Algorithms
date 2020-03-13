#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
enum color {
    WHITE,
    GRAY,
    BLACK
};
struct Vertex {
    color color = WHITE;
    vector<int> connected;
};

Vertex* vertexes;
int vertex_count;
int edge_count;
bool cycles = false;
stack<int> answer;
int cycle_vertex;
ofstream output;
    void Read() {
        ifstream input;
        input.open("cycle.in", ios_base::in);
        input >> vertex_count >> edge_count;
        vertexes = new Vertex[vertex_count];
        for (int i = 0; i < edge_count; i++)
        {
            int a, b;
            input >> a >> b;
            vertexes[a - 1].connected.push_back(b - 1);
        }
        input.close();
    }
   
    bool DFS(int start) {
        if (vertexes[start].color == WHITE)
        {
            vertexes[start].color = GRAY;
            answer.push(start + 1);
            if (vertexes[start].connected.size() == 0)
            {
                vertexes[start].color = BLACK;
                answer.pop();
                return false;
            }
            else {
            for (int i = 0; i < vertexes[start].connected.size(); i++)
            {
                if(DFS(vertexes[start].connected[i]))
                    return true;
            }
            vertexes[start].color = BLACK;
            return false;
            }
        }
        else if (vertexes[start].color == GRAY) {
            cycles = true;
            cycle_vertex = start;
            return true;
        }
        else if (vertexes[start].color == BLACK) {
            return false;
        }
    }

int main()
{
    output.open("cycle.out", ios_base::out);
    Read();
    for (int i = 0; i < vertex_count; i++)
    {
        if (DFS(i))
            break;
    }
    if (!cycles)
        output << "NO" << '\n';
    else
    {
        stack<int> final_answer;
        output << "YES" << '\n';
        while (answer.top() != cycle_vertex + 1)
        {
            final_answer.push(answer.top());
            answer.pop();
        }
        final_answer.push(answer.top());
        while (!final_answer.empty())
        {
            output << final_answer.top() << ' ';
            final_answer.pop();
        }
    }
    delete[] vertexes;
    output.close();
 
  
    
    return 0;
}


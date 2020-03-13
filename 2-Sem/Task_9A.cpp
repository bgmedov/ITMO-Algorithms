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
ofstream output;
    void Read() {
        ifstream input;
        input.open("topsort.in", ios_base::in);
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
   
    void DFS(int start) {
        if (vertexes[start].color == WHITE)
        {
            vertexes[start].color = GRAY;
            if (vertexes[start].connected.size() == 0)
            {
                vertexes[start].color = BLACK;
                answer.push(start + 1);
            }
            else {
            for (int i = 0; i < vertexes[start].connected.size(); i++)
            {
                DFS(vertexes[start].connected[i]);
            }
            vertexes[start].color = BLACK;
            answer.push(start + 1);
            }
        }
        else if (vertexes[start].color == GRAY) {
            cycles = true;
        }
        else if (vertexes[start].color == BLACK) {
            return;
        }
    }

int main()
{
    output.open("topsort.out", ios_base::out);
    Read();
    for (int i = 0; i < vertex_count; i++)
        DFS(i);
    if (cycles)
        output << -1 << '\n';
    else
    {
        while (!answer.empty())
        {
            output << answer.top() << ' ';
            answer.pop();
        }
    }
    delete[] vertexes;
    output.close();
 
  
    
    return 0;
}


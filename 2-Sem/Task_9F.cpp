#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;


vector<vector<int>> graph;
int vertex_count;
int edge_count;
bool* visited;
int* colors; // 0 - white, 1 - gray, -1 - black
bool* status;
vector<int> topsort;
int visited_vertex_count = 0;
bool hamilton = true;
int chip_position;
ofstream output;
    void Read() {
        ifstream input;
        input.open("game.in", ios_base::in);
        input >> vertex_count >> edge_count >> chip_position; 
        chip_position--;
        graph.resize(vertex_count);
        visited = new bool[vertex_count];
        colors = new int[vertex_count];
        status = new bool[vertex_count];
       // components = new int[vertex_count];
        for (int i = 0; i < edge_count; i++)
        {
            int a, b;
            input >> a >> b ;
            graph[a - 1].push_back(b - 1);
        }
        for (int i = 0; i < vertex_count; i++) {
            visited[i] = false;
            status[i] = false;
        }
        input.close();
    }

    void DFS(vector<vector<int>>& in_graph, int start) {
            bool current_status = false;
            visited[start] = true;
            for (int i = 0; i < in_graph[start].size(); i++)
            {
                if (!visited[in_graph[start][i]])
                {
                    DFS(in_graph, in_graph[start][i]);
                }
                if (!status[in_graph[start][i]])
                {
                    current_status = true;
                }
            }
            status[start] = current_status;
        }
    

  

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    output.open("game.out", ios_base::out);
    Read();
    DFS(graph, chip_position);
    if (status[chip_position])
        output << "First player wins" << '\n';
    else
        output << "Second player wins" << '\n';
 
    output.close();
    return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;


vector<vector<int>> vertexes;
int vertex_count;
int edge_count;
bool cycles = false;
stack<int> answer;
int cycle_vertex;
bool* visited;
int* colors;
ofstream output;
    void Read() {
        ifstream input;
        input.open("bipartite.in", ios_base::in);
        input >> vertex_count >> edge_count;
        vertexes.resize(vertex_count);
        visited = new bool[vertex_count];
        colors = new int[vertex_count];
        for (int i = 0; i < edge_count; i++)
        {
            int a, b;
            input >> a >> b;
            vertexes[a - 1].push_back(b - 1);
        }
        for (int i = 0; i < vertex_count; i++)
            visited[i] = false;
        input.close();
    }
    bool bipartite = true;

    bool DFS(int start, int start_color) {
        colors[start] = start_color;
        visited[start] = true;
        for (int i = 0; i < vertexes[start].size(); i++)
            if (colors[vertexes[start][i]] == 0)
            {
                if (!DFS(vertexes[start][i], -start_color))
                {
                    bipartite = false;
                    return false;
                }
            }
            else if (colors[vertexes[start][i]] == start_color)
            {
                bipartite = false;
                return false;
            }
        return true;
    }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    output.open("bipartite.out", ios_base::out);
    Read();
    bool flag = true;
    for (int i = 0; i < vertex_count; i++)
    {
        if (!visited[i]) {
            fill(&colors[0], &colors[vertex_count], 0);
            if (!DFS(i, 1))
                break;
        }
    }
    if (bipartite)
        output << "YES" << '\n';
    else
        output << "NO" << '\n';
 
    output.close();
    return 0;
}


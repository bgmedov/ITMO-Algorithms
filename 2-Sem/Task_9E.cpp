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
vector<int> topsort;
int visited_vertex_count = 0;
bool hamilton = true;
ofstream output;
    void Read() {
        ifstream input;
        input.open("hamiltonian.in", ios_base::in);
        input >> vertex_count >> edge_count;
        graph.resize(vertex_count);
        visited = new bool[vertex_count];
        colors = new int[vertex_count];
       // components = new int[vertex_count];
        for (int i = 0; i < edge_count; i++)
        {
            int a, b;
            input >> a >> b;
            graph[a - 1].push_back(b - 1);
        }
        for (int i = 0; i < vertex_count; i++) {
            colors[i] = 0;
            visited[i] = false;
        }
        input.close();
    }

    bool DFS(vector<vector<int>>& in_graph, int start) {
        if (colors[start] == 0) {
            visited[start] = true;
            colors[start] = 1;
            if (in_graph[start].size() == 0)
            {
                if (visited_vertex_count == vertex_count)
                {
                    colors[start] = -1;
                    topsort.push_back(start);
                }

            }
            else
                for (int i = 0; i < in_graph[start].size(); i++)
                {
                    DFS(in_graph, in_graph[start][i]);
                }
            colors[start] = -1;
            topsort.push_back(start);
        }
        else if (colors[start] == 1)
            return true;
    }
    

  bool exists(int vertex_1, int vertex_2)
  {
      for (int i = 0; i < graph[vertex_1].size(); i++)
      {
          if (graph[vertex_1][i] == vertex_2)
              return true;
      }
      return false;
  }
   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    output.open("hamiltonian.out", ios_base::out);
    Read();
    bool flag = true;
    for (int i = 0; i < vertex_count; i++)
    {
        if (!visited[i])
          DFS(graph, i);
    }
    for (int i = vertex_count - 1; i > 0; i--)
    {
        if (!exists(topsort[i], topsort[i - 1]))
        {
            hamilton = false;
            break;
        }
    }
    if (hamilton)
        output << "YES" << '\n';
    else
        output << "NO" << '\n';
 
    output.close();
    return 0;
}


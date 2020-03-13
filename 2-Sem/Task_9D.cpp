#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;


vector<vector<int>> graph;
vector<vector<int>> reversed_graph;
stack<int> post;
stack<bool> post_visited;
int vertex_count;
int edge_count;
bool* visited;
int* colors; // 0 - white, 1 - gray, -1 - black
int* components;
ofstream output;
    void Read() {
        ifstream input;
        input.open("cond.in", ios_base::in);
        input >> vertex_count >> edge_count;
        graph.resize(vertex_count);
        reversed_graph.resize(vertex_count);
        visited = new bool[vertex_count];
        colors = new int[vertex_count];
        components = new int[vertex_count];
        for (int i = 0; i < edge_count; i++)
        {
            int a, b;
            input >> a >> b;
            graph[a - 1].push_back(b - 1);
            reversed_graph[b - 1].push_back(a - 1);
        }
        for (int i = 0; i < vertex_count; i++) {
            colors[i] = 0;
            visited[i] = false;
        }
        input.close();
    }
    bool bipartite = true;

   void DFS(vector<vector<int>> &in_graph, int start) {
        if (colors[start] == 0) {
            colors[start] = 1;
            if (in_graph[start].size() == 0)
            {
                colors[start] = -1;
                post.push(start);
                post_visited.push(false);
            }
            else
                for (int i = 0; i < in_graph[start].size(); i++)
                {
                    DFS(in_graph, in_graph[start][i]);
                }
            colors[start] = -1;
            post.push(start);
            post_visited.push(false);
        }
        else if (colors[start] == -1)
            return;
    }

    void another_DFS(vector<vector<int>>& in_graph, int start, int comp_number) {
        if (colors[start] == 0) {
            colors[start] = 1;
            if (in_graph[start].size() == 0)
            {
                colors[start] = -1;
                components[start] = comp_number;
            }
            else
                for (int i = 0; i < in_graph[start].size(); i++)
                {
                    another_DFS(in_graph, in_graph[start][i], comp_number);
                }
            colors[start] = -1;
            components[start] = comp_number;
        }
        else if (colors[start] == -1)
            return;
    }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    output.open("cond.out", ios_base::out);
    Read();
    bool flag = true;
    for (int i = 0; i < vertex_count; i++)
    {
        DFS(reversed_graph, i);
    }
    fill(&colors[0], &colors[vertex_count], 0);
    int comp = 1;
    while (post.size() > 0) {
        if (colors[post.top()] == 0) {
            another_DFS(graph, post.top(), comp);
            post.pop();
            comp++;
        }
        else {
           post.pop();
        }
    }
    output << comp - 1 << '\n';
    for (int i = 0; i < vertex_count; i++)
        output << comp - components[i] << ' ';
 
    output.close();
    return 0;
}


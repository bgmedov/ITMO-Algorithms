﻿#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input;
    ofstream output;
    input.open("input.txt", ios_base::in);
    output.open("output.txt", ios_base::out);
    int n, m;
    input >> n >> m;
    int** matrix;
    matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    int a, b;
    for (int i = 0; i < m; i++)
    {
        input >> a >> b;
        matrix[a - 1][b - 1]++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (((matrix[i][j] == matrix[j][i])&&(matrix[i][j] != 0)) || (matrix[i][j] > 1)) {
                output << "YES";
                input.close();
                output.close();
                return 0;
            }
        }
    }

    output << "NO" << '\n';
    input.close();
    output.close();
    return 0;
}


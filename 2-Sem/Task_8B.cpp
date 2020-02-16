#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input;
    ofstream output;
    input.open("input.txt", ios_base::in);
    output.open("output.txt", ios_base::out);
    int n;
    input >> n;
    int** matrix;
    matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    int a, b;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if ((matrix[i][j] != matrix[j][i]) || (matrix[i][j] > 1) || (matrix[j][i] > 1))
            {
                output << "NO" << '\n';
                input.close();
                output.close();
                return 0;
            }
            if ((j == i) && (matrix[i][j] != 0))
            {
                output << "NO" << '\n';
                input.close();
                output.close();
                return 0;
            }
        }
    }

    output << "YES" << '\n';
    input.close();
    output.close();
    return 0;
}


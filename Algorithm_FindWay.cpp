#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using std::pair;
using std::min;
using std::cin;
using std::cout;
using std::vector;

vector<vector<pair<int, int>>> matrix
{
    {pair<int, int>(4, 1), pair<int, int>(2, 2), pair<int, int>(3, 3), pair<int, int>(6, 4)},
    {pair<int, int>(1, 4)},
    {pair<int, int>(1, 5), pair<int, int>(8, 7)},
    {pair<int, int>(1, 6), pair<int, int>(9, 7)},
    {pair<int, int>(1, 5), pair<int, int>(1, 6), pair<int, int>(3, 7)},
    {},
    {},
    {}
}; //матрица смежности, pair.first - вес, pair.second - направление  
vector<bool> visited; //посещенные вершины

void DFS(int i, vector<int>* points)
{
    visited[i] = true;
    int size = matrix[i].size();
    for (int j = 0; j < size; ++j) {
        int v1 = matrix[i][j].second;
        if (!visited[v1]) {
            DFS(v1, points);
        }
    }
    points->push_back(i);
}

vector<int> TopSort()
{
    int size = matrix.size();
    vector<int> points;
    for (int i = 0; i < size; ++i) {
        if (!visited[i]) {
            DFS(i, &points);
        }
    }
    std::reverse(points.begin(), points.end());
    return points;
}

int FindWay(int u, int k)
{
    int size = matrix.size();
    vector<int> d(size, false);
    for (int i = 0; i < size; ++i) {
        d[i] = 1000000000;
    }
    d[u] = 0;
    vector<int> points = TopSort();
    for (int i = 0; i < size; ++i) {
        int v1 = points[i];
        for (int j = 0; j < matrix[v1].size(); ++j) {
            int near = matrix[v1][j].second;
            d[near] = min(d[near], d[v1] + matrix[v1][j].first);
        }
    }
    return d[k];
}


int main()
{
    
    cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    
    
    cout << "Enter number of vertices N and edges M in format N M, then enter A B C,\n A adjacent to B with weight C \n";
    //Введите количество вершин n и ребер m, потом введите вершину A, что входит в B со стоимостью C
    int n;
    int m;
    cin >> n >> m;
    visited = vector<bool>(n);
    matrix = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    for (int i = 0; i < m; ++i) {
        int a;
        int b;
        int c;
        cin >> a >> b >> c;
        matrix[a].push_back(pair<int, int>(c, b));
    }
    cout << "Enter the first and last point to search";
    int u;
    int k;
    cin >> u >> k;
    cout << FindWay(u, k);
    
    
   
    
    return 0;
}

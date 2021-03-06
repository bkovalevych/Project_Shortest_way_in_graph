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

vector<vector<pair<int, int>>> matrix; //матрица смежности, pair.first - вес, pair.second - направление  
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

void OneSearch(int V)
{
    visited.clear();
    visited.resize(V);
    matrix.clear();
    matrix.resize(V);
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            matrix[i].push_back(pair<int, int>(rand() % 10000, j));
        }
    }
    int start = clock();
    auto res = FindWay(0, V - 1);
    int finish = clock() - start;
    cout << "Time = "<< finish << "ms, N = " << V + (V * V) / 2 << "\n";
}

int main()
{
    
    cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    
    for (int i = 100; i < 10000; i += 100) {
        OneSearch(i);
    }
    
    
   
    
    return 0;
}

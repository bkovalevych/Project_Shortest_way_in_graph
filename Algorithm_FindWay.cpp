#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <regex>

using std::regex_match;
using std::pair;
using std::min;
using std::cin;
using std::cout;
using std::vector;

vector<vector<pair<int, int>>> matrix; //матрица смежности, pair.first - вес, pair.second - направление  
vector<bool> visited; //посещенные вершины

void DFS(int i, vector<int>* points, bool test = false)
{
    if (!test)
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

int testINT(char a, int from = 0, int to = 9999)
{
    
    int res;
    cin >> res;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Invalid data of " << a << "\n";
    }
    else {
        
        if (from <= res && res <= to)
            return res;
        cin.clear();
        cin.ignore(32767, '\n');
        
        cout << "Out of range [" << from << ", " << to << "]. Value " << a << "\n";
    }
    
    return  -1;
}

void Testing()
{
    system("cls");
    cout << "Enter number of vertices N (1 < N < 10000) and edges M in format N M, then enter A B C,\n A adjacent to B (start numbering from 0) with weight C (0 <= C < 10000) \n";
    //Введите количество вершин n и ребер m, потом введите вершину A, что входит в B со стоимостью C
    int n;
    int m;
    while (true) {
        n = testINT('N');
        if (n == -1) {
            cout << "Enter again N M\n";
            continue;
        }
        
        m = testINT('M');
        if (m == -1) {
            cout << "Enter again N M\n";
            continue;
        }
        
        if (n <= 10000 && n > 1 && m > 0 && m < n * n / 2) {
            break;
        }
        
        cout << "N must be in range [2, 10000], M must be in range [1, N * N / 2)\nEnter again N M\n";
    }
    
    vector<int> pointsTest;
    matrix = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    for (int i = 0; i < m; ++i) {
        int a = -1;
        int b = -1;
        int c = -1;
        while (true) {
            a = testINT('A', 0, n - 1);
            
            if (a == -1) {
                cout << "Enter again A B C\n";
                continue;
            }
            
            b = testINT('B', 0, n - 1);
            
            if (b == -1) {
                cout << "Enter again A B C\n";
                continue;
            }
            
            c = testINT('C', 0, 9999);
            if (c == -1) {
                cout << "Enter again A B C\n";
                continue;
            }
           
            break;
        }
        
        visited = vector<bool>(n);
        matrix[a].push_back(pair<int, int>(c, b));
        DFS(a, &pointsTest, true);
        if (visited[a]) {
            --i;
            cout << "graph must be without loops\n";
            matrix[a].erase(matrix[a].begin() + matrix[a].size() - 1);
            continue;
        }
    }
    visited = vector<bool>(n);
    cout << "Enter the first u and the last k point to search\n";
    int u = -1;
    int k = -1;
    while (true) {
        u = testINT('u', 0, n - 1);
        if (u == -1) {
            cout << "Enter u and k again\n";
            continue;
        }
        cin.ignore(32767, ' ');
        cin.clear();
        k = testINT('k', 0, n - 1);
        if (k == -1) {
            cout << "Enter u and k again\n";
            continue;
        }
        break;
    }
    
    int res = FindWay(u, k);
    if (res == 1000000000) {
        cout << "No way" << "\n";
    }
    else {
        cout <<"Answer: " << res << "\n";
    }
}

int main()
{
    
    cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int ex = 1;
    while (ex == 1)
    {
        Testing();
        cout << "Enter 0 to exit, 1 to test again\n";
        cin >> ex;
    }
    return 0;
}

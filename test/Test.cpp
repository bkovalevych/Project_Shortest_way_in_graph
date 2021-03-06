#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <regex>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::regex_match;
using std::pair;
using std::min;
using std::cin;
using std::cout;
using std::vector;

vector<vector<pair<int, int>>> matrix; //матрица смежности, pair.first - вес, pair.second - направление  
vector<bool> visited; //посещенные вершины
int numberOfValue = 1;

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

int testString(string str, int from = 0, int to = 9999)
{
    string res = "";
    
    
    for (int i = 0; i < str.size(); ++i) {

        if (str[i] >= -1 && str[i] <= 255 && isdigit(str[i])) {
            res.push_back(str[i]);
        }
    }
    if (res.size() == 0) {
        return -1;
    }
    if (res.size() > 5) {
        return -2;
    }
    int intRes = atoi(res.c_str());
    if (intRes < from || intRes > to) {
        return -2;
    }
    return intRes;
}

int GetVal(ifstream& istr, ofstream& ostr, int from = 0, int to = 9999)
{
    while (true) {
        string inp = "";
        if (istr.eof() || !istr.is_open()) {
            ostr << "There are not enough values\n";
            cout << "There are not enough values\n";
            return -1;
        }
        istr >> inp;
        int res = testString(inp, from, to);
        if (res == -2) {
            ostr << "Out of range [" << from << ", " << to << "] Number of value: " << numberOfValue << "\n";
        }
        else if (res == -1) {
            ostr << "Invalid data. You add symbols '"<< inp <<"', which are ignored. Number of value: " << numberOfValue << "\n";

        }
        else {
            return res;
        }
        ++numberOfValue;
    }
    return -1;
}

int testINT(char a, int from = 0, int to = 9999)
{
    while (true) {
        int res;
        cin >> res;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid data. Enter again starting with " << a << "\n";
        }
        else {
            if (from <= res && res <= to)
                return res;
            cout << "Out of range [" << from << ", " << to << "] Try again enter " << a << "\n";
        }
    }
    return  -1;
}



void Testing(ifstream& istr, ofstream& ostr)
{
    system("cls");
    
    //Введите количество вершин n и ребер m, потом введите вершину A, что входит в B со стоимостью C
    numberOfValue = 1;
   
    
    int n = GetVal(istr, ostr);
    if (n == -1) {
        return;
    }
    int m = GetVal(istr, ostr, 0, n * n / 2 + 1);
    if (m == -1) {
        return;
    }
    cout << "N = " << n << ", M = " << m << "\n";

    vector<int> pointsTest;
    matrix = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    for (int i = 0; i < m; ++i) {
        int a = GetVal(istr, ostr, 0, n -1);
        int b = GetVal(istr, ostr, 0, n - 1);
        int c = GetVal(istr, ostr, 0, 9999);
        
        if (a == -1 || b == -1 || c == -1) {
            return;
        }
        cout << a << " " << b << " " << c << "\n";
        visited = vector<bool>(n);
        matrix[a].push_back(pair<int, int>(c, b));
        DFS(a, &pointsTest, true);
        if (visited[a]) {
            --i;
            cout << "^graph must be without loops. Your values from "<< numberOfValue - 2 << " to " << numberOfValue << " are ignored\n";
            ostr << "graph must be without loops. Your values from " << numberOfValue - 2 << " to " << numberOfValue << " are ignored\n";
            matrix[a].erase(matrix[a].begin() + matrix[a].size() - 1);
            continue;
        }
    }
    visited = vector<bool>(n);
    
    int u = GetVal(istr, ostr, 0, n - 1);
    int k = GetVal(istr, ostr, 0, n - 1);
    if (u == -1 || k == -1) {
        return;
    }
    cout << "u = " << u << ", k = " << k << "\n";
    ostr << "u = " << u << ", k = " << k << "\n";
    int res = FindWay(u, k);
    if (res == 1000000000) {
        cout << "No way" << "\n";
        ostr << "No way" << "\n";
    }
    else {
        cout << "Answer: " << res << "\n";
        ostr << "Answer: " << res << "\n";
    }
}

int main()
{
    int test = 0;
    ifstream istr;
    ofstream ostr;
    cout << "You can open some test in file. There are 3 tests.\n 1 - correct test\n 2 - test with invalid data\n 3 - test with incorrect values" <<
        "\nEnter t - number of test from 1 to 8..\n";
    test = testINT('t', 1, 8);
    if (test == 1) {
        istr.open("test_1.txt", std::ifstream::in);
        ostr.open("res_1.txt", std::ofstream::out);
    }
    if (test == 2) {
        istr.open("test_2.txt", std::ifstream::in);
        ostr.open("res_2.txt", std::ofstream::out);
    }
    if (test == 3) {
        istr.open("test_3.txt", std::ifstream::in);
        ostr.open("res_3.txt", std::ofstream::out);
    }
    if (test == 4) {
        istr.open("test_4.txt", std::ifstream::in);
        ostr.open("res_4.txt", std::ofstream::out);
    }
    if (test == 5) {
        istr.open("test_5.txt", std::ifstream::in);
        ostr.open("res_5.txt", std::ofstream::out);
    }
    if (test == 6) {
        istr.open("test_6.txt", std::ifstream::in);
        ostr.open("res_6.txt", std::ofstream::out);
    }
    if (test == 7) {
        istr.open("test_7.txt", std::ifstream::in);
        ostr.open("res_7.txt", std::ofstream::out);
    }
    if (test == 8) {
        istr.open("test_8.txt", std::ifstream::in);
        ostr.open("res_8.txt", std::ofstream::out);
    }
    
    Testing(istr, ostr);
    istr.close();
    ostr.close();
    system("pause");

    return 0;
}









#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;


vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> graph;

    if (!file.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;
        while (ss >> value) {
            row.push_back(value);
        }

        if (!graph.empty() && row.size() != graph[0].size()) {
            cerr << "Помилка: Некоректний формат графу. Кількість елементів в рядках не співпадає." << endl;
            exit(EXIT_FAILURE);
        }
        graph.push_back(row);
    }

    file.close();
    return graph;
}


void depthFirstSearch(const vector<vector<int>>& graph, int startVertex) {
    int vertices = graph.size();
    vector<bool> visited(vertices, false);
    stack<int> s;
    vector<int> dfsNumbers(vertices, 0);


    s.push(startVertex);
    visited[startVertex] = true;
    int dfsCounter = 1;

    cout << "Поточна вершина | DFS-номер | Стан стеку\n";
    cout << "-------------------------------------------\n";

    while (!s.empty()) {
        int currentVertex = s.top();
        s.pop();
        dfsNumbers[currentVertex] = dfsCounter++;


        cout << currentVertex + 1 << "              | " << dfsNumbers[currentVertex]
            << "         | ";


        stack<int> tempStack = s;
        vector<int> stackContent;
        while (!tempStack.empty()) {
            stackContent.push_back(tempStack.top() + 1);
            tempStack.pop();
        }
        for (auto it = stackContent.rbegin(); it != stackContent.rend(); ++it) {
            cout << *it << " ";
        }

        cout << "\n";


        for (int i = vertices - 1; i >= 0; --i) {
            if (graph[currentVertex][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
}


int main() {
    string filename;
    cout << "Введіть назву вхідного файлу з описом графу: ";
    cin >> filename;

    vector<vector<int>> graph = readGraph(filename);


    int startVertex;
    cout << "Введіть початкову вершину (1-" << graph.size() << "): ";
    cin >> startVertex;
    startVertex--;

    if (startVertex < 0 || startVertex >= graph.size()) {
        cerr << "Помилка: Некоректна початкова вершина." << endl;
        return EXIT_FAILURE;
    }

    cout << "\nЗавдання 1: Обхід графу пошуком углиб.\n";
    depthFirstSearch(graph, startVertex);

    return 0;
}
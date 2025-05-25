/*
Дан базовый интерфейс для представления ориентированного графа:
struct IGraph {
virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func){
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty()){
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex)){
            if (!visited[nextVertex]){
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func){
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i){
        if (!visited[i]){
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func){
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex)){
        if (!visited[nextVertex]){
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func){
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i){
        if (!visited[i]){
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted){
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex)){
        if (!visited[nextVertex]){
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph){
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++){
        if (!visited[i]){
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }
    
    return sorted;
}

void testFunction(const IGraph &graph, const std::function<void(int)> &func) {
    std::cout << "BFS: ";
    mainBFS(graph, func);
    std::cout << std::endl;

    std::cout << "DFS: ";
    mainDFS(graph, func);
    std::cout << std::endl;

    std::cout << "Topological Sort: ";
    for (int vertex: topologicalSort(graph)) {
        func(vertex);
    }
    std::cout << std::endl;
}

void test1(){
    std::cout << "First testing Graphs:" << std::endl;
    ListGraph listGraph(7);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);

    MatrixGraph matrixGraph(listGraph);
    ArcGraph arcGraph(matrixGraph);
    SetGraph setGraph(arcGraph);

    // Тестирование графов
    std::cout << "ListGraph:" << std::endl;
    testFunction(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "MatrixGraph:" << std::endl;
    testFunction(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "ArcGraph:" << std::endl;
    testFunction(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    std::cout << "SetGraph:" << std::endl;
    testFunction(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
}

void test2(){
    std::cout << "Second testing Graphs:" << std::endl;
    ListGraph listGraph(5);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(2, 3);
    listGraph.AddEdge(3, 4);

    MatrixGraph matrixGraph(listGraph);
    ArcGraph arcGraph(matrixGraph);
    SetGraph setGraph(arcGraph);

    // Тестирование графов
    std::cout << "ListGraph:" << std::endl;
    testFunction(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "MatrixGraph:" << std::endl;
    testFunction(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "ArcGraph:" << std::endl;
    testFunction(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    std::cout << "SetGraph:" << std::endl;
    testFunction(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
    test1();
    test2();
    return 0;
}
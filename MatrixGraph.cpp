#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size): adjacencyMatrix(size, std::vector<int>(size, ZERO_VALUE)){}

MatrixGraph::MatrixGraph(const IGraph &graph){
    adjacencyMatrix.resize(graph.VerticesCount(), std::vector<int>(graph.VerticesCount(), ZERO_VALUE));
    for (int i = 0; i < graph.VerticesCount(); i++){
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int v: vertices){
            adjacencyMatrix[i][v] = 1;
        }
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to){
    assert(0 <= from && from < adjacencyMatrix.size());
    assert(0 <= to && to < adjacencyMatrix.size());
    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const{
    return (int)adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const{
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> nextVertices;
    for (int to = 0; to < adjacencyMatrix.size(); to++){
        if (adjacencyMatrix[vertex][to] != ZERO_VALUE){
            nextVertices.push_back(to);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const{
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyMatrix.size(); from++){
        if (adjacencyMatrix[from][vertex] != ZERO_VALUE){
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}

#include "ArcGraph.h"


Arc::Arc(int from, int to): from(from), to(to) {}


ArcGraph::ArcGraph(int size): vertices(size) {}

ArcGraph::ArcGraph(const IGraph &graph){
        vertices = graph.VerticesCount();
        for (int i = 0; i < graph.VerticesCount(); i++){
            std::vector<int> nextVertices = graph.GetNextVertices(i);
            for (int v: nextVertices){
                arcList.push_back(Arc(i, v));
            }
        }
    }

ArcGraph::~ArcGraph() {}

void ArcGraph::AddEdge(int from, int to){
    assert(0 <= from && from < vertices);
    assert(0 <= to && to < vertices);
    arcList.push_back(Arc(from, to));
}

int ArcGraph::VerticesCount() const{
    return vertices;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const{
    assert(0 <= vertex && vertex < vertices);
    std::vector<int> nextVertices;
    for (Arc arc: arcList){
        if (arc.from == vertex){
            nextVertices.push_back(arc.to);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const{
    assert(0 <= vertex && vertex < vertices);
    std::vector<int> prevVertices;
    for (Arc arc: arcList){
        if (arc.to == vertex){
            prevVertices.push_back(arc.from);
        }
    }
    return prevVertices;
}
#pragma once

#include "IGraph.h"
#include <vector>
#include <map>
#include <cassert>

template<typename TemplateMap = std::map<int, int>>
struct SetGraph : public IGraph {
public:
    SetGraph(int size): list(size) {};

    SetGraph(const IGraph &graph){
        list.resize(graph.VerticesCount());
        for (int i = 0; i < graph.VerticesCount(); i++){
            std::vector<int> vertices = graph.GetNextVertices(i);
            for (int v: vertices){
                list[i][v] = 1;
            }
        }
    };

    ~SetGraph() {};

    void AddEdge(int from, int to) override{
        assert(0 <= from && from < list.size());
        assert(0 <= to && to < list.size());
        list[from][to] = 1;
    }

    int VerticesCount() const override{
        return (int)list.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override{
        assert(0 <= vertex && vertex < list.size());
        std::vector<int> nextVertices;
        for (const auto& v: list[vertex]){
            nextVertices.push_back(v.first);
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override{
        assert(0 <= vertex && vertex < list.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < list.size(); from++){
            if (list[from].find(vertex) != list[from].end()){
                prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<TemplateMap> list;
};
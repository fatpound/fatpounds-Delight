#pragma once

#include "graph.h"

class Dijkstra
{
private:
    std::deque<int> deque;

    std::vector<int> d;
    std::vector<int> p;

    graph* G = nullptr;

    int item_count = 0;

    int w(int u, int v);
    void relax(int u, int v);


protected:


public:
    Dijkstra();
    ~Dijkstra();
    Dijkstra(graph* graf, int source_index);

    void run();
};
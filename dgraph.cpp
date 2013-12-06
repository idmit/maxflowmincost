//
//  dgraph.cpp
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 03.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#include <iostream>
#include <limits>
#include "dgraph.h"

DGraph::DGraph(unsigned nodesNumber):nodesNumber(nodesNumber), adj(nodesNumber, std::vector<Arc>(nodesNumber)) {}

DGraph& DGraph::operator=(DGraph &value)
{
    if (this != &value)
    {
        adj = value.adj;
        nodesNumber = value.nodesNumber;
    }
    return *this;
}

void DGraph::printM() const
{
    for (auto it = std::begin(adj); it != std::end(adj); ++it)
    {
        for (auto in = std::begin(*it); in != std::end(*it); ++in)
        {
            std::cout << "(" << in->capacity << ", " << in->cost << ") ";
        }
        std::cout << '\n';
    }
}

void DGraph::printMProperty(double arcProp(const Arc &)) const
{
    for (unsigned u = 0; u < nodesNumber; ++u)
    {
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            std::cout << arcProp(adj[u][v]) << ", ";
        }
        std::cout << '\n';
    }
}

void DGraph::printMCap() const
{
    printMProperty(Arc::cap);
}

void DGraph::printMCst() const
{
    printMProperty(Arc::cst);
}

void DGraph::printProperty(double arcProp(const Arc &)) const
{
    for (unsigned u = 0; u < nodesNumber; ++u)
    {
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            if (arcProp(adj[u][v]))
            {
                std::cout << "(" << u << ", " << v << ") = " << arcProp(adj[u][v]) << '\n';
            }
        }
    }
    std::cout << '\n';
}

void DGraph::printCap() const
{
    printProperty(Arc::cap);
}

/* Returns vector with i-th value equal to dist(s, i) */
std::vector<double> DGraph::bellmanFord(unsigned s, double arcProp(const Arc &), std::vector<unsigned> *path) const
{
    std::vector<double> distance(nodesNumber);
    std::vector<unsigned> predecessor(nodesNumber);
    bool meaningfullIteration = true;

    /* initialize */
    for (unsigned i = 0; i < nodesNumber; ++i)
    {
        distance[i] = (i == s) ? 0 : std::numeric_limits<double>::infinity();
        predecessor[i] = nodesNumber;
    }

    /* main loop */
    for (unsigned t = 0; meaningfullIteration && t < nodesNumber - 1; ++t)
    {
        /* if current iteration won't make any improvements main loop stops */
        meaningfullIteration = false;
        for (unsigned u = 0; u < nodesNumber; ++u)
        {
            for (unsigned v = 0; v < nodesNumber; ++v)
            {
                auto cap = adj[u][v].capacity;
                auto prop = arcProp(adj[u][v]);

                if (cap > 0 && distance[u] + prop < distance[v])
                {
                    distance[v] = distance[u] + prop;
                    predecessor[v] = u;
                    meaningfullIteration = true;
                }
            }
        }
    }

    if (path)
    {
        *path = predecessor;
    }
    
    return distance;
}

/* Returns vector with i-th value equal to dist(s, i) */
std::vector<double> DGraph::dijkstra(unsigned s, double arcProp(const Arc &), std::vector<unsigned> *path) const
{
    std::vector<double> distance(nodesNumber);
    std::vector<unsigned> predecessor(nodesNumber), Q;
    std::vector<bool> visited(nodesNumber);
    
    /* initialize */
    for (unsigned i = 0; i < nodesNumber; ++i)
    {
        distance[i] = std::numeric_limits<double>::infinity();
        visited[i] = false;
        predecessor[i] = nodesNumber;
    }

    distance[s] = 0;
    Q.push_back(s);
    
    /* main loop */
    while (!Q.empty())
    {
        auto u = Q[0];
        /* u is unvisited element with minimal dist(s, u) */
        for (auto v : Q)
        {
            u = (distance[v] < distance[u] && !visited[v]) ? v : u;
        }
        /* remove it before processing */
        Q.erase(std::remove(begin(Q), end(Q), u), end(Q));
        visited[u] = true;
        
        /* shrink dist(s, v) if addition of u helps */
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            auto cap = adj[u][v].capacity;
            if (!(cap > 0))
            {
                continue;
            }

            auto prop = arcProp(adj[u][v]);
            
            double alternative = distance[u] + prop;
            if (alternative < distance[v])
            {
                distance[v] = alternative;
                predecessor[v] = u;
                if (!visited[v]) { Q.push_back(v); }
            }
        }
    }
    
    if (path)
    {
        *path = predecessor;
    }
    
    return distance;
}

std::vector<double> DGraph::bellmanFordCst(unsigned v, std::vector<unsigned> *path) const
{
    return bellmanFord(v, Arc::cst, path);
}

std::vector<double> DGraph::dijkstraCst(unsigned v, std::vector<unsigned> *path) const
{
    return dijkstra(v, Arc::cst, path);
}

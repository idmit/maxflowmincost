//
//  network.cpp
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 05.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#include "network.h"

double Network::MaxFlowMinCost(double *cost, Network *flowNetwork) const
{
    auto flowStorage = *this;
    auto supplemented = *this;
    std::vector<double> distance(nodesNumber);
    std::vector<unsigned> aug(nodesNumber);
    bool augPathExists = true;
    
    double flow = 0, minAugFlow = 0;
    
    for (unsigned u = 0; u < nodesNumber; ++u)
    {
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            if (adj[u][v].capacity > 0)
            {
                supplemented.adj[v][u].cost = - adj[u][v].cost;
            }
            flowStorage.adj[u][v].capacity = 0;
        }
    }
    
    auto potential = supplemented.bellmanFordCst(src);
    
    for (unsigned u = 0; u < nodesNumber; ++u)
    {
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            supplemented.adj[u][v].cost += potential[u] - potential[v];
        }
    }
    
    while (augPathExists)
    {
        augPathExists = false;
        
        potential = supplemented.dijkstraCst(src, &aug);
        
        for (unsigned u = 0; u < nodesNumber; ++u)
        {
            for (unsigned v = 0; v < nodesNumber; ++v)
            {
                supplemented.adj[u][v].cost += potential[u] - potential[v];
            }
        }
        
        unsigned i = snk;
        minAugFlow = 0;
        while (aug[i] != nodesNumber)
        {
            auto cap = supplemented.adj[aug[i]][i].capacity;
            augPathExists = true;
            if (minAugFlow < cap)
            {
                minAugFlow = cap;
            }
            i = aug[i];
        }
        
        i = snk;
        while (aug[i] != nodesNumber)
        {
            flowStorage.adj[aug[i]][i].capacity += minAugFlow;
            supplemented.adj[aug[i]][i].capacity -= minAugFlow;
            supplemented.adj[i][aug[i]].capacity += minAugFlow;
            i = aug[i];
        }
        flow += minAugFlow;
    }
    
    if (cost)
    {
        for (unsigned u = 0; u < nodesNumber; ++u)
        {
            for (unsigned v = 0; v < nodesNumber; ++v)
            {
                *cost += flowStorage.adj[u][v].capacity * flowStorage.adj[u][v].cost;
            }
        }
    }
    
    if (flowNetwork)
    {
        *flowNetwork = flowStorage;
    }
    
    return flow;
}
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
    /* Keeps original costs and stores arc flow in cap */
    auto flowStorage = *this;
    
    /* Copy of network with added negative backward arcs */
    auto supplemented = *this;
    
    std::vector<double> distance(nodesNumber);
    std::vector<unsigned> aug(nodesNumber);
    bool augPathExists = true;
    
    double flow = 0, maxAugFlow = 0;
    
    /* Adds negative backward arcs and sets overall flow to zero */
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
    
    /* Calculates initial potentials with possibility of negative costs */
    auto potential = supplemented.bellmanFordCst(src);
    
    /* Adjusts costs so that they all become non-negative */
    for (unsigned u = 0; u < nodesNumber; ++u)
    {
        for (unsigned v = 0; v < nodesNumber; ++v)
        {
            supplemented.adj[u][v].cost += potential[u] - potential[v];
        }
    }
    
    /* main loop */
    while (augPathExists)
    {
        augPathExists = false;
        
        /* New potentials can be found by dijkstra, because costs are non-negative */
        potential = supplemented.dijkstraCst(src, &aug);
        
        /* Applies new potentials */
        for (unsigned u = 0; u < nodesNumber; ++u)
        {
            for (unsigned v = 0; v < nodesNumber; ++v)
            {
                supplemented.adj[u][v].cost += potential[u] - potential[v];
            }
        }
        
        /* Finds the max flow that can be added to the cheapest path (goes from snk to src) */
        unsigned i = snk;
        maxAugFlow = 0;
        while (aug[i] != nodesNumber)
        {
            auto cap = supplemented.adj[aug[i]][i].capacity;
            augPathExists = true;
            if (maxAugFlow < cap)
            {
                maxAugFlow = cap;
            }
            i = aug[i];
        }
        
        /* Adds found amount to that path (goes from snk to src) */
        i = snk;
        while (aug[i] != nodesNumber)
        {
            flowStorage.adj[aug[i]][i].capacity += maxAugFlow;
            supplemented.adj[aug[i]][i].capacity -= maxAugFlow;
            supplemented.adj[i][aug[i]].capacity += maxAugFlow;
            i = aug[i];
        }
        
        /* Increases overall flow */
        
        flow += maxAugFlow;
    }
    
    /* Calculates flow's cost (if requested) */
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
    
    /* Exports found flow (if requested) */
    if (flowNetwork)
    {
        *flowNetwork = flowStorage;
    }
    
    return flow;
}
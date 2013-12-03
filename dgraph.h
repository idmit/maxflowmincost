//
//  dgraph.h
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 03.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __maxflowmincost__dgraph__
#define __maxflowmincost__dgraph__

#include <vector>

struct Node
{
    double weight;
    double cost;
    Node():weight(0), cost(0) {};
    void set(double w, double c) {weight = w; cost = c;}
};

struct DGraph
{
    std::vector<std::vector<Node>> adj;

    DGraph(unsigned nodesNumber);
    DGraph& operator=(DGraph &value);

    std::vector<double> bellmanFord(unsigned v);
    std::vector<double> dijkstra(unsigned v);

    void print() const;

private:
    unsigned nodesNumber;
};

#endif /* defined(__maxflowmincost__dgraph__) */

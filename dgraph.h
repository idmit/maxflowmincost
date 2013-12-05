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
#include <functional>

struct Arc
{
    double capacity;
    double cost;
    Arc():capacity(0), cost(0) {};
    void set(double w, double c) {capacity = w; cost = c;}
    static double cst(Arc &a) { return a.cost; };
    static double cap(Arc &a) { return a.capacity; };
};

struct DGraph
{
    std::vector<std::vector<Arc>> adj;

    DGraph(unsigned nodesNumber);
    DGraph& operator=(DGraph &value);

    std::vector<double> bellmanFordW(unsigned v, std::vector<unsigned> *path = 0);
    std::vector<double> dijkstraW(unsigned v, std::vector<unsigned> *path = 0);
    std::vector<double> bellmanFordC(unsigned v, std::vector<unsigned> *path = 0);
    std::vector<double> dijkstraC(unsigned v, std::vector<unsigned> *path = 0);

    void reduceCost(double amount);
    void print() const;

protected:
    unsigned nodesNumber;
    std::vector<double> bellmanFord(unsigned v, double arcProp(Arc &), std::vector<unsigned> *path = 0);
    std::vector<double> dijkstra(unsigned v, double arcProp(Arc &), std::vector<unsigned> *path = 0);
};

#endif /* defined(__maxflowmincost__dgraph__) */

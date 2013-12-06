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
    static double cst(const Arc &a) { return a.cost; };
    static double cap(const Arc &a) { return a.capacity; };
};

struct DGraph
{
    std::vector<std::vector<Arc>> adj;

    DGraph(unsigned nodesNumber);
    DGraph& operator=(DGraph &value);

    std::vector<double> bellmanFordCst(unsigned v, std::vector<unsigned> *path = 0) const;
    std::vector<double> dijkstraCst(unsigned v, std::vector<unsigned> *path = 0) const;

    void printM() const;
    void printMCap() const;
    void printMCst() const;
    
    void printCap() const;

protected:
    unsigned nodesNumber;
    std::vector<double> bellmanFord(unsigned v, double arcProp(const Arc &), std::vector<unsigned> *path = 0) const;
    std::vector<double> dijkstra(unsigned v, double arcProp(const Arc &), std::vector<unsigned> *path = 0) const;
    void printMProperty(double arcProp(const Arc &)) const;
    void printProperty(double arcProp(const Arc &)) const;
};

#endif /* defined(__maxflowmincost__dgraph__) */

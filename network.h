//
//  network.h
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 05.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __maxflowmincost__network__
#define __maxflowmincost__network__

#include "dgraph.h"

struct Network:DGraph
{
    Network(unsigned nodesNumber, unsigned source, unsigned sink):DGraph(nodesNumber), src(source), snk(sink) {}
    
    double MaxFlowMinCost(double *cost = 0, Network *flowNetwork = 0) const;
    Network(char *filename);
private:
    unsigned src, snk;
};

#endif /* defined(__maxflowmincost__network__) */

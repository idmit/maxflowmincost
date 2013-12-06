//
//  main.cpp
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 03.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#include "dgraph.h"
#include "network.h"

int main(int argc, const char * argv[])
{
    Network n(5, 0, 4);
    Network flow(5, 0, 4);
    double f, cost;
    
    n.adj[0][1].set(1, 1);
    
    n.adj[1][2].set(1, 1.5);
    n.adj[2][4].set(1, -0.5);
    
    n.adj[1][3].set(1, 0.5);
    n.adj[3][4].set(1, 0.5);
    
    f = n.MaxFlowMinCost(&cost, &flow);
    
    flow.printCap();
    
    return 0;
}


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
    DGraph dg(3);
    Network n(3, 0, 2);
    double f;
    
    n.adj[0][1].set(1, 1);
    n.adj[1][2].set(1, 1);
//    n.adj[0][2].set(1, 1);
    
    f = n.MaxFlowMinCost();
    
    return 0;
}


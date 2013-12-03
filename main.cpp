//
//  main.cpp
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 03.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#include "dgraph.h"

int main(int argc, const char * argv[])
{
    DGraph dg(3);
    auto v = dg.bellmanFord(0);
    
    dg.adj[0][1].set(1, 1);
    dg.adj[1][2].set(1, 1);
    dg.adj[0][2].set(1, 1);
    
    v = dg.dijkstra(0);
    v = dg.bellmanFord(0);
    
    return 0;
}


//
//  main.cpp
//  maxflowmincost
//
//  Created by Ivan Dmitrievsky on 03.12.13.
//  Copyright (c) 2013 Ivan Dmitrievsky. All rights reserved.
//

#include <iostream>
#include "dgraph.h"
#include "network.h"

int main(int argc, const char * argv[])
{
    char exampleFile[] = "/Users/ivan/.supp/code/maxflowmincost/maxflowmincost/example.txt";
    
    Network n(exampleFile);
    Network flow(5, 0, 4);
    double f, cost;
    
    f = n.MaxFlowMinCost(&cost, &flow);
    
    flow.printCap();
    std::cout << "\nFlow: " << f << '\n';
    std::cout << "\nCost: " << cost << '\n';
    
    return 0;
}


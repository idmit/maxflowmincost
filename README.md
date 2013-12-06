maxflowmincost
==============

An implementation of maxflowmincost problem solution.

For references see:

- Edmonds-Karp max flow algorithm
- Dijkstra and Bellman-Ford shortest path algorithms

With this in mind here is an explanation of maxflowmincost:

Instead of finding the shortest path from `source` to `sink` in a sense of number of nodes (via BFS) we are using Dijkstra to find the "cheapest" path (the shortest in a `cost` sense) and then trying to push the `flow` along this path. That's all.

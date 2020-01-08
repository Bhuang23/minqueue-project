/*util.h*/

#pragma once

#include <iostream>
#include <string>

#include "graph.h"

using namespace std;
int findindex(graph &g, char currentV);
void buildGraph(string filename, graph& g);
vector<char> BFS(graph& g, char startV);
vector<char> DFS(graph& g, char startV);
vector<char> Dijkstra(graph &g, char startV, int *(&predV), int *(&distance));
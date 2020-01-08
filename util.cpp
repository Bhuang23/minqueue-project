/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <limits>
#include "graph.h"
#include "util.h"
#include "minqueue.h"
using namespace std;
const int Infinity = numeric_limits<int>::max();
// findindex:
// Finds the index of currentV in vector of vertices
// returns the index as an integer
int findindex(graph &g, char currentV)
{
	int currVdistance;
		for(int i = 0; i < g.vertices().size(); i++)
		{
			if(g.vertices()[i] == currentV)
			{
				currVdistance = i;
			}
		}
	return currVdistance;
}
//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //

   char vertexes;
   file >> vertexes;
   while(vertexes != '#')
   {
      g.addvertex(vertexes);
      file >> vertexes;
   }
  //
  // TODO: use >> operator, since we are not inputting
  // strings that might contain blanks:
  //
  char from;
  char to;
  int weight;
  file >> from;
  while(from != '#')
  {
     file >> to;
     file >> weight;
      g.addedge(from, to , weight);
      file >> from;
  }
  //
  // Now input edges:  Src Dest Weight ... #
  //

  //
  // TODO: use >> operator, since we are not inputting
  // strings that might contain blanks:
  //
  
}
//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;

  //
  // TODO:
  //
  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  while(!frontierQueue.empty())
  {
     char currentV = frontierQueue.front();
     frontierQueue.pop();
     visited.push_back(currentV);
     vector<char> adj = g.neighbors(currentV);
     for(int i = 0; i < adj.size(); i++)
     {
        if(discoveredSet.find(adj[i]) == discoveredSet.end())
        {
         frontierQueue.push(adj[i]);
         discoveredSet.insert(adj[i]);
        }
     }
  }
  
  return visited;
}
//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  frontierStack.push(startV);

  while(!frontierStack.empty())
  {
     char currentV = frontierStack.top();
     frontierStack.pop();
     if(visitedSet.find(currentV) == visitedSet.end())
     {
        visited.push_back(currentV);
        visitedSet.insert(currentV);
        vector<char> neighbor = g.neighbors(currentV);
        for(int i = 0; i < neighbor.size(); i++)
        {
           frontierStack.push(neighbor[i]);
        }
     }
  }
  //
  // TODO: main loop of DFS algorithm
  //
  

  return visited;
}
//
// Dijkstra:
//
// Performs Dijkstra algorithm to find shortest paths from source 
// to all vertices in the given graph from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> Dijkstra(graph &g, char startV, int *(&predV), int *(&distance))
{
	vector<char>  visited;
	minqueue<char, int> unvisitedQueue(g.vertices(), Infinity);
	for(int i = 0; i < g.numvertices(); i++)
	{
		distance[i] = Infinity;
		predV[i] = -1;
	}
	distance[findindex(g, startV)] = 0;
	unvisitedQueue.pushinorder(startV, 0);
	while(!unvisitedQueue.empty())
	{
		char currentV;
		currentV = unvisitedQueue.minfront();
		unvisitedQueue.minpop();
		if(distance[findindex(g, currentV)] == Infinity)
		{
			break;
		}
	    visited.push_back(currentV);
		vector<char> neighbor = g.neighbors(currentV);
        for(int i = 0; i < neighbor.size(); i++)
		{
			int edgeweight = g.getweight(currentV, neighbor[i]);
			int alternativePathDistance = distance[findindex(g, currentV)]+edgeweight;
			if(alternativePathDistance < distance[findindex(g, neighbor[i])])
			{
				distance[findindex(g, neighbor[i])] = alternativePathDistance;
				predV[findindex(g, neighbor[i])] = findindex(g, currentV);
				unvisitedQueue.pushinorder(neighbor[i], alternativePathDistance);
			}
		}
	}
	return visited;
}
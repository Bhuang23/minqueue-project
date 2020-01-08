/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run BFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"

using namespace std;


//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
}
//Shortestpath:
//backtrack using recursion and predV to print out the shortest path from a vertex whose
// predecessor is the startV vertex to any vertex in the graph 
// 
void Shortestpath(graph g, int predV[], int index) 
{  
    // If the predV[predV[predV[...]]] is -1 then return because 
    // the index is the index of startV 
    if (predV[index] == - 1) 
        return; 
  
    Shortestpath(g, predV, predV[index]); 
  
    cout << g.vertices()[index] << " ";
} 
//printVertices:
//print the str and print all the visited elements using for loop
void printVertices(string str, vector<char> visited)
{
	cout << str;
	 for (char v : visited)
       cout << v << " ";
	cout << endl;
}
//printDijkstra:
////loop through all the vertices in the graph and print the vertices,
//their distances from the startV vertex and 
//the shortest path from the startV vertex to the vertices  
void printDijkstra(graph g, char startV, int *predV, int *distance, vector<char> visited)
{
	  for(int i = 0; i < visited.size(); i++)
	  { 
			  cout << " " << visited[i] << ": " << distance[findindex(g, visited[i])] << " via ";
			  //first print out startV vertex
			  cout << startV << " ";
		      //print out the shortest path from a startV to visited[i] 
		      Shortestpath(g, predV, findindex(g, visited[i]));
			  cout << endl;
	  }
}
int main()
{
  graph  g;
  string filename;
  char   startV;

  cout << "Enter filename containing graph data> ";
  cin >> filename;
  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  outputGraph(g);
  //ask for starting vertex of #

  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;

  while (startV != '#')
  {
    vector<char> visited;
    if (g.isvertex(startV))
    {
      //Neighbors
      visited = g.neighbors(startV);
	  printVertices("Neighbors: ", visited);
      //BFS
	  visited = BFS(g, startV);
	  printVertices("BFS: ", visited);
	  //DFS
	  visited = DFS(g, startV);
       printVertices("DFS: ", visited);
	  int *distance = new int[g.vertices().size()];
	  int *predV = new int[g.vertices().size()];
	  //Dijkstra
	  visited = Dijkstra(g, startV, predV, distance);
	  printVertices("Dijkstra: ", visited);
	  printDijkstra(g, startV,predV, distance,visited);
    }
    else
    {
      cout << "Not a vertex in graph, ignored..." << endl;
    }

    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }
  //
  // done:
  //
  return 0;
}
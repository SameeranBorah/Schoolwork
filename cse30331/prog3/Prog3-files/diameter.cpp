#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#include "graph.hpp"

void read_graph (ifstream &infile, undirected_graph &g) {
  /*
    Precondition:
      infile is a file whose lines have the following format:
        u \t v \n
      where u and v are 0-based node ids.

      g is an empty graph.

    Postcondition:
      g is the graph read from infile.
   */
  string line;
  while (getline (infile, line)) {
    int u, v;
    istringstream ss (line);
    ss >> u >> v;
    add_edge(u, v, g);
  }
}

int dijkstra(const undirected_graph &g, int u) {
  /*
    Precondition:
      g is an undirected graph
      u is a node of g

    Postcondition: 
      Computes the shortest path from u to every node v.
      The return value is the *maximum* length of all such paths.
  */
  int n = num_vertices(g);

  vector<int> distance(n, n); // a distance of n is like infinity
  distance[u] = 0;

  vector<bool> visited(n);

  priority_queue<pair<int, int> > unvisited;
  for (int i=0; i<n; i++)
    unvisited.push(make_pair(-distance[i], i));

  while (unvisited.size() > 0) {
    u = unvisited.top().second;
    unvisited.pop();

    pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(u, g);
    for (neighbor_iterator it = p.first; it != p.second; ++it) {
      int v = *it;
      if (!visited[v]) {
	distance[v] = min(distance[v], distance[u]+1);
	// Bug: need to update priority of v in unvisited
      }
    }

    visited[u] = true;
  }
  return *max_element(distance.begin(), distance.end());
}

int diameter_dijkstra(const undirected_graph &g) {
  /*
    Precondition:
      g is an undirected graph

    Postcondition: 
      Computes the shortest path every node u to every node v.  The
      return value is the diameter of g, that is, the *maximum* length
      of all such paths.
  */
  int n = num_vertices(g);
  int d = 0;
  for (int u=0; u<n; u++)
    d = max(d, dijkstra(g, u));
  return d;
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "usage: diameter <filename>" << endl;
    exit(1);
  }

  ifstream infile (argv[1]);
  undirected_graph g;
  read_graph (infile, g);

  int d = diameter_dijkstra(g);
  cout << d << endl;
}


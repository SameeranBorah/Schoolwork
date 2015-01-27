/*
	John F. Lake, Jr. 
	diameter2.cpp
	
	For this method, I used the original implementation, but added my boolean checks so that you only perform Dijkstra's algorithm on the edge nodes.  This method utilizes the original priority queue of unvisited nodes, and when I update distance[v] I push a new value of the node onto the unvisited priority queue.  If a node comes off the queue having a different priority value than the distance associated with it, it means that it was not updated and I skip over it. 
	
	 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "graph.hpp"
#include <iostream>

using namespace std;



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


/*
	Dijkstra algorithm.  This is implemented with a priority queue.  
*/
int dijkstra(const undirected_graph &g, int u,int maxNum, int minNum) {

	/*
    		Precondition:
      		g is an undirected graph
      		u is a node of g
      		minNum is the fewest number of neighbors a node in g has.
      		maxNum is the most neighbors a node in g has. 

    		Postcondition: 
      		Computes the shortest path from u to every node v.
      		The return value is the *maximum* length of all such paths.
  	*/
	

	//If u is NOT an edge node, don't perform dijkstra's algorithm because it won't be one of the biggest distances.  
	if(g.graph[u].size() <maxNum || maxNum == minNum){
	
		//If the minimum number of nodes is 1, then skip all other nodes that have more neighbors.  
		if((minNum == 1 && g.graph[u].size()==1) ||(minNum >1 && g.graph[u].size() <= maxNum)){
			
			
			int n = num_vertices(g);
  			vector<int> distance(n, n); // a distance of n is like infinity
  			distance[u] = 0;


			//Vector of visited nodes
  			vector<bool> visited(n);


			//Priority queue of unvisited nodes
  			priority_queue<pair<int, int> > unvisited;
		  	for (int i=0; i<n; i++)
   			unvisited.push(make_pair(-distance[i], i));


			//While there are still nodes to visit: 
  			while (unvisited.size() > 0) {
  	
  				//If the node has been marked "dead", skip over it
  				if(unvisited.top().first != distance[unvisited.top().second] || visited[unvisited.top().second]){
  					unvisited.pop();
  				}else{
  	
  					//Pop the next node off and look at its neighbors
    					u = unvisited.top().second;
    					unvisited.pop();

    					pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(u, g);
    					for (neighbor_iterator it = p.first; it != p.second; ++it) {
    					
    					
    						//Update the distance of each neighbor
						int v = *it;
      						int old = distance[v];
						distance[v] = min(distance[v], distance[u]+1);
				
				
						//If the distance is updated, you need to visit that node again.
						if(old != distance[v]){
							visited[v] = false; 
							//Push the new distance onto it.  
							unvisited.push(make_pair(distance[v],v)); 
						}
				
      						
    					}

    				visited[u] = true;
    				}
  			}
  		return *max_element(distance.begin(), distance.end());
   		}
   	}
   	
   	
   	//If a node has the maximum number of neighbors AND the minimum is less than the maximum, then skip that node. 
   	else return 0; 
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
  
  
  //Find the max and min number of neighbors:
  int n = num_vertices(g);
  int maxNum = g.graph[0].size(); 
  for(int i = 1;i<n;i++){
	if(g.graph[i].size() > maxNum) maxNum = g.graph[i].size(); 
  }
  int minNum = g.graph[0].size(); 
  for(int i = 1;i<n;i++){
	if(g.graph[i].size() < minNum) minNum = g.graph[i].size(); 
  }
  
  
  int d = 0;
  for (int u=0; u<n; u++)
    d = max(d, dijkstra(g, u,maxNum,minNum));
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

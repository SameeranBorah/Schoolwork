/*
	John F. Lake, Jr. 
	diameter1.cpp
	
	I took a different approach for finding the diameter in this program.  In order to make this fast, I first calculated the minimum and maximum number of neighbors a node in the undirected graph could have.  I added these as parameters to the dijikstra function, and if a node had the max amount of neighbors, I skip it.  Also, if the minimum number of neighbors is only 1 (meaning that there is a node on the edge of the graph only connected to one node), then I skip every node that has more than one neighbor. As a contingency, if all of the nodes have the same number of neighbors (like a circle), then I check every node.  
	
	My thought process for this was as follows: the longest distance will be between nodes that are on the edges of the graph.  If the maxium number of neighbors for a graph is 5 (which would mean that no nodes have more than 5 neighbors) and the minimum number is 2, then the nodes that would have the largest distance between other nodes would have 2 neighbors.  Similarly, if the minimum number of neighbors is 1, then it only makes sense to use Dijkstra's algorithm on the nodes that only have 1 neighbor. 
	
	
	Using this method, I correctly ran ./diameter1 on snap.txt in 14 seconds.  
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
			
			//Vector of distances
  			vector<int> distance(n,n);
  			distance[u] = 0;
  			
  			//Vector of the nodes that have been visited already
  			vector<bool> visited(n);
  			
  			//Nodes that need to be visited and have their neighbors checked
  			//This is a MIN priority queue
  			priority_queue<pair<int, int>, vector<pair<int,int> >, std::greater<pair<int, int> > > nodesToVisit;
			nodesToVisit.push(make_pair(distance[u],u)); 


			//While there are still nodes that need to be visited
  			while (nodesToVisit.size()>0) {	
  	
				//If the node has already been visited, skip over it.  
   				if(visited[nodesToVisit.top().second]){ 
					nodesToVisit.pop(); 
				}
				else{ 
	
    					u = nodesToVisit.top().second;
    					nodesToVisit.pop();
    					pair<neighbor_iterator, neighbor_iterator> p = adjacent_vertices(u, g);
    					
    					//Loop through the neighbors of u and determine their new distances: 
    					for (neighbor_iterator it = p.first; it != p.second; ++it) {
    			
    						//v is the current neighbor being looked at
     						int v = *it;
      						
      						//old is the distance BEFORE v is looked at.  
      						int old = distance[v]; 
      						
						//Update the distance if it is smaller than the old distance.  
						distance[v] = min(distance[v], distance[u]+1);	
				
						//If the new distance is different, we need to visit that node again.  		
						if(old != distance[v]){
							visited[v] = false; 
							
							//UNLESS that node only has one neighbor
							//(Updating the distane of the node won't change the distance of other nodes.)
							if(g.graph[v].size() == 1) visited[v] = true; 
						}
						
						//If we need to visit the node, we push it onto the queue.  
						if (!visited[v]){
							nodesToVisit.push(make_pair(distance[v],v));
						}	
	
    					}
    					
    				//Update that we don't need to visit u again
    				visited[u] = true;
    				}
 			}
 	
 			//Find the maximum value to return by going through the distance vector. 
 			int maximum = 0; 
        		for (int place = 0; place < n; place++)
  				if (distance[place] > maximum)
    			  		maximum  = distance[place];
   			return maximum;
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

#ifndef GRAPH_HPP
#define GRAPH_HPP

// Import definitions from Boost Graph Library. Your solution must
// delete the following five lines and replace them with your own
// ipmplementation.

#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>

//typedef boost::adjacency_set<boost::vecS, boost::vecS, boost::undirectedS> undirected_graph;
//typedef boost::graph_traits<undirected_graph>::adjacency_iterator neighbor_iterator;
//using boost::num_vertices;
//using boost::adjacent_vertices;


//Typedef for neighbor_iterator
typedef std::set<int>::const_iterator neighbor_iterator;



 //Undirected graph class
 //Each vertex is represented by a number, starting with 0. 
class undirected_graph{ 
public: 

	int numVertices; 
	std::vector<std::set<int> > graph;  
	undirected_graph(); 
};



//Constructor with no args.  Sets everything to zero. 
undirected_graph::undirected_graph(){ 
	numVertices=0;  
}

//Returns the number of vertices in the graph.  
int num_vertices(const undirected_graph &g){
	return g.numVertices; 
}
//Function I use to list the graph.
void list_graph(const undirected_graph &g){
	std::cout << "Listing the graph..."<<std::endl; 
	neighbor_iterator it; 
	for(int i = 0; i<g.numVertices;i++){
		std::cout << "Vertex [" << i << "]:"; 
		
		for(it = g.graph[i].begin(); it != g.graph[i].end();++it){
			std::cout << *it << " "; 
		} 
		std::cout << std::endl;
	}
}

//Returns the range of vertices that vertex u connects to as an STL::pair.  
std::pair<neighbor_iterator,neighbor_iterator> adjacent_vertices(int u,const undirected_graph &g){
	
	neighbor_iterator it = g.graph[u].begin(); 
	neighbor_iterator it2 = g.graph[u].end(); 
	std::pair<neighbor_iterator,neighbor_iterator> pair(it,it2);
	return pair;
}





//This function adds a vertex to the graph, as well as any lower numbered vertices as well. 
int add_vertex(int ver, undirected_graph &g){
	 
	//If there are no vertices present, push on all of the vertices leading up to the one you are adding.  
	if(g.numVertices == 0){
		for(int i =0;i<ver+1;i++){
			//Make a set and push it onto the vector. 
			std::set<int> in;
			g.graph.push_back(in); 
		}
		
		//The number of vertices is ver+1.  (If ver is 0, there is still 1 vertex.)
		g.numVertices = ver+1; 
	
	//If there are vertices, but you are adding a vertex not already in the graph
	}else if(ver > g.numVertices-1){
		for(int i = g.numVertices;i<ver+1;i++){
			std::set<int> in; 
			g.graph.push_back(in); 
		}
		g.numVertices = ver+1; 	
	}
}

//Check to see if an edge is already added
int check_edge(const undirected_graph &g,int u, int v){
	std::set<int>::iterator it = g.graph[u].find(v); 
	if(it == g.graph[u].end()) return 0;
	return 1; 
}


void add_edge(int u, int v,undirected_graph &g){
	 
	if(u >= 0 && v >= 0){
		
		//Valid inputs. Check if they are in the graph already. 
		add_vertex(u,g); 
		add_vertex(v,g); 
		
		if (!check_edge(g,u,v)){
			g.graph[u].insert(v); 
			g.graph[v].insert(u); 
		}
		

	} else{
		std::cout << "Cannot add negative numbers for vertices.\n"; 
		return; 
	}
}
	













#endif

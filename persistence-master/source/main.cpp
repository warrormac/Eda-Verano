// Copyright 2021 Roger Peralta Aranibar
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

// TODO: Uncommend after implement the partial structure
#include "persistence/partial_directed_graph.hpp"
//#include "pointer_machine/directed_graph.hpp"



void partial_directed_graph() {
	std::cout << "Partial Directed Graph"
		<< "\n";
	// Create a DirectedGraph, a maximum of 5 edge for each node and the root with
	// the starting value of 1.
	ADE::Persistence::PartialDirectedGraph<int>
		my_graph(100, 5, 4);
	

	// We can obtain the root and print their value.
	ADE::Persistence::PartialNode<int>* root_ptr = my_graph.get_root_ptr(1);
	std::cout << "Root Value: " << root_ptr->get_data(0) << "\n";  // 5
//
//	// Also, we can insert a new vertex passing the new Node value, and the index
//	// of the pointer that will be used to point the inserted node.
     my_graph.get_root(1).insert_vertex(1, 2);  // 1[0] -> 2
//
	std::cout << "Inserted Value: " << my_graph.get_root(1).get_data(0) << "\n";  // 2
//
//// Likewise, the method to insert a new vertex, returns a reference of the
//// new vertex inserted.
	ADE::Persistence::PartialNode<int>* other_inserted_node_ptr =
		my_graph.get_root(2).insert_vertex(2, 3);  // 5[0] -> 2[1] -> 3
//
	std::cout << "Inserted Value: " << my_graph.get_root(2).get_data(0) << "\n"; 
//		<< "\n";  // 3
//

}

int main() {
	partial_directed_graph();
  return 0;
}

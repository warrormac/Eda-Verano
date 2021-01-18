// Copyright 2021 Roger Peralta Aranibar
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

// TODO: Uncommend after implement the partial structure
// #include "persistence/partial_directed_graph.hpp"
#include "pointer_machine/directed_graph.hpp"

void test_directed_graph() {
  std::cout << "Directed Graph"
            << "\n";
  // Create a DirectedGraph, a maximum of 5 edge for each node and the root with
  // the starting value of 1.
  ADE::PointerMachine::DirectedGraph<int, ADE::PointerMachine::Node<int>>
      my_graph(1, 5);

  // We can obtain the root and print their value.
  ADE::PointerMachine::Node<int>* root_ptr = my_graph.get_root_ptr();
  std::cout << "Root Value: " << root_ptr->get_data() << "\n";  // 5

  // Also, we can insert a new vertex passing the new Node value, and the index
  // of the pointer that will be used to point the inserted node.
  my_graph.get_root().insert_vertex(0, 2);  // 5[0] -> 2

  std::cout << "Inserted Value: " << my_graph.get_root()[0].get_data()
            << "\n";  // 2

  // Likewise, the method to insert a new vertex, returns a reference of the
  // new vertex inserted.
  ADE::PointerMachine::Node<int>* other_inserted_node_ptr =
      my_graph.get_root()[0].insert_vertex(1, 3);  // 5[0] -> 2[1] -> 3

  std::cout << "Inserted Value: " << my_graph.get_root()[0][1].get_data()
            << "\n";  // 3

  // To add an edge between two vertex, we call the function update edge from
  // the startin Node with the index id that will link both nodes.
  my_graph.get_root().update_edge(1,
                                  other_inserted_node_ptr);  // 5[0] -> 2[1] ->
                                                             // 3 5[1]   -> 3

  std::cout << "Following other Edge: " << my_graph.get_root()[1].get_data()
            << "\n";
}

int main() {
  test_directed_graph();

  return 0;
}

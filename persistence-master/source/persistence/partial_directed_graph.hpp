// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <utility>

namespace ADE {
namespace Persistence {

template <typename Type>
class PartialNode {
 public:
  typedef Type data_type;

  PartialNode() {}

  PartialNode(data_type const& data, std::size_t const& out_ptrs_size,
              std::size_t const& in_ptrs_size) {
    backward_ = new PartialNode<Type>*[in_ptrs_size]();
  }

  data_type get_data(unsigned int version) { return data_; }

  bool set_data(data_type const& data) { return true; }

  PartialNode* insert_vertex(std::size_t const& position,
                             data_type const& data) {
    return nullptr;
  }

  bool update_edge(std::size_t const& position, PartialNode* v) { return true; }

  PartialNode& operator[](
      std::pair<std::size_t, unsigned int> const& position_version) const {
    return;
  }

  data_type* data_;
  std::size_t out_ptrs_size_;
  PartialNode** forward_;

  std::size_t in_ptrs_size_;
  std::size_t current_modifications_size_;
  std::size_t current_back_pointer_size_;

  PartialNode** backward_;
  // TODO: Table mods, 2 * in_ptrs_size_
};

template <typename Type, typename Node>
class PartialDirectedGraph {
 public:
  typedef Type data_type;

  PartialDirectedGraph(data_type const data, std::size_t const& out_ptrs_size,
                       std::size_t const& in_ptrs_size) {}

  Node* get_root_ptr(unsigned int const& version) { return nullptr; }

  Node get_root(unsigned int const& version) { return; }

  bool add_edge(Node* u, Node* v, std::size_t position) {
    ++(*current_version_);
    return true;
  }

 protected:
  unsigned int* current_version_;
  std::size_t in_ptrs_size_;

  Node* root_ptr_;
  std::size_t out_ptrs_size_;
};

}  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

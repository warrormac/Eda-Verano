// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <utility>
#include <vector>

namespace ADE {
namespace Persistence {
	template <typename Type>
	class PartialNode {
	public:
		typedef Type data_type;

		PartialNode() : data_(nullptr), forward_(nullptr), backward_(nullptr), 
                      out_ptrs_size_(0), in_ptrs_size_(0),prev_version(nullptr),
                      corresponding_version(0) {}

		PartialNode(data_type const& data, std::size_t const& out_ptrs_size,
			std::size_t const& in_ptrs_size):data_(new data_type(data)),
                  	in_ptrs_size_(in_ptrs_size), out_ptrs_size_(out_ptrs_size)
                  	, prev_version(nullptr),
                  	corresponding_version(std::numeric_limits<unsigned int>::max())
      		{
			backward_ = new PartialNode<Type> * [in_ptrs_size]();
			forward_ = new PartialNode<Type> * [out_ptrs_size]();
		}

		data_type get_data(unsigned int version) { return *(search_version(version)->data_);}  

      bool tabla()
      {
      	int i=0;
        while (i<p.size())
        {
        	if(p[i]==nullptr)
            	return false;
          	i++;
        }
        return true;
      }


	bool set_data(data_type const& data) 
        {
        	if (data == *data_)
             	return false;
        
	     	PartialNode* new_version = new PartialNode<Type>(data, out_ptrs_size_, in_ptrs_size_);
		
	     	if (tabla()) 
             	{
			insert_vertex(next_position, data);
			return true;
		}
        	for (int index=0;table[index] != nullptr;index++ )
			;	
	    	table[index] = &new_version;
        	data_(new data_type(data)); 
		    return true;
		}

	PartialNode* insert_vertex(std::size_t const& position, data_type const& data) 
      	{
        	if (out_ptrs_size_ < position) 
			throw std::out_of_range("Inserted position is out of edges range");

		PartialNode* sig = forward_[position];

		if (sig && sig->in_ptrs_size_ < sig->current_back_pointer_size_) 
			throw std::out_of_range("Position out of second argument node range");

		PartialNode* Nnode = new PartialNode<Type>(data, out_ptrs_size_, in_ptrs_size_);

		Nnode->forward_[position] = sig;
        	forward_[position] = Nnode;
		Nnode->backward_[position] = this;
		Cv++;

		return forward_[position];
	}

  

	bool update_edge(std::size_t const& position, PartialNode* x) 
      	{
        	if (out_ptrs_size_ < position) 
			throw std::out_of_range("Position out of first argument node.");
			
		if (sig->in_ptrs_size_ < x->current_back_pointer_size_) 
			throw std::out_of_range("Position out of second argument node range");

		forward_[position] = x;
		x->backward_[position] = this;
		return true;
	}

      	PartialNode* search_version(unsigned int version) 
      	{
        	PartialNode* cvn = this;
        	PartialNode* cnj = cvn;
        	while (cvn) 
        	{
          		if (cvn->corresponding_version > version) 
			{
            			cnj = cvn;
            			cvn = cvn->prev_version;
         		}
          		else if (cvn->corresponding_version == version)
            			return cvn;
          		else
            			break;
        	}
      		return cnj;
      	}

	PartialNode& operator[]( 
			std::pair<std::size_t, unsigned int> const& position_version) const 
      	{
		if (out_ptrs_size_ < position_version) 
			throw std::out_of_range("Index out of node edges range.");
		
		if (!forward_[position_version]) 
			throw std::logic_error("Access to null reference.");
				
		if (position_version < 2) 
			return *(table[position_version]->forward);
				
		return *search_version(position_version.second)->forward_[position_version.first];
	} 

	data_type* data_;
	std::size_t out_ptrs_size_;
	PartialNode** forward_;

	std::size_t in_ptrs_size_;
	std::size_t current_modifications_size_;
	std::size_t current_back_pointer_size_;

	PartialNode** backward_;

      	int Cv = 0;
	int next_position = 0;
	std::vector<PartialNode**> p[2];
      	unsigned int corresponding_version;
      	unsigned int *last_graph_version;
      	PartialNode* prev_version;
	// TODO: p mods, 2 * in_ptrs_size_
};

template <typename Type>
class PartialDirectedGraph {
 public:
	typedef Type data_type;

	PartialDirectedGraph(data_type const data, std::size_t const& out_ptrs_size, 
                         std::size_t const& in_ptrs_size): in_ptrs_size_(in_ptrs_size),
                         out_ptrs_size_(out_ptrs_size), 
                         root_ptr_(new PartialNode<Type>(data, out_ptrs_size, in_ptrs_size)) {}

	PartialNode<Type>* get_root_ptr(unsigned int const& version) 
      	{
		assert(version <= *current_version_);
        	return root_ptr_->search_version(version);
	}

	PartialNode<Type> get_root(unsigned int const& version) {return *root_ptr_;}
	
	bool add_edge(PartialNode<Type>* u, PartialNode<Type>* v, std::size_t position) 
	{
		 return u->update_edge(position, v);
	}

	protected:
	 unsigned int* Cv_ = 0;
	 std::size_t in_ptrs_size_;

	 PartialNode<Type>* root_ptr_;
	 std::size_t out_ptrs_size_;
};

}  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

// Copyright
#ifndef SOURCEtemp_LINK_HPP_
#define SOURCEtemp_LINK_HPP_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <iostream>

#include <utility>
#include <atomic>

using namespace std;

#define LEAF true

namespace EDA {
namespace Concurrent {



template <class Type>
class BLNode;


template <class Type>
class tuple
{
  public:
    Type value;
    BLNode<Type> * L;
    BLNode<Type>* data_n;
    tuple<Type>* next;

    tuple(Type value)
    {
      this->value = value;
      this->L = nullptr;
      this->data_n = new BLNode<Type>();
      this->data_n->start = new tuple<Type>(value);
      this->next = nullptr;
    };

};


struct locker  //"mutex"
{
  int UNLOCKED = 0;
  int LOCKED = 1;

  std::atomic<int> m_value = 0;
  void lock()
  {
    while (true)
    {
      int expected = UNLOCKED;
      if (m_value.compare_exchange_strong(expected, LOCKED))
        break;
      }
    }

      void unlock()
      {
        m_value.store(UNLOCKED);
      }
 };

        
template <class Type>
class BLNode
{
  public:

    tuple<Type>* start;
    BLNode<Type>* lp;
    locker spinner;
    bool hoja;
    int ent;
    bool lock2;

    BLNode(bool hoja = 0)
    {
      this->start = nullptr;
      this->lp = nullptr;
      this->hoja = hoja;
      this->ent = 0;
      this->lock2 = false;
    }

    BLNode<Type>* esc(Type value)
    {
      tuple<Type>* aux = this->start;
      while (aux != nullptr && aux->value < value)
        aux = aux->next;
      
      return aux ? aux->L : this->lp;
    }

    tuple<Type> area(Type value, tuple<Type>* &aux)
    {
      while (aux != nullptr && aux->value != value)
          aux = aux->next;
      return 0;
    }
    tuple<Type>* medioT() // obtiene el tuple del medio 
    {
      tuple<Type>* aux = this->start;
      for (int i = 0; i < (this->ent / 2) - 1; ++i)
          aux = aux->next;
      
      tuple<Type>* middle_tuple = aux;
      return middle_tuple;
    };

    tuple<Type>* ultimoT() // obtiene el tuple del medio 
    {
      tuple<Type>* aux = this->start;
      while (aux != nullptr && aux->next != nullptr)
        aux = aux->next;
      
      return aux;
    };

    tuple<Type>* Tup(Type value) // obtiene el tuple
    {
      tuple<Type>* aux = this->start;
      area(value , aux);
      return aux;
    };

    Type get_data(Type value) // jala la data
    {
      tuple<Type>* aux = this->start;
      area(value , aux);
      return aux ? aux->data_n->start->value : value;
    }

    void insertL(Type value)  //insertar a la hoja
    {
      tuple<Type>* new_tuple = new tuple<Type>(value);
      this->insert(new_tuple);
    }

    void insertNL(Type value, BLNode<Type>* link_node) // no hoja
    {
      tuple<Type>* new_tuple = new tuple<Type>(value);
      this->insert(new_tuple);
      BLNode<Type>* old_node = new_tuple->next->L;
      new_tuple->next->L = link_node;
      new_tuple->L = old_node;
    }

    void insert(tuple<Type>* new_tuple)
    {
      tuple<Type>* aux = this->start;
      tuple<Type>** aux2 = &(this->start);
      while (aux != nullptr && aux->value < new_tuple->value)
      {
        aux2 = &(aux->next);
        aux = aux->next;
      }
      *aux2 = new_tuple;
      new_tuple->next = aux;
      ++this->ent;
    }

    void lock () { spinner.lock(); }

    void unlock () { spinner.unlock(); }
};



template <std::size_t B, typename Type>
class BLinkTree {
 public:
  typedef Type data_type;
  typedef BLNode<Type> Node;
  typedef tuple<Type> NodeInNode;
  typedef locker locker;

  Node* root;
  int B;

  BLinkTree() 
  {
    this->root = new Node(LEAF);
  };

  BLinkTree(int temp)
  {
    this->root = new Node(LEAF);
    this->B = temp;
  };

  ~BLinkTree() {}
  std::size_t size() const {}

  bool empty() const {}

  bool search(const data_type& value) const 
  {

    //cout<<"buscando "<<value<<"\n";
    Node* current = root;
    while (!current->hoja) // find a candidate leaf
      current = current->esc(value);

    while (!current->hoja && current->esc(value) == current->lp)
      current = current->lp;
    
    return current->get_data(value);
  }

  void der(Node* current, Type value)
  {
    Node* aux;
    while (current && current->esc(value) == current->lp)
    {
      aux = current->esc(value);
      aux->lock();
      current->unlock();
      current = aux;
    }
  }

  Type ordenar(Node* current_node, Node* new_node)
  {
    new_node->lp = current_node->lp;
    current_node->lp = new_node;

    NodeInNode* middle_tuple = current_node->medioT();
    new_node->start = middle_tuple->next;
    middle_tuple->next = nullptr;

    int ent = current_node->ent;
    current_node->ent = ent / 2;
    new_node->ent = ent - current_node->ent;

    return middle_tuple->value;
  }

  void split (Node* current, data_type value2, Node* link_node, Node* aux, stack<Node*> &node_stack, data_type value)
  {
    Node* new_node = new Node();
    if (!current->hoja)
    {
      current->insertNL(value, link_node);
      value2= this->ordenar(current, new_node);
    }
      else
      {
        new_node->hoja = true;
        current->insertL(value);
        value2 = this->ordenar(current, new_node);
        
      }
      aux = current;
      link_node = new_node;
      if (!node_stack.empty())
      {
        current = node_stack.top();
        node_stack.pop();
        current->lock();
        der(current, value);
      }
      else current = nullptr;
        
      
      aux->unlock(); 
  }

  void terminar(Node* current, data_type value2, Node* link_node, Node* aux, stack<Node*> &node_stack, data_type value)
  {
    Node* new_root_node = new Node();
    tuple<Type>* left = new tuple<Type>(value);
    tuple<Type>* right = new tuple<Type>(link_node->ultimoT()->value);
    new_root_node->insert(left);
    new_root_node->insert(right);
    new_root_node->start->L = this->root;
    new_root_node->start->next->L = link_node;
    this->root = new_root_node;
    
  }


  void insert(const data_type& value) 
  {
    
    //cout<<"insertando "<<value<<"\n";
    stack<Node*> node_stack;
    Node* current = root;
    Node* aux = nullptr;
    Node* link_node = nullptr;
    data_type value2 = value;

    while (!current->hoja) // encuentra el leaf para que se inserte 
    {
      aux = current;
      current = current->esc(value);
      if (current != aux->lp)
        node_stack.push(aux);
    }

    der(current, value);

    if (current->Tup(value) != nullptr)   //evita repetir elementos
      return; 

    current->lock();
    while (current)
    {
      if (current->ent < this->B) // la pagina elegida tiene espacio
      {
        (!current->hoja)?current->insertNL(value, link_node):current->insertL(value);
        current->unlock();
        return;
      }
      else split(current, value2, link_node, aux, node_stack, value ); //se hace el split
      

    }
    //cout<<"\n\n\ni finisjed\n\n\n";
    terminar(current, value2, link_node, aux, node_stack, value);
    current->unlock();
  }

  

  void remove(const data_type& value) {}

  

 public:
  data_type* data_;
  
};




}  // namespace Concurrent
}  // namespace EDA

#endif  // SOURCEtemp_LINK_HPP_



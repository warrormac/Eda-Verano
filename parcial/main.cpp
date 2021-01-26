// Copyright 2021 Roger Peralta Aranibar / andre alvarez
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "b-link.hpp"

std::size_t NUMBER_THREADS = 8;

const std::size_t NUMBER_OPERATIONS = 10;

int MIN_VALUE = 1;
int MAX_VALUE = 20;

vector<int> ver;
std::random_device rd;


class TreeSearcher {
 public:
  TreeSearcher(unsigned int id, EDA::Concurrent::BplusTree<3, int>* b_link)
      : id_(id), b_link_(b_link) {}
  
  void operator()() {
    std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
    for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
      //std::cout << distribution(rd) << "\n";
      b_link_->search(distribution(rd));
      

    }
  }

 private:
  unsigned int id_;
  EDA::Concurrent::BplusTree<3, int> *b_link_;
};


void run_test() {
  EDA::Concurrent::BplusTree<3, int>* b_link;
  b_link = b_link->Nodo();
  
  std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
  for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
    //std::cout << distribution(rd) << "\n";
    int x=distribution(rd);
    if (find(ver.begin(),ver.end(),x)!=ver.end());
    else
    {
      b_link->insert(x);
      ver.push_back(x);
      while (b_link->par != NULL)   //actualiza los datos 
        b_link = b_link->par;            
    }
  }
 
  std::thread *threads = new std::thread[NUMBER_THREADS];

  for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
    threads[i] = std::thread(TreeSearcher(i, b_link));
  }
  for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
    threads[i].join();
  }

}

int main() {
  run_test();
  return 0;
}

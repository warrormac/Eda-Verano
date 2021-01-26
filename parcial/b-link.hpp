// Copyright
#ifndef SOURCE_B_LINK_Hq_
#define SOURCE_B_LINK_Hq_

#include <utility>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>



using namespace std;

vector<int> verificador;


namespace EDA {
namespace Concurrent {

template <std::size_t B, typename Type>
class BplusTree {
 public:
  
  typedef Type data_type;
  
  BplusTree* ptr[B+3];
  BplusTree* par;
  BplusTree* hijo;
  int b, p, q,ID, val[B + 3];
  bool hoja;
  

  BplusTree(): b(B),p(0),q(0) {}


  ~BplusTree() 
  {
    delete [] ptr;
    delete [] par;
    delete [] hijo;
    delete [] Nodo;
  }

  BplusTree* Nodo() // crea las tablas guia del arbol
  {
    BplusTree* cur = (BplusTree*)malloc(sizeof(BplusTree));
    cur->p = 0; cur->q = 0;
    cur->hoja = true;
    cur->par = NULL;
    cur->hijo = NULL;
    cur->ID = -1;
    return cur;
  } 


  bool empty() const {}

  void search(const data_type& value) const 
  {
    //cout << "estoy buscando " << value << "\n";
    int temp = p - 1;
    while (temp >= 0 && value < val[temp]) 
      temp--;
    
    temp++;
    if (hoja==true) 
    {
      temp--;
      //(val[temp] == value)?cout << "Encontrado...........!\n ":cout << "No existe\n";
    }
    else ptr[temp]->search(value); // siguente link
    //for (std::vector<int>::const_iterator i = verificador.begin(); i != verificador.end(); ++i)
    //std::cout << *i << ' ';            
  }

  void Insert_d(int in, int x) //inserta el valor
  { 
    //if (find(verificador.begin(),verificador.end(),x) != verificador.end())
      //cout<<"rep\n";
    
   // else{
    for (int i = p - 1; i >= in; i--)    
      val[i + 1] = val[i];  

    val[in] = x;
    p++;

    //}
  }


  void Insert_p(int in, BplusTree* p) //inserta el link entre los nodos
  { 
    for (int i = q - 1; i >= in; i--) 
    {
      ptr[i]->ID++;
      ptr[i + 1] = ptr[i];
    }
    ptr[in] = p;
    q++;
  }

  void insert(const data_type& value)  
  {
    
    //cout<<"estoy insertando "<<value<<"\n";
    
    int temp = 0;
    for(; temp<p; temp++)
    {
      if (value < val[temp]) //busca la posicion para meterlo 
        break;
    }
    (hoja==true)?Insert_d(temp, value):  ptr[temp]->insert(value); //evita el overflow
    
    
    while (p == B) split(); //verifica si es necesario un split, para crear un nuevo nodo
    
  }


  void pushBackVal(int x) //move a new lista
  { 
    val[p++] = x;
  }

  void pushBackPtr(BplusTree* p) 
  {
    ptr[q++] = p;
  }

  void delVal(int in) 
  {
    for (int i = in + 1; i < p; i++) 
      val[i - 1] = val[i];
    p--;
  }


  void invt() 
  {
    reverse(val, val + p);
    reverse(ptr, ptr + q);
  }
  

  void split() 
  {
    //cout<<"toy en el split\n\n";
    BplusTree* splitedNode = Nodo(); //crea una tabala temporal
        
    splitedNode->hoja = hoja;
    hijo = splitedNode;

    int i=0;
    while (p > B / 2 || q > B / 2 + 1) 
    {  
      if (p > B / 2)
      {
        splitedNode->pushBackVal(val[p - 1]);//reasigna los valores
        p--; 
      }
      if (q > B / 2 + 1)
      {
        splitedNode->pushBackPtr(ptr[q - 1]); //hace el link
        q--; 
      }
    }

    splitedNode->invt();
    //verificador.pop_back();
    while (i<splitedNode->q) //actulizamos el nodo temp, se genera un nuevo nivel
    {
      splitedNode->ptr[i]->ID = i;
      splitedNode->ptr[i]->par = splitedNode;
      i++;
    }    

    if (par == NULL)  // creamos la nodo final
    { 
      par = Nodo();
      par->hoja = false;
      par->pushBackPtr(this);
      ID = 0;
    }

    splitedNode->par = par;
    splitedNode->ID = ID + 1;


    par->Insert_d(ID, splitedNode->val[0]); //manejamos al nuevo padre
    par->Insert_p(ID + 1, splitedNode); 

    if (!hoja) splitedNode->delVal(0); //clean

  }

  // no era necesario :(
  /*bool prestar() 
  {
    if (ID + 1 == par->q) 
      return false; 
    
    BplusTree* rgt = par->ptr[ID + 1]; ///jalamos de la derecha
  }

  void remove(const data_type& value) 
  {
    int temp=p;
    while (temp-1 >= 0 && value < val[temp-1]) 
      temp--;
    
    if (hoja==true) 
    {
      if (temp >= 0 && val[temp] == value) 
      {
        delVal(temp);
        if (p < B / 2) 
        {
          if (prestar()) 
            return;
          
        }
        else cout << "error!" << endl;
      }
      else ptr[temp+1]->remove(value);
    }
  }*/

 private:
  data_type* data_;
};

}  // namespace Concurrent
}  // namespace EDA

#endif  // SOURCE_B_LINK_Hq_

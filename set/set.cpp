#include "set.h"
#include "../common/Common.h"

struct Node {
   Hechizo elem; // el elemento que este nodo almacena
   Node* next; // siguiente nodo de la cadena de punteros
};

struct SetSt {
   int size; // cantidad de elementos del conjunto
   Node* first; // puntero al primer elemento
};

/**
  Invariantes de representacion:
    - size es la cantidad de nodos
    - no hay nodos con hechizos repetidos
**/

/// Proposito: retorna un conjunto de hechizos vacio
/// Costo: O(1)
Set emptyS() {
   SetSt* res= new SetSt;
   res-> size= 0;
   res -> first =NULL;
   return res;
}

/// Proposito: retorna la cantidad de hechizos
/// Costo: O(1)
int sizeS(Set s) {
   return s-> size;
}

/// Proposito: indica si el hechizo pertenece al conjunto
/// Costo: O(h), h = cantidad de hechizos
bool belongsS(Hechizo h, Set s) {
   bool res= false;
  Node* pAux= s ->first;
   while (pAux!=NULL) {

        res=res || mismoHechizo(h,pAux->elem);
        pAux=pAux->next;

   }

   return res;
}

/// Proposito: agrega un hechizo al conjunto
/// Costo: O(h), h = cantidad de hechizos
void addS(Hechizo h, Set s) {
   if (!belongsS(h,s)){
   Node* n = new Node;
    n->elem=h;
    n->next=s->first;

    s->first=n;
        s->size ++;
    }
}

/// Proposito: borra un hechizo del conjunto (si no existe no hace nada)
/// Costo: O(h), h = cantidad de hechizos
void removeS(Hechizo h, Set s) {

if(s->first!=NULL&&belongsS(h,s)){
   Node* act= s->first ;
    Node* ant = NULL;

    while (act !=NULL && !mismoHechizo(act->elem,h) ){
        ant =act;
        act= act->next;
        }

    if (act!=NULL && ant != NULL){
       ant->next= act->next;
       s->size-=1;
         delete act;

    }
    else {

       s->first=act->next;
       s->size-=1;
     delete act;

        }
    }

}

/// Proposito: borra toda la memoria consumida por el conjunto (pero no la de los hechizos)
/// Costo: O(n)
void destroyS(Set s) {
  Node* p=s->first;
  while (p!=NULL){

    Node* tmp=p->next;
    delete p;
    p=tmp;
  }
}

Set copiar(Set xs){

 Set res= emptyS();
 Node* n= xs-> first;

    while (n!=NULL){

        addS(n->elem,res);
        n=n->next;
    }

    return res;
}


/// Proposito: retorna un nuevo conjunto que es la union entre ambos (no modifica estos conjuntos)
/// Costo: O(h^2), h = cantidad de hechizos
Set unionS(Set s1, Set s2) {
   Set s= copiar(s1);
   Node* n= s2->first;

   while (n!=NULL){

        addS(n->elem,s);
        n=n->next;

   }
   return s;
}

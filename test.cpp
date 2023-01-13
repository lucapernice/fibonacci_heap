#include "fibonacciheap.hpp"


//Comparatore per le key dei nodi
template<typename T> 
struct NodeComparator{
    bool operator()(const Node<T>* n1,const Node<T>* n2){
        return (n1->key > n2->key);
    }
};

int main(){

//Inizializza una Heap vuota (per valori interi e comparatore "NodeComparator")
fibonacci_heap<int,NodeComparator<int>> H; 


//Valori da inserire nella Heap di Fibonacci

int x = -5;
int y = 224;
int z = 10;
int w = 143;
int c = 331;


//Inserimento dei valori nella Heap

H.insert(x);
H.insert(y);
H.insert(z);
H.insert(w);
H.insert(c);

//Tutti questi valori sono inseriti nella lista di radici della Heap
//Si può stampare a schermo questa lista con il metodo dedicato

std::cout<<"Prima dell'unione"<<std::endl;
H.print_roots();



//Inizializzazione di una nuova Heap

fibonacci_heap<int,NodeComparator<int>> Hs;


//Valori da inserire

int a = 12;
int b = -31;
int d = 22;


//Inserimento dei valori nella nuova Heap

Hs.insert(a);
Hs.insert(b);
Hs.insert(d);


//Unione delle due Heap in H
H.heap_union(Hs);


//Una nuova stampa a schermo della lista di radici di H mostra il risultato
std::cout<<"Dopo l'unione "<<std::endl;
H.print_roots();


//Estrazione del minimo e stampa a schermo del valore
int min = H.extract_min();

std::cout<<"Valore minimo estratto: "<< min <<std::endl;


//Dopo l'estrazione del minimo la struttura della Heap è cambiata.
//Oltre alla lista delle radici è possibile stampare la lista dei figli di un nodo.

std::cout<<"Dopo l'estrazione del minimo"<<std::endl;

H.print_roots();
H.print_children(H.head);  //L'attributo head è il puntatore al nodo di testa della
                           //lista di radici

//Decremento a -100 del nodo con chiave 224 
H.decrease_key(H.head->child->right,-100);
std::cout<<"Dopo decremento: "<<std::endl;
H.print_children(H.head->right);
H.print_roots();

//Cosa succede se si prova a incrementare un valore con decrease_key() ?
H.decrease_key(H.head,101); //La funzione stampa un messaggio a schermo spiegando che
                            //il tentativo viene ignorato e la heap non subisce alcuna 
                            //modifica

//Svuotamento della Heap 
while(H.n_nodes > 0){
   std::cout<<"Estratto il nodo "<< H.extract_min()<<std::endl;
}
//Così facendo la memoria occupata dai nodi della Heap è stata deallocata.
//Si può verificare con Valgrind

/*
==11816== HEAP SUMMARY:
==11816==     in use at exit: 0 bytes in 0 blocks
==11816==   total heap usage: 14 allocs, 14 frees, 74,421 bytes allocated
==11816== 
==11816== All heap blocks were freed -- no leaks are possible

*/


//Provare a estrarre il minimo da una Heap vuota lancia un errore
try{
   auto nonexistent_min = H.extract_min();
}

catch(const std::exception& e){
    std::cout<<"Errore: "<< e.what() <<std::endl;
}





return 0;
}
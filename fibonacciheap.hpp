#ifndef __fibonacciheap_hpp__
#define __fibonacciheap_hpp__


#include <iostream>
#include <stdexcept>

/**
 * @brief Struct di un nodo.
 * 
 * Tutti i nodi, che siano radici o figli di altri nodi, sono in liste doppiamente
 * concatenate circolari, dunque la testa della lista raggiunge ,e a sua volta è raggiunta,
 * dalla coda della lista.
 * 
 * @tparam T tipo della chiave del nodo
*/
template<typename T>  
struct Node{

    T key; /** < valore della chiave */
    Node<T>* child; /** < puntatore alla testa della lista di figli del nodo */                
    Node<T>* left; /** < puntatore al nodo a sinistra */
    Node<T>* right; /** < puntatore al nodo a destra */
    Node<T>* parent; /** < puntatore al nodo genitore */
    
    int degree; /** < numero di figli del nodo */
    bool mark; /** < vale 1 se il nodo è marcato, 0 altrimenti */


    /**
     * @brief costruttore.
     * 
     * Imposta come valore della chiave 0
    */
    Node()
    : key(0),child(nullptr),left(nullptr),right(nullptr),parent(nullptr),degree(0),mark(false)
    {}

};





/**
 * @brief Heap di Fibonacci.
 * @tparam T tipo delle chiavi dei nodi della Heap
 * @tparam CMP classe del comparatore
*/
template<typename T,typename CMP> 
struct fibonacci_heap{

    Node<T>* head; /**< puntatore alla testa della lista di radici */
    Node<T>* min; /**< puntatore alla radice con chiave minima */
    size_t n_nodes; /**< numero di nodi nella Heap */
    size_t n_tree; /**< numero di alberi nella Heap */
    CMP cmp; /**< comparatore */


    /**
     * @brief costruttore della Heap.
     * 
     * Inizializza una Heap vuota
    */
    fibonacci_heap()
        : head(nullptr), min(nullptr), n_nodes(0), n_tree(0)
        {}

    
    

    /**
     * @brief Funzione di inserimento.
     * @param x valore del nodo da inserire
    */
    void insert(const T x){

        Node<T>* X = new Node<T>;
        X->key = x;
        

        //inserimento su una heap ancora vuota       
        if (this->n_nodes==0){

            this->head=X;   //La testa delle radici diventa X
            this->min=X;    //Il minimo diventa X
            X->left = X;    //X punta a sè stesso perchè è al momento
            X->right = X;   //l'unico elemeto della lista di radici
        }

        //inserimento in una heap non vuota
        else{

            this->head->left->right = X;   //L'elemeno in coda alla lista di radici
                                        //punta come elemento a destra X

            X->left = this->head->left;    //X punta come elemento a sinistra l'ultimo
                                        //elemento della coda

            X->right = this->head;    //X punta come elemento a destra l'elemento di testa

            this->head->left = X;     //La testa della lista di radici punta come elemento 
                                    //a sinistra X
            
            this->head = X;  //X diventa l'elemento di testa della lista di radici

            //Se la chiave di X è minore del minimo, allora
            //X diventa il minimo
            if (cmp(this->min,X)){
                this->min = X;
            }

        }

        this->n_nodes +=1;  //Il numero di nodi aumenta di 1
        this->n_tree +=1;   //Il numero di alberi aumenta di 1

       

    }



   /**
    * @brief funzione di unione.
    * 
    * Unione alla heap corrente di un'altra heap.
    * In particolare si aggiunge in coda alla lista di radici corrente quella nuova.
    * Il nodo di testa rimane dunque invariato ma si aggiornano se necessario il minimo,
    * il numero totale di nodi e degli alberi.
    * 
    * @param heap Heap da unire
   */
   void heap_union (fibonacci_heap<T,CMP> heap ){

    this->head->left->right = heap.head; //l'ultimo nodo della lista di radici
                                            //della heap corrente (this) si lega a destra
                                            //con la testa della heap da unire

    heap.head->left->right = this->head;   //l'ultimo nodo della lista di radici della heap 
                                            //da unire si lega a destra con il nodo di testa 
                                            //della lista di radici della heap corrente(this)
    
    Node<T>* temp = this->head->left;       //Copia temporanea dell'ultimo nodo della lista di 
                                            //di radici della heap corrente(this)

    this->head->left = heap.head->left;    //l'elemento di testa della lista di radici della heap 
                                            //corrente(this) si lega a sinistra con  l'ultimo 
                                            //elemento della lista della heap da unire
   
    heap.head->left->right = this->head;   //l'ultimo nodo della lista di radici della heap da 
                                            //unire si leaga a destra con la testa della lista 
                                            //di radici della heap corrente(this)

    heap.head->left = temp;                 //Il primo elemento della lista di radici della heap 
                                            //da unire si lega a sinistra con la coda della lista
                                            //della heap corrente(this)

    if(cmp(this->min,heap.min)){  //Si aggiorna il nodo di minimo ne necessario
        this->min = heap.min;
    }

    this->n_nodes += heap.n_nodes; //Sommo il numero di nodi per avere il totale dell'unione
    this->n_tree += heap.n_tree; //Sommo analogamente il nuemero di alberi

    
 
   }

   /**
    * @brief stampa radici.
    * 
    * Semplice funzione per stampare la lista di radici
   */
   void print_roots(){

    if(this->n_nodes==0){
        std::cout<<"empty heap"<<std::endl;
    }

    else{
        Node<T>* current = head;
        std::cout << "Root list:  ";
        for (int i = 0; i<n_tree;++i){
            std::cout<<current->key;
            if(i<n_tree-1) std::cout <<" -- ";
            if(i==n_tree -1){
                std::cout<<std::endl;
            }
            current = current->right;
    }}

   }


    /**
     * @brief stampa figli.
     * 
     * Dato un nodo, semplice funzione per stampare la lista dei suoi figli
     * 
     * @param a nodo di cui stampare i figli
    */
    void print_children(const Node<T>* a){

        if(a->degree == 0){
            std::cout<<"Node "<<a->key<<" children list is empty "<<std::endl;
        }

        else{
            std::cout << "Node "<<a->key<<" children list: ";
            Node<T>* current = a->child;
            for(int i = 0; i<a->degree; ++i){
                std::cout<<current->key;
                if(i<a->degree-1) std::cout <<" -- ";
                if(i==a->degree -1){
                std::cout<<std::endl;
                }
            current = current->right;
        }}
    }

   

  


    /**
     * @brief estrazione minimo.
     * 
     * Funzione per estrarre il minimo dalla Heap.
     * Dopo aver estratto il minimo chiama la funzione di consolidazione.
     * 
     * @return valore minimo della Heap estratto
    */
    T extract_min(){
         
        

        if(this->n_nodes==0){
            throw std::invalid_argument( "Can't extract min beacause the heap is empty");   //Errore: viene lanciato se la fibonacci heap è vuota

        }

        

        if(this->n_nodes==1){                 //caso particolare in cui la heap ha solo un nodo
            T min_value = this->min->key;     //salvo in una nuova variabile il valore del minimo
            delete this->min;                 //elimino il nodo 
            this->n_nodes=0;                  //aggiorno i valori della heap
            this->n_tree = 0;
            this->head = nullptr;
            this->min = nullptr;
            return min_value;               //ritorna il minimo
            
        }

        //caso particolare in cui c'è solo un nodo con figli nella lista di radici
        if(this->n_tree == 1){  
            

            T min_value = this->min->key;
            this->n_tree = this->head->degree;  //I figli diventano radici
            this->n_nodes = this->n_nodes-1;
            this->head = this->head->child; //Aggiornamento della lista di radici
            delete this->min;  //Libero la memoria
            this->min = this->head;
            
            
            Node<T>* current = this->head;  //Puntatore al nodo corrente
            for(int i = 0; i < this->n_tree ; ++i){    //Ciclo for su tutti i figli del nodo rimosso
                current->parent = nullptr;                  //Il puntatore al padre diventa un nullptr

                if(cmp(this->min, current)) this->min = current;  //aggiornamento del minimo

                current = current->right;                   //Si passa al nodo successivo nella lista
            }         




            return min_value;
        }


        
        if(this->min == this->head){        //se il nodo minimo è anche il nodo di testa, 
        
            this->head = this->min->right;  //si pone il nodo a destra del minimo come testa
                                            //della lista di radici
        }

        T min_value = this->min->key; //Salvo il valore minimo in una nuova variabile



        //Se il nodo da rimuovere ha figli:
        if(this->min->degree > 0){              
            

            Node<T>* right = this->min->right;
            Node<T>* left = this->min->left;
            Node<T>* child = this->min->child;

            this->min->left->right = child;  //lego con il puntatore destro la radice
                                                        //a sinistra del minimo con la testa
                                                        //della lista dei figli del nodo di minimo
                                                        //che voglio rimuovere

            this->min->right->left = child->left;                 //lego con il puntatore sinistro la radice
                                                                //a destra del minimo con la rcoda della 
                                                                //lista di figli del nodo minimo che
                                                                //voglio rimuovere            
            
           
            
            child->left->right = right; //lego con il puntatore a destra la coda
                                                            //dei figli del nodo da rimuovere con 
                                                            //il nodo che stava alla sua destra

             child->left = left;       //lego con il puntatore a sinistra la testa dei
                                                        //figli del nodo da rimuovere al nodo che stava
                                                        //alla sua sinistra

            //Adesso il nodo minimo non viene raggiunto da nessun altro nodo della lista di radici e al suo posto
            //ci sono i suoi figli.
            
            

            Node<T>* current = this->min->child;  //La variabile current punta al primo figlio del nodo rimosso 
                                                  //dalla lista di radici
            
            for(int i = 0; i < this->min->degree ; ++i){    //Ciclo for su tutti i figli del nodo rimosso
                current->parent = nullptr;                  //Il puntatore al padre diventa un nullptr
                current = current->right;                   //Si passa al nodo successivo nella lista
            }

            this->n_tree=this->n_tree + this->min->degree - 1;  //Al numero di alberi (che equivale al numero di elementi
                                                                //nella lista di radici) presenti in precedenza si sommano
                                                                //il numero di figli del nodo appena rimosso meno 1
            

        }


        else{   //caso in cui il nodo di minimo da rimuovere non ha figli

            
            this->min->left->right = this->min->right;  //lego il nodo a sinistra del nodo di minimo con quello 
                                                        //alla destra                                       
            this->min->right->left = this->min->left;   //e viceversa

            this->n_tree= this->n_tree - 1;  //aggiorno il numero di alberi

        //Adesso il nodo minimo non viene raggiunto da nessun altro nodo della lista di radici

        }


       
        this->n_nodes = this->n_nodes - 1 ;  //Il numero di nodi è calato di 1
        delete this->min;   //elimino dalla memoria il nodo di minimo precedente
        
        this->consolidate();  //chiamo la funzione consolidate
        this->min = this->head;
        
        int iter = this->n_tree;

        Node<T>* curr = this->head->right; //puntatore al nodo corrente per il ciclo for
        for(int z = 1; z<iter;++z){
            if(cmp(this->min,curr)) {                  
                this->min = curr;   //aggiornamento del minimo
            }
        }    

        return min_value;
    }


   
    /**
     * @brief decremento chiave.
     * 
     * Decrementa il valore della chiave di un nodo della Heap e se necessario
     * lo sposta nella lista di radici
     * 
     * @param x nodo da decrementare
     * @param new_key nuovo valore del nodo
    */
    void decrease_key(Node<T>* x, T new_key){

        //Bisogna controllare che new_key < key per la relazione d'ordine del comparatore

        Node<T>* confronto = new Node<T>;
        confronto->key = new_key;

        if(cmp(confronto,x)){
            std::cout<<"Inserito nuovo valore del nodo maggiore della chiave precedente, nessuna modifica apportata."<<std::endl;
        }

        else{

            x->key = new_key;
            Node<T>* y = x->parent;

            if((y != nullptr) && cmp(y,x)){
                this->cut(x);
                this->cascading_cut(y);
                }
            
            if(cmp(this->min,x)){
                this->min = x;
            }
        }
        delete confronto;  //libero la memoria
    }


private:
 
  /**
   * @brief funzione di linking.
   * 
   * Prende in input il puntatore a due radici.
   * Il secondo nodo in input diventa figlio del primo.
   * 
   * @param root_a prima radice
   * @param root_b seconda radice
  */
    void linking(Node<T>* root_a, Node<T>* root_b){

        
        


        if(this->head==root_b) this->head = root_a;     //Se root_b era testa della lista lo diventa root_a

        root_b->left->right = root_b->right;    //Lego la radice a sinistra di root_b con quella alla sua destra         
        root_b->right->left = root_b->left;     //Lego la radice a destra di root_b con quella alla sua sinistra

        //A questo punto root_b non è più raggiungibile dagli altri nodi della lista di radici
        //Ora si aggiunge root_b in testa alla lista di figli di root_a

        if(root_a->degree == 0){          //se root_a non ha figli
            root_a->child = root_b;       //root_b diventa figlio di root_a

            root_b -> right = root_b;     //in quanto unico elemento della lista di figli, root_b   
            root_b -> left = root_b;      //si lega sia a sinistra che a destra con sè stesso  

            root_b->parent = root_a;      //root_a diventa genitore di root_b 
        }

        //caso in cui root_a ha già altri figli
        else{
            root_b->right = root_a->child;   //root_b punta a destra sulla testa dei figli di root_a
            root_b->left = root_a->child->left;     //root_b punta a sinistra sulla coda dei figli di root_a
            root_a->child->left->right = root_b;    //La coda della lista di figli di root_a punta a destra su root_b
            root_a->child->left = root_b;  //la testa dei figli di root_a punta a sinistra su root_b;
            root_b->parent = root_a;  //root_a diventa genitore di root_b
            root_a->child = root_b;  //root_b diventa la testa della lista dei figli di root_a
        }

        root_a->degree = root_a->degree + 1;  //Il numero di figli di root_a aumenta di 1
        this->n_tree = this->n_tree - 1;  //Il numero di alberi totali diminuisce di uno  
        
    }

    /**
     * @brief funzione di scambio.
     * 
     * Funzione che scambia la posizione di due nodi nella stessa lista
     * 
     * @param a puntatore al primo nodo da scambiare
     * @param b puntatore al secondo nodo da scambiare
    */
    void scambio(Node<T>*a, Node<T>*b){
        

        if(this->head == a)  this->head = b;    //Bisogna prestare attenzione al fatto che una radice tra a 
                                                //e b potrebbe essere testa della lista di radici. 
        else{                                   //Nel caso lo sia una lo diventa l'altra

            if(this->head == b)  this->head = a;
        }


        if(a->right == b){        //Se a è a sinistra di b
            a->right = b->right;
            Node<T>* temp = a->left;
            a->left = b;
            b->right->left = a;
            b->right = a;
            temp->right = b;
            b->left = temp;
            
        }

        else{
            if(a->left == b){      //Se b è a sinistra di a
                b->right = a->right;
                Node<T>* temp = b->left;
                b->left = a;
                a->right->left = b;
                a->right = b;
                temp->right = a;
                a->left = temp;
        }

            //caso generale in cui le due radici non sono adiacenti nella lista
                else{
                a->left->right = b;  //I due nodi attorno ad a si legano a b
                a->right->left = b;

                b->left->right = a; //I due nodi attorno a b si legano ad a
                b->right->left = a; 

                Node<T>* temp_a_left = a->left;
                Node<T>* temp_a_right= a->right;

                
                a->left = b->left;
                a->right = b->right;
                

                b->left = temp_a_left;
                b->right = temp_a_right;
            }
            }
    }
    


    /**
     * @brief funzione di "consolidazione".
     * 
     * Modifica la Heap di Fibonacci di modo che nessuna radice abbia lo stesso degree (numero di figli)
     * 
    */
    void consolidate(){

        Node<T>* A[n_nodes];  // Array che associa ad ogni posizione una radice con relativo degree.
                                     //Dunque in posizione 0 punta alla radice con degree 0, in posizione x alla
                                     //radice di degree x
                                     //Viene allocata una dimensione di n_nodes perchè sicuramente maggiore del
                                     //max degree raggiungibile

        for(int j = 0; j<= n_nodes; ++j){    //Ogni elemento di A è inizializzato nullptr
            A[j]=nullptr;        
            
        }    
        

        int iter = n_tree;      //Salvo il numero di alberi presenti nella heap prima di iniziare le operazioni di "consolidate"
                                //nella variabile iter.            

        Node<T>* current = this->head;  //Setto il nodo corrente alla testa della lista di radici

        //Il ciclo for farà "scorrere" current sulle radici della lista
        //Ciclo sulla varaibile iter e non su n_tree perchè quest'ultima cambia il suo valore (diminuisce il numero di radici
        //durante le operazioni) e quindi interromperei il ciclo for prima di visitare tutte le radici.
        for(int i = 0; i<iter;++i){   

            
            int deg = current->degree; //Per comodità salvo la variabile deg

            
            
            if(A[deg]==nullptr){    //Se nell'array A la posizione relativa al degree 
                     A[deg] = current;   //non è mai stata riempita o è comunque nullptr, vi si inserisce current
            }


            //caso in cui la posizione nell'array A è già occupata
            else{
               
                int check = 1;     //variabile di controllo
                while(check==1){    //finchè la variabile di controllo rimane 1...


                    if(cmp(current,A[current->degree])) {           //Se il nodo corrente è maggiore di quello nell'array A
                                                                    //Allora prima vengono scambiati di posizione
                        this->scambio(current,A[current->degree]);
                        

                        this->linking(A[current->degree],current);  //Il nodo corrente diventa figlio di quello nell'array A

                        A[current->degree] = nullptr; //Si libera il posto nell'array A precedentemente occupato

                        current = current->parent;  //Si aggiorna la posizione corrente
                        

                    }

                    //se invece il nodo corrente ha chiave minore di quello indicato nell'array A
                    else{
                        

                        this->linking(current,A[current->degree]);  //Il nodo dell'array diventa figlio di quello corrente
                        
                         A[(current->degree)-1] = nullptr;  //Si libera il posto nell'array A precedentemente occupato
                                                            //(tenere conto che current->degree è ora aumentato di uno,
                                                            //quindi l'indice di A precedentemente occupato è current->degree -1)
                        
                         }
                    
                   
                    if(A[current->degree]==nullptr){    //Se la posizione nell'array A è libera
                        
                        A[current->degree] = current;   //aggiornamento dell'array A
                        check = 0;  //Aggiorno variabile di controllo per terminare il while
                     }
                    
                }

            }
            
            current = current->right; //Aggiorno nodo corrente
        }

    }

     /**
      * @brief funzione di taglio.
      * 
      * Prende un nodo, lo rimuove dalla posizione corrente e lo aggiunge alla lista di radici.
      * 
      * @param x puntatore al nodo da tagliare
     */
    void cut(Node<T>* x){

        if(x->parent == nullptr){  //Se il nodo x è già nella lista di radici
            std::cout<<"Il nodo "<<x->key<<" è già nella lista di radici"<<std::endl;;
        }
        else{   
            if(x->degree == 0){     //Se il nodo x non ha figli
            //Aggiungo x in testa alla lista di radici

                if(x->parent->degree == 1){ //sottocaso in cui x è "figlio unico"
                    x->right = this->head;
                    x->left = this->head->left;
                    this->head->left->right = x;
                    this->head->left = x;
                    this->head = x;
                    x->parent->degree =0;
                    x->parent->child = nullptr;
                    x->parent = nullptr;
                    this->n_tree = this->n_tree + 1;    
                }
                else{ //sottocaso in cui x NON è "figlio unico"

                    if(x->parent->child == x){       //Se x è la testa della lista di figli,
                        x->parent->child = x->right; //la testa diventa il nodo alla sua destra
                    }

                    //Sposto x in testa alla lista di radici

                    x->left->right = x->right; 
                    x->right->left = x->left;

                    x->right = this->head;
                    x->left = this->head->left;
                    this->head->left->right = x;
                    this->head->left = x;
                
                    this->head = x;    
                    x->parent->degree = x->parent->degree - 1;
                    x->parent = nullptr;
                    this->n_tree = this->n_tree + 1;                
                }
            }
            else{  //Caso in cui il nodo x ha figli


                if(x->parent->degree == 1){ //sottocaso in cui x è "figlio unico"
                    x->parent->child = x->child; 
                    x->child = nullptr;
                    x->parent->degree = x->degree;
                    x->degree = 0;
                    x->right = this->head;
                    x->left = this->head->left;
                    this->head->left->right = x;
                    this->head->left = x;
                    this->head = x;
                    this->n_tree = this->n_tree + 1;

                }

                else{ //sottocaso in cui x NON è figlio unico

                    if(x->parent->child == x){       //Se x è la testa della lista di figli,
                        x->parent->child = x->right; //la testa diventa il nodo alla sua destra
                    }

                    x->left->right = x->child;
                    x->right->left = x->child->left;
                    x->child->left->right = x->right;
                    x->child->left = x->left;

                    x->parent->degree = x->parent->degree + x->degree - 1;
                    x->degree = 0;
                    x->child = nullptr;
                    x->right = this->head;
                    x->left = this->head->left;
                    this->head->left->right = x;
                    this->head->left = x;
                    
                    this->head = x;
                    this->n_tree = this->n_tree + 1;

                }

            }


            if(x->mark == 1) x->mark = 0;
            if(cmp(this->min,x)) this->min = x;  //aggiornamento del minimo (non necessario se non fosse per la decrease function)

        }
    }

    /**
     * @brief funzione di taglio a cascata.
     * @param y puntatore al nodo cui applicare la funzione
    */
    void cascading_cut(Node<T>* y){
        if(y->parent != nullptr){  
            //Se y non è una radice   

            if(y->mark==0) y->mark = 1;  //Se non è marcato aggiorno mark 
            else{                        //altrimenti
                this->cut(y);            //si taglia y e si richiama la funzione
                cascading_cut(y->parent);//sul genitore di y

            }
        }
    }

};

#endif  //__fibonacciheap_hpp__


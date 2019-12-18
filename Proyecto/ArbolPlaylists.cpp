#include <iostream>
#include "NodoPlaylist.cpp"
using namespace std;

class ArbolPlaylists{

private:
    NodoPlaylist *raiz;
    int count;
    bool vacio;
    string name_aux;
    int num_nodos;
public:
    ArbolPlaylists(){
        this->vacio = true;
        this->raiz = 0;
        this->count = 1;
        this->name_aux = "";
        this->num_nodos = 0;
    }

    NodoPlaylist *getRaiz(){ return this->raiz; }

    int getCount(){ return this->count; }

    bool EstaVacio(){ return this->vacio; }

    void insertar(Playlist *p){
        this->num_nodos++;
        NodoPlaylist *n = new NodoPlaylist(p,this->num_nodos); 
        if(this->raiz==0){
            this->raiz = n;
            this->vacio = false;
        } else {
            insertar_recursivo(this->raiz,n);
        }

    }

    void insertar_recursivo(NodoPlaylist *raiz_actual, NodoPlaylist *n){
            if(n->getPlaylist()->getName().compare(raiz_actual->getPlaylist()->getName()) == -1){ //INSERTAR A LA IZQUIERDA
                if(raiz_actual->getIzquierda()!=0){ //LLAMADA RECURSIVA
                    insertar_recursivo(raiz_actual->getIzquierda(),n);
                } else {
                    raiz_actual->setIzquierda(n);
                }
            } else if (n->getPlaylist()->getName().compare(raiz_actual->getPlaylist()->getName()) == 1){ //INSERTAR A LA DERECHA
             if(raiz_actual->getDerecha()!=0){ //LLAMADA RECURSIVA
                insertar_recursivo(raiz_actual->getDerecha(),n);
             } else {
                 raiz_actual->setDerecha(n);
             }
            } 
    }

    void inorder(){
        this->count = 1;
        inorder_recursivo(this->raiz);
    }

    void inorder_recursivo(NodoPlaylist *raiz_actual){ //IZQUIERDA-RAIZ-DERECHA
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            inorder_recursivo(raiz_actual->getIzquierda());
        }
        //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << count << ". " << raiz_actual->getPlaylist()->getName() << endl;
        this->count++;
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            inorder_recursivo(raiz_actual->getDerecha());
        }
    }

    void getPlaylist(int index){
        this->count = 1;
        getPlaylistRecursivo(this->raiz,index);
    }
    
    void getPlaylistRecursivo(NodoPlaylist *raiz_actual, int index){
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            getPlaylistRecursivo(raiz_actual->getIzquierda(),index); 
        }
            
        if(count == index){
            this->name_aux = raiz_actual->getPlaylist()->getName();
        }
        this->count++;        
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            getPlaylistRecursivo(raiz_actual->getDerecha(),index);         
        }
    }

    NodoPlaylist *FindNode(NodoPlaylist *root, string name){
        if(root==0){ return 0; }
        if(root->getPlaylist()->getName()==name){ return root; }

        NodoPlaylist *found = FindNode(root->getIzquierda(),name);
        if(found!=0){ return found; }

        return FindNode(root->getDerecha(),name);

    }

    NodoPlaylist *getInorderNode(int index){
        getPlaylist(index);
        return FindNode(this->raiz,name_aux);
    }


    void preorder(){
        preorder_recursivo(this->raiz);
    }

    void preorder_recursivo(NodoPlaylist *raiz_actual){  //RAIZ-IZQUIERDA-DERECHA
       //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << raiz_actual->getPlaylist()->getName();
        cout << "->";
       
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            preorder_recursivo(raiz_actual->getIzquierda());
        }       
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            preorder_recursivo(raiz_actual->getDerecha());
        }
    }


    void postorder(){
        postorder_recursivo(this->raiz);
    }

    void postorder_recursivo(NodoPlaylist *raiz_actual){  //IZQUIERDA-DERECHA-RAIZ      
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            postorder_recursivo(raiz_actual->getIzquierda());
        }       
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            postorder_recursivo(raiz_actual->getDerecha());
        }
         //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << raiz_actual->getPlaylist()->getName();
        cout << "->";
    }

};
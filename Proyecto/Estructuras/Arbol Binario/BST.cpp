#include <iostream>
#include "NodoArbol.cpp"
using namespace std;

class ArbolBinario{

private:
    Nodo *raiz;
public:
    ArbolBinario(){
        this->raiz = 0;
    }

    void insertar(int dato){
        Nodo *n = new Nodo(dato); 
        if(this->raiz==0){
            this->raiz = n;
        } else {
            insertar_recursivo(this->raiz,n);
        }

    }

    void insertar_recursivo(Nodo *raiz_actual, Nodo *n){
            if(n->getDato()<raiz_actual->getDato()){ //INSERTAR A LA IZQUIERDA
                if(raiz_actual->getIzquierda()!=0){ //LLAMADA RECURSIVA
                    insertar_recursivo(raiz_actual->getIzquierda(),n);
                } else {
                    raiz_actual->setIzquierda(n);
                }
            } else if (n->getDato()>raiz_actual->getDato()){ //INSERTAR A LA DERECHA
             if(raiz_actual->getDerecha()!=0){ //LLAMADA RECURSIVA
                insertar_recursivo(raiz_actual->getDerecha(),n);
             } else {
                 raiz_actual->setDerecha(n);
             }
            } 
    }

    void inorder(){
        inorder_recursivo(this->raiz);
    }

    void inorder_recursivo(Nodo *raiz_actual){ //IZQUIERDA-RAIZ-DERECHA
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            inorder_recursivo(raiz_actual->getIzquierda());
        }
        //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << raiz_actual->getDato();
        cout << "->";
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            inorder_recursivo(raiz_actual->getDerecha());
        }
    }

    void preorder(){
        preorder_recursivo(this->raiz);
    }

    void preorder_recursivo(Nodo *raiz_actual){  //RAIZ-IZQUIERDA-DERECHA
       //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << raiz_actual->getDato();
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

    void postorder_recursivo(Nodo *raiz_actual){  //IZQUIERDA-DERECHA-RAIZ      
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL IZQUIERDO
        if(raiz_actual->getIzquierda()!=0){
            postorder_recursivo(raiz_actual->getIzquierda());
        }       
        //LLAMAR RECURSIVAMENTE AL SUB ARBOL DERECHO
        if(raiz_actual->getDerecha()!=0){
            postorder_recursivo(raiz_actual->getDerecha());
        }
         //IMPRIMIR EL VALOR ACTUAL DE LA RAIZ
        cout << raiz_actual->getDato();
        cout << "->";
    }

};
#include <iostream> 
#include "pila.h"
#include "cola.h"
#include "listadoble.h"
#include "listadoblecircular.h"
using namespace std; 


int main(){


    ListaDoble<int> *ld = new ListaDoble<int>;
    ld->insertar_inicio(5);
    ld->insertar_inicio(4);
    ld->insertar_inicio(3);
    ld->insertar_inicio(2);
    ld->insertar_inicio(1);
    ld->insertar_en(6,0);
    ld->insertar_en(7,ld->getSize());
    ld->borrar_en(ld->getSize()-1);
    ld->borrar_en(ld->getSize()-1);
    ld->borrar_en(ld->getSize()-1);
    cout<<"El inicio de la lista es: "<<ld->primero->getDato()<<endl;
    cout<<"El final de la lista es: "<<ld->ultimo->getDato()<<endl;
    cout<<"El tamaño de la lista es: "<<ld->getSize()<<endl;
    return 0;
}
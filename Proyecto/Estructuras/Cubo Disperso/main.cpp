#include <iostream>
#include <fstream>
#include "CuboDisperso.cpp"
using namespace std; 

 int main(){

    CuboDisperso *m = new CuboDisperso();
    m->insertar_nodo(1,3,6);
    m->insertar_nodo(1,4,6);
    m->insertar_nodo(1,4,10);
    return 0;
 }
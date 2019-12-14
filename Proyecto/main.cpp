#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <sstream>
#include "Json/json.hpp"
#include "ListaArtistas.cpp"
#include "ListaCancionesOrdenada.cpp"

using namespace std;
using json = nlohmann::json;
string path; //String para guardar la dirección del archivo JSON
json libreria; //Variable Json para almacenar la libreria completa en formato json
json artistas; //Variable Json para almacenar los artistas en formato json
json albumes;  //Variable Json para almacenar los albumes en formato json
json canciones; //Variable Json para almacenar las canciones en formato json
ListaArtistas *lista_artistas = new ListaArtistas();
ListaCancionesOrdenada *lista_canciones = new ListaCancionesOrdenada(); //Lista global de canciones

 void sleepcp(int milliseconds) { // Función para pausar ejecución

    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void Cargar(string path){
    std::ifstream file(path);
    file >> libreria;
    artistas = libreria["Library"];// aqui obtenemos un arreglo con cada artista existente en la libreria
    for (const auto& artista : artistas){ 
    string name_aux = artista["Artist"]["Name"];
    lista_artistas->insertar_ordenado(name_aux, 0);
    Artista *artista_aux = lista_artistas->getArtista(name_aux)->getArtista();
    CuboDiscografia *cubo_aux = artista_aux->getDiscografia();
    albumes = artista["Artist"]["Albums"]; //aqui obtenemos un arreglo con cada album del artista actual.
    double rating_aux = 0;   
        for(const auto& album : albumes ){
            string year = album["Year"];
            int year_int;
            istringstream(year)>>year_int;
            system("cls");
            string album_aux = album["Name"];
            string mes_aux = album["Month"];
            Album *a = new Album(album_aux, mes_aux, year_int);        
            canciones = album["Songs"]; // aqui obtenemos un arreglo con cada canción del album            
                for(const auto& cancion : canciones){
                    string cancion_aux = cancion["Name"];
                    string rating_aux = cancion["Rating"];
                    a->getSongs()->insertar(cancion_aux, a->getName(),artista_aux->getName(), atof(rating_aux.c_str()), a->getYear(),a->getMonth());
                    lista_canciones->insertar_ordenado(cancion_aux, a->getName(),artista_aux->getName(), atof(rating_aux.c_str()), a->getYear(),a->getMonth());                
                }
            a->setRating(a->getSongs()->CalculateRating());
            rating_aux+=a->getRating();
            cubo_aux->insertar_nodo(a->getYear(),a->getMonth(),a);
        }
        double d = (double)cubo_aux->getSize();
        rating_aux = rating_aux / d;
        artista_aux->setRating(rating_aux);
    }
}

void ReproducirCancion(NodoCancion *n){
    system("cls");
    cout << "---------------\"[REPRODUCIENDO]\"---------------"<< endl;
    cout << endl;
    cout << "\t Name: " << n->getCancion()->getName() << endl;
    cout << "\t Artist: " << n->getCancion()->getArtista() << endl;
    cout << "\t Album: " << n->getCancion()->getAlbum() << endl;
    cout << "\t Month: " << n->getCancion()->getMonth() << endl;
    cout << "\t Year: " << n->getCancion()->getYear() << endl;
    cout << "\t Rating: " << n->getCancion()->getRating() << endl;
    cout << endl;
    cout << endl;
    cout << "\tPresione cualquier tecla para salir.";
    getch();
}


void DezplegarCanciones(NodoCubo *n){
system("cls");
    string name_aux = n->getAlbum()->getName();
    std::for_each(name_aux.begin(), name_aux.end(), [](char & c) {
		c = ::toupper(c);});
    cout << "---------------\"["<<name_aux<<"]\"---------------"<< endl;
    cout << endl;
    int x = 1;
    if(n->getAlbum()->getSongs()->getSize()>0){
        NodoCancion *aux = n->getAlbum()->getSongs()->getPrimero();       
    while(aux!=0){
        cout << x << ". " << aux->getCancion()->getArtista()<< ":\t" <<aux->getCancion()->getName() << endl;
        aux = aux->getSiguiente();
        x++;
    }
        cout << endl;
        cout << "Ingrese el numero de la cancion deseada." << endl;
    } else {
        cout << endl;
        cout << "No hay canciones en este album." << endl;
    }
    cout << "s - Regresar a Albums" << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;

    if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index <x){
                NodoCancion *aux = n->getAlbum()->getSongs()->getCancion(index);
                ReproducirCancion(aux);
                DezplegarCanciones(n);
            } else {
             DezplegarCanciones(n); 
            }
        }       
    } else {
        DezplegarCanciones(n);
    }
}

void DezplegarAlbums(NodoArtista *n){
    system("cls");
    string name_aux = n->getArtista()->getName();
    std::for_each(name_aux.begin(), name_aux.end(), [](char & c) {
		c = ::toupper(c);});
    cout << "---------------\"["<<name_aux<<"]\"---------------"<< endl;
    cout << endl;
    int x = 1;
    if(n->getArtista()->getDiscografia()->getSize()>0){        
        NodoCubo *aux = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
        while(aux!=0){
            NodoCubo *b = aux->getAdelante();
            while(b!=0){
                NodoCubo *a = b;
                while(a!=0){
                    cout << x << ". " << a->getAlbum()->getYear() << ": " << a->getAlbum()->getName()<< endl;
                    x++;
                    a = a->getArriba();
                }
                b = b->getAdelante();
            }
            aux = aux->getDerecha();
        }
        cout << endl;
        cout << "Ingrese el numero del album deseado." << endl;
    } else {
        cout << endl;
        cout << "No hay albumes de este artista." << endl;
    }   
    cout << "s - Regresar a Artistas" << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;

    if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index <x){
                NodoCubo *album_aux = n->getArtista()->getDiscografia()->getAlbum(index);
                DezplegarCanciones(album_aux);
                DezplegarAlbums(n);
            } else {
             DezplegarAlbums(n);  
            }
        }       
    } else {
        DezplegarAlbums(n);
    }
}

void menuArtistas(){
    system("cls");
    cout << "---------------\"[ARTISTAS]\"---------------"<< endl;
    cout << endl;
    int x = 1;
    if(lista_artistas->getSize()>0){
        NodoArtista *aux = lista_artistas->getPrimero();
    while(aux!=0){
        cout << x << ". " << aux->getArtista()->getName() << endl;
        aux = aux->getSiguiente();
        x++;
    }
    cout << endl;
    cout << "Ingrese el numero del album deseado." << endl;
    } else {
    cout << endl;
    cout << "No hay artistas disponibles." << endl;
    }   
    cout << "s - Regresar al menu principal." << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;
    if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index <x){
                NodoArtista *n = lista_artistas->getArtista_Index(index);
                DezplegarAlbums(n);
                menuArtistas();
            } else {
             menuArtistas();   
            }
        }       
    } else {
        menuArtistas();
    }

}

void ReproducirCancionGlobal(NodoCancionOrdenado *n){
    system("cls");
    cout << "---------------\"[REPRODUCIENDO]\"---------------"<< endl;
    cout << endl;
    cout << "\t Name: " << n->getCancion()->getName() << endl;
    cout << "\t Artist: " << n->getCancion()->getArtista() << endl;
    cout << "\t Album: " << n->getCancion()->getAlbum() << endl;
    cout << "\t Month: " << n->getCancion()->getMonth() << endl;
    cout << "\t Year: " << n->getCancion()->getYear() << endl;
    cout << "\t Rating: " << n->getCancion()->getRating() << endl;
    cout << endl;
    cout << endl;
    cout << "\tPresione cualquier tecla para salir.";
    getch();
}

void menuCanciones(){
    system("cls");
    cout << "---------------\"[CANCIONES]\"---------------"<< endl;
    cout << endl;
    int x = 1;
    if(lista_canciones->getSize()>0){
        NodoCancionOrdenado *aux = lista_canciones->getPrimero();   
    while(aux!=0){
        cout << x << ". " << aux->getCancion()->getArtista()<< ":\t" <<aux->getCancion()->getName() << endl;
        aux = aux->getSiguiente();
        x++;
    }
    cout << endl;
    cout << "Ingrese el numero de la cancion deseada." << endl;
    } else {
    cout << endl;
    cout << "No hay canciones disponibles." << endl;
    }


    cout << "s - Regresar al menu principal." << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;
    if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index <x){
                NodoCancionOrdenado *aux = lista_canciones->getCancion(index);
                ReproducirCancionGlobal(aux);
                menuCanciones();
            } else {
             menuCanciones();   
            }
        }       
    } else {
        menuCanciones();
    }
}

void menuPrincipal(){
    system("cls");
    cout << "---------------\"[MENU]\"---------------"<< endl;
    cout << endl;
    cout << "Que desea hacer?"<< endl;
    cout << endl;
    cout << "1. Ver artistas\n2. Ver canciones\n3. Ver playlists\n4. Importar playlists\n5. My Music++\n6. Salir"<< endl;
    char c = cin.get();
    switch (c){
        case '1': menuArtistas();
                  menuPrincipal();
                  break;
        case '2': menuCanciones();
                  menuPrincipal();
                  break;
        case '3': break;
        case '4': break;
        case '5': break;
        case '6': break;
        default: menuPrincipal(); break;
    }   
}

void MensajeCarga(string anuncio){
    cout << "----------------[BIENVENIDO A Music++]----------------"<< endl;
    cout << endl;
    cout << "\t\t CARGA DE LIBRERIA "<< endl;
    cout << endl;
    if(anuncio.compare("") !=0){
    cout << "\t"<< anuncio << endl;} 
    cout << "\tNombre del archivo (.json): ";     
    cin >> path;
    if(!fexists(path)){
        system("cls");
        MensajeCarga("Archivo invalido o inexistente, intente de nuevo.");
    }   
}

 int main(){
    system ("cls");
    MensajeCarga("");
    system ("cls");
    Cargar(path);
    cout << "Libreria cargada con exito. Presione cualquier tecla para continuar";
    getch();
    menuPrincipal();
    return 0;
 }
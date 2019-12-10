#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "Json/json.hpp"
#include "ListaArtistas.cpp"

using namespace std;
using json = nlohmann::json;
string path; //String para guardar la dirección del archivo JSON
json libreria; //Variable Json para almacenar la libreria completa en formato json
json artistas; //Variable Json para almacenar los artistas en formato json
json albumes;  //Variable Json para almacenar los albumes en formato json
json canciones; //Variable Json para almacenar las canciones en formato json
ListaArtistas *lista_artistas = new ListaArtistas();

 void Cargar(string path){
    
   // cout << "----------------Informacion---------------" << endl;
    std::ifstream file(path);
    file >> libreria;
    artistas = libreria["Library"];// aqui obtenemos un arreglo con cada artista existente en la libreria
    for (const auto& artista : artistas){ //iterando en cada artista de la libreria
   /* std::cout << "Nombre del artista:" <<artista["Artist"]["Name"] << std::endl; //imprimimos el nombre de cada artista
    std::cout << endl;
    std::cout << "+++++++++++++++DISCOGRAFIA++++++++++++++++" << std::endl;*/
    albumes = artista["Artist"]["Albums"]; //aqui obtenemos un arreglo con cada album del artista actual.
        for(const auto& album : albumes ){      //iterando en cada album      
           /* std::cout << "Nombre del album:" <<album["Name"] << std::endl; //imprimimos el nombre de cada album
            std::cout << "Mes del album:" <<album["Month"] << std::endl; //imprimimos el mes de cada album
            std::cout << "Anio del album:" <<album["Year"] << std::endl; //imprimimos el año de cada album
            std::cout << endl;
            std::cout << endl;
            std::cout << "Canciones del album:" << std::endl;*/
            canciones = album["Songs"]; // aqui obtenemos un arreglo con cada canción del album
            
                for(const auto& cancion : canciones){
                    /*std::cout << "Nombre de la cancion:" <<cancion["Name"] << std::endl; //imprimimos el nombre de cada cancion
                    std::cout << "Rating de la cancion:" <<cancion["Rating"] << std::endl; //imprimimos el rating de cada cancion
                    std::cout << endl;*/
                }
            //std::cout << "........................................" << std::endl;
        }

    }
 }

 void sleepcp(int milliseconds) // Función para pausar ejecución
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

 int main(){
    system ("cls");
    cout << "---------------\"Bienvenido a Music++\"---------------"<< endl;
    cout << endl;
    cout << "Ingrese el nombre del archivo JSON para cargar libreria:" << endl;
    cin >> path;
    system ("cls");
    Cargar(path);
    cout<< "Libreria cargada con exito!" << endl;
    sleepcp(2000);
    cout << "Cerrando programa" << endl;
  
     return 0;
 }
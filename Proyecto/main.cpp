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
#include "ArbolPlaylists.cpp"

using namespace std;
using json = nlohmann::json;
string path; //String para guardar la dirección del archivo JSON
json libreria; //Variable Json para almacenar la libreria completa en formato json
json artistas; //Variable Json para almacenar los artistas en formato json
json albumes;  //Variable Json para almacenar los albumes en formato json
json canciones; //Variable Json para almacenar las canciones en formato json
json playlist; //Variable Json para almacenar la playlist completa en formato json
ListaArtistas *lista_artistas = new ListaArtistas();
ListaCancionesOrdenada *lista_canciones = new ListaCancionesOrdenada(); //Lista global de canciones
ArbolPlaylists *arbol_playlists = new ArbolPlaylists(); //Arbol de playlists
string global_bst = "";
int nivel = 0;

 void sleepcp(int milliseconds) { // Función para pausar ejecución

    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

 bool TerminaCon(string fullString, string ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool EmpiezaCon(string fullString, string inicio){

    string a = fullString;
    std::for_each(a.begin(), a.end(), [](char & c) {
		c = ::tolower(c);});

    if (a.rfind("playlist_", 0) == 0) {
        return true;
        } else{
    return false;
    }
}

void BorrarSubStr(std::string & mainStr, const std::string & toErase){
	size_t pos = mainStr.find(toErase);
 
	if (pos != std::string::npos)
	{
		mainStr.erase(pos, toErase.length());
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


void GenerarAlbumReport(NodoCubo *n){
    std::ofstream outfile ("salida.dot");
    outfile << "digraph AlbumReport{" << endl;
    outfile << endl;
    outfile << "node[shape=record];" << endl;
    outfile << "rankdir=LR;" << endl;
    outfile << endl;
    int x = 1;
    NodoCancion *aux = n->getAlbum()->getSongs()->getPrimero();
    while(aux!=0){
            outfile << "node" << x <<"[label=\"{" << aux->getCancion()->getName() << "|}\"];" << endl;
            aux = aux->getSiguiente();
            x++;
        }
    outfile << "node" << x <<"[label=\"null\"];" << endl;
    outfile << endl;
    int count = 1;
        while(count < x){
            outfile << "node" << count << "->node" << count+1 << ";" << endl;
            count++;
        }
    outfile << "}" << endl;
    outfile.close();
    system("dot.exe -Tpng salida.dot -o AlbumReport.png");
    system("AlbumReport.png");

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

void DesplegarCanciones(NodoCubo *n){
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
                DesplegarCanciones(n);
            } else {
             DesplegarCanciones(n); 
            }
        }       
    } else {
        DesplegarCanciones(n);
    }
}

void DesplegarAlbums(NodoArtista *n, string motivo){
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
                if(motivo == "navegacion"){
                    DesplegarCanciones(album_aux);
                } else if(motivo == "reporte"){
                    GenerarAlbumReport(album_aux);
                }
                DesplegarAlbums(n,motivo);
            } else {
             DesplegarAlbums(n,motivo);  
            }
        }       
    } else {
        DesplegarAlbums(n,motivo);
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
    cout << "Ingrese el numero del artista deseado." << endl;
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
                DesplegarAlbums(n,"navegacion");
                menuArtistas();
            } else {
             menuArtistas();   
            }
        }       
    } else {
        menuArtistas();
    }

}

void AlbumReport(){
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
    cout << "Ingrese el numero del artista deseado." << endl;
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
                DesplegarAlbums(n,"reporte");
               AlbumReport();
            } else {
             AlbumReport();   
            }
        }       
    } else {
        AlbumReport();
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

void DiscographyReport(NodoArtista *n, string name){
    std::ofstream outfile ("salida.dot");
    outfile << "digraph DiscographyReport{" << endl;
    outfile << endl;
    outfile << "node[shape=box];" << endl;
    outfile << endl;
    outfile << "Mt[label=\"" << name << "\", width = 1.5, style = filled, fillcolor = green, group = 1 ];" << endl;
    NodoCubo *aux = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();
    int y = 0;
    string mes;
        while(aux!=0){
            switch(aux->getY()){
                case 1: mes = "Enero"; break;
                case 2: mes = "Febrero"; break;
                case 3: mes = "Marzo"; break;
                case 4: mes = "Abril"; break;
                case 5: mes = "Mayo"; break;
                case 6: mes = "Junio"; break;
                case 7: mes = "Julio"; break;
                case 8: mes = "Agosto"; break;
                case 9: mes = "Septiembre"; break;
                case 10: mes = "Octubre"; break;
                case 11: mes = "Noviembre"; break;
                case 12: mes = "Diciembre"; break;
                default: mes = "Unknown"; break;
            }
            outfile << "M" << y << "[label=\"" << mes << "\",width = 1.5, style = filled, fillcolor = darkslategrey, fontcolor = white, group = 1 ];" << endl;
            aux = aux ->getAdelante();
            y++;
        }
        outfile << endl;
        int count = 0;
        while(count<y-1){
            outfile << "M" << count << "-> M" << count+1 << "[dir=back];" << endl;
            outfile << "M" << count << "-> M" << count+1 << ";" << endl;
            count++;
        }
        outfile << endl;
    aux = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
        int group = 2;
        int x = 0;
        while(aux!=0){
         outfile << "A" << x << "[label=\"" << aux->getX() << "\", width = 1.5, style = filled, fillcolor = cornsilk, group = " << group << "];" << endl;   
         aux = aux ->getDerecha();
         x++;
         group++;
        }
    outfile << endl;
     count = 0;
        while(count<x-1){
            outfile << "A" << count << "-> A" << count+1 << "[dir=back];" << endl;
            outfile << "A" << count << "-> A" << count+1 << ";" << endl;
            count++;
        }
    outfile << endl;
    outfile << "Mt -> M0 [dir=back];" << endl;
    outfile << "Mt -> M0;" << endl;
    outfile << "Mt -> A0 [dir=back];" << endl;
    outfile << "Mt -> A0;" << endl;

    string rank = "{ rank = same; Mt;";
    count = 0;
        while(count<x){
            rank+="A"+to_string(count)+";";
            count++;
        }
    rank += "}";
    outfile << endl;
    outfile << rank << endl;
    outfile << endl;

    NodoCubo *fil;
    NodoCubo *col;
    y= 0;
    aux = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();
    while(aux!=0){
    fil = aux->getDerecha();
    col = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
    x = 0;    
    group = 2;
    while(fil!=0 && col!=0){    
        if(fil->getX() == col->getX()){
            outfile <<"M"<<y<<"A"<<x<<"[label = \"" <<fil->getAlbum()->getName()<<"\", width = 1.5, group ="<<group<<"];"<<endl;
            fil = fil->getDerecha();        
        }
        x++;
        group++;       
        col = col->getDerecha();       
    }
        y++;
        aux = aux -> getAdelante();
        outfile << endl;
    }

    bool primera_x;
    y = 0;
    aux = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();
    while(aux!=0){
    col = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
    fil = aux->getDerecha();
    x = 0;    
    primera_x = true;
    while(fil!=0 && col!=0){
            if(fil->getX() == col->getX()){
                 if(primera_x){
                primera_x = false;
                count = x;
                outfile << "M" << y << "-> M" << y << "A" << x << "[dir=back];" <<endl;
                outfile << "M" << y << "-> M" << y << "A" << x << ";" <<endl;               
                 } else {
                outfile<< "M" << y << "A" << count << "-> M" << y << "A" << x << "[dir=back];" <<endl;
                outfile<< "M" << y << "A" << count << "-> M" << y << "A" << x << ";" <<endl;
                count = x;
            }  
            col = col->getDerecha();
            fil = fil->getDerecha();
            x++;
            } else {
                col = col -> getDerecha();
                x++;
            }              
            }
        y++;
        aux = aux -> getAdelante();
        outfile << endl;
        }

    
    bool primera_y;
    x= 0;   
    aux = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
    while(aux!=0){
    fil = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();
    col = aux->getAdelante();  
    primera_y = true;
    y = 0;
    while(col!=0 && fil!=0){        
            if(col->getY() == fil->getY()){
                if(primera_y){
                primera_y = false;
                count = y;
                outfile << "A" << x << "-> M" << y << "A" << x << "[dir=back];" <<endl;
                outfile << "A" << x << "-> M" << y << "A" << x << ";" <<endl;
            } else {
                outfile << "M" << count << "A" << x << "-> M" << y << "A" << x << "[dir=back];" << endl;
                outfile << "M" << count << "A" << x << "-> M" << y << "A" << x << ";" << endl;
                count = y;
            }
            fil = fil ->getAdelante();                   
            col = col->getAdelante();      
            y++;               
            } else {
                fil = fil ->getAdelante();
                y++;  
            }                         
           }
        x++;
        aux = aux -> getDerecha();
        outfile << endl;
        }

    aux = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();    
    y = 0;
    while(aux!=0){
    col = col = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
    rank = "{ rank = same; M"+to_string(y)+";";
    fil = aux->getDerecha();
    x = 0;    
    while(fil!=0 && col!=0){

        if(fil->getX() == col->getX()){
            rank+="M"+to_string(y)+"A"+to_string(x)+";";
            col = col->getDerecha();                  
            fil = fil->getDerecha();
            x++; 
        }else {
          col = col->getDerecha();  
           x++; 
        }                
    }
        rank += "}";
        outfile << rank << endl;
        y++;
        aux = aux -> getAdelante();
    }

    bool primera_z;
    y= 0;
    aux = n->getArtista()->getDiscografia()->getRaiz()->getAdelante();
    while(aux!=0){
    fil = aux->getDerecha();
    col = n->getArtista()->getDiscografia()->getRaiz()->getDerecha();
    x = 0;    
    while(fil!=0 && col!=0){    
        if(fil->getX() == col->getX()){
            NodoCubo *a = fil->getArriba();
                primera_z = true;
                count = 0;
                while(a!=0){
                    if(primera_z){
                        primera_z = false;
                        outfile << "M" << y << "A" << x << "Z" << count << "[label=\"" << a->getAlbum()->getName() << "\", style = filled, fillcolor = yellow];" << endl;
                        outfile << "M" << y << "A" << x << "-> M" << y << "A" << x << "Z" << count << "[dir=back];" << endl;
                        outfile << "M" << y << "A" << x << "-> M" << y << "A" << x << "Z" << count << ";" << endl;
                    } else {
                        outfile << "M" << y << "A" << x << "Z" << count << "[label=\"" << a->getAlbum()->getName() << "\", style = filled, fillcolor = yellow];" << endl;
                        outfile << "M" << y << "A" << x << "Z" << count-1 << "-> M" << y << "A" << x << "Z" << count <<  "[dir=back];" << endl;
                        outfile << "M" << y << "A" << x << "Z" << count-1 << "-> M" << y << "A" << x << "Z" << count <<  ";" << endl;
                    }
                    a = a -> getArriba();
                    count++;
                }
            fil = fil->getDerecha();                   
        }
        x++;      
        col = col->getDerecha();       
    }
        y++;
        aux = aux -> getAdelante();
        outfile << endl;
    }


    

    outfile << "}" << endl;
    outfile.close();
    system("dot.exe -Tpng salida.dot -o DiscographyReport.png");
    system("DiscographyReport.png");
}

void SeleccionarArtista(){
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
    cout << "Ingrese el numero del artista deseado." << endl;
    } else {
    cout << endl;
    cout << "No hay artistas disponibles." << endl;
    }   
    cout << "s - Regresar a MyMusic++." << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;
    if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index <x){
                NodoArtista *n = lista_artistas->getArtista_Index(index);
                DiscographyReport(n, n->getArtista()->getName());                
                SeleccionarArtista();
            } else {
             SeleccionarArtista();   
            }
        }       
    } else {
        SeleccionarArtista();
    }

}

void ArtistsReport(){
    std::ofstream outfile ("salida.dot");
    outfile << "digraph ArtistsReport{" << endl;
    outfile << endl;
    outfile << "node[shape=record];" << endl;
    outfile << "rankdir=LR;" << endl;
    outfile << endl;
    outfile << "node0[label=\"null\"];" << endl;
    int x = 1;
    NodoArtista *aux = lista_artistas->getPrimero();
        while(aux!=0){
            outfile << "node" << x <<"[label=\"{|" << aux->getArtista()->getName() << "|}\"];" << endl;
            aux = aux->getSiguiente();
            x++;
        }
    outfile << "node" << x <<"[label=\"null\"];" << endl;
    outfile << endl;
    outfile << "node0->node1[dir=back]" << endl;
    int count = 1;
        while(count < x){
            outfile << "node" << count << "->node" << count+1 << ";" << endl;
            count++;
        }
    count = 1;
    while(count < x-1){
            outfile << "node" << count << "->node" << count+1 << "[dir=back];" << endl;
            count++;
        }
    outfile << "}" << endl;
    outfile.close();
    system("dot.exe -Tpng salida.dot -o ArtistaReport.png");
    system("ArtistReport.png");
}

void RecursiveBSTReport(NodoPlaylist *n, string &cadena){
  
    if(n!=0){
    
        cadena+= "nodo" + to_string(n->getNumero()) + "[label=\"" + n->getPlaylist()->getName() + "\"];\n";

        RecursiveBSTReport(n->getIzquierda(), cadena);
        RecursiveBSTReport(n->getDerecha(), cadena);

        if(n->getIzquierda()!=0){
        cadena+= "nodo" +to_string(n->getNumero()) + "-> nodo" + to_string(n->getIzquierda()->getNumero()) + ";\n";
        }

        if(n->getDerecha()!=0){
        cadena+= "nodo" +to_string(n->getNumero()) + "-> nodo" + to_string(n->getDerecha()->getNumero()) + ";\n";
        }
    }   
    
}


void PlaylistReport(){
    std::ofstream outfile ("salida.dot");
    outfile << "digraph PlaylistReport{" << endl;
    outfile << endl;
    outfile << "node[shape=oval];" << endl;
    global_bst = "";
    RecursiveBSTReport(arbol_playlists->getRaiz(), global_bst);
    outfile << endl;
    outfile << global_bst<< endl;
    outfile << endl;
    outfile << "}" << endl;
    outfile.close();
    system("dot.exe -Tpng salida.dot -o PlaylistsReport.png");
    system("PlaylistsReport.png");
}

void MyMusic(){
    system("cls");
    cout << "---------------\"[MY MUSIC++]\"---------------"<< endl;
    cout << endl;
    cout << "Que reporte desea ver?"<< endl;
    cout << endl;
    cout << "1. Artists Report\n2. Discography Report\n3. Album Report\n4. Playlists Report\n5. Top 5 Albums By Artist Report\n6. Top 5 Artists Report"<< endl;
    cout << endl;
    cout << "s - Regresar al menu principal." << endl;
    cout << ">>";
    char c = cin.get();
    switch (c){
        case '1': ArtistsReport();
                  MyMusic();
                  break;
        case '2': SeleccionarArtista();
                  MyMusic();
                  break;
        case '3': AlbumReport();
                  MyMusic();
                  break;
        case '4': PlaylistReport();
                  MyMusic();
                  break;
        case '5': break;
        case '6': break;
        case 's': break;
        default: MyMusic(); break;
    } 
     
}

void CargarPlaylist(string path){
    std::ifstream file(path);
    file >> playlist;
    string playlist_name = path;
    std::for_each(playlist_name.begin(), playlist_name.end(), [](char & c) {
		c = ::tolower(c);});
    BorrarSubStr(playlist_name,"playlist_");
    playlist_name = playlist_name.substr(0,playlist_name.length()-5);
    playlist_name[0] = toupper(playlist_name[0]);
    string tipo = playlist["Type"];  //obtenemos el tipo de playlist
    std::for_each(tipo.begin(), tipo.end(), [](char & c) {
		c = ::tolower(c);});
    Playlist *p = new Playlist(playlist_name, tipo);
    canciones = playlist["Songs"]; //obtenemos un arreglo con las canciones de la playlist
    srand(time(0));
    for(const auto& cancion : canciones){
        string year = cancion["Year"];
        int year_int;
        istringstream(year)>>year_int;
        string month = cancion["Month"];
        string album = cancion["Album"];
        string name = cancion["Song"];
        string artist = cancion["Artist"];
        if(lista_canciones->CancionExiste(year_int, month, album, name, artist)){
            if(tipo == "queue"){
                Cancion_Cola *c = new Cancion_Cola(name, album, artist, 0, year_int, month);
                p->getQueue()->enqueue(c);
            } else if(tipo == "stack"){
                Cancion_Pila *c = new Cancion_Pila(name, album, artist, 0, year_int, month);
                p->getStack()->push(c);
            } else if(tipo == "shuffle"){
                Cancion_Shuffle *c = new Cancion_Shuffle(name, album, artist, 0, year_int, month);
                if(p->getShuffle()->getSize()>0){
                    p->getShuffle()->insertar_en(c,rand()%(p->getShuffle()->getSize()+1));
                } else {
                    p->getShuffle()->insertar_inicio(c);
                }              
            } else if(tipo == "circular"){
                Cancion_Circular *c = new Cancion_Circular(name, album, artist, 0, year_int, month);
                p->getCircular()->insertar_final(c);
            }
        }       
    }
    arbol_playlists->insertar(p);
}

void MensajeCargaPlaylist(string anuncio){
    system("cls");
    cout << "---------------------[MUSIC ++]---------------------"<< endl;
    cout << endl;
    cout << "\t\t CARGA DE PLAYLIST "<< endl;
    cout << endl;
    if(anuncio.compare("") !=0){
    cout << "\t"<< anuncio << endl;} 
    cout << "Ingrese nombre del archivo (.json) o 's' para cancelar " << endl;
    cout << endl;
    cout << "\t\t>>";
    cin >> path;
    if (path == "s") {
        return;
    } else if(fexists(path) && EmpiezaCon(path,"playlist_") && TerminaCon(path,".json")){
        CargarPlaylist(path);
    }  else {
        system("cls");
        MensajeCargaPlaylist("Archivo invalido o inexistente, intente de nuevo.");
    }
}

void DesplegarCancionesPlaylist(NodoPlaylist *n){
system("cls");
    string name_aux = n->getPlaylist()->getName();
    std::for_each(name_aux.begin(), name_aux.end(), [](char & c) {
	c = ::toupper(c);});
    cout << "---------------\"["<<name_aux<<"]\"---------------"<< endl;
    cout << endl;
    string c;
    cin >> c;



}

void DesplegarPlaylists(){
system("cls");
cout << "---------------\"[MY PLAYLISTS]\"---------------"<< endl;
cout << endl;
if(!arbol_playlists->EstaVacio()){ 
    arbol_playlists->inorder();
    cout << endl;
    cout << "Ingrese el numero de la playlist deseada." << endl;
} else {   
    cout << "\t\tNo hay playlists disponibles." << endl;
    cout << endl;
}
cout << "s - Regresar al menu principal." << endl;
cout << ">>";
string opcion;
cin >> opcion;

if(opcion == "s" || is_number(opcion)){
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            if(index >0 && index < arbol_playlists->getCount()){
              NodoPlaylist *aux = arbol_playlists->getInorderNode(index);
              DesplegarCancionesPlaylist(aux);
              DesplegarPlaylists(); 
            } else {
             DesplegarPlaylists();   
            }
        }       
    } else {
        DesplegarPlaylists();
    }

}

void menuPrincipal(){
    system("cls");
    cout << "---------------\"[MENU]\"---------------"<< endl;
    cout << endl;
    cout << "Que desea hacer?"<< endl;
    cout << endl;
    cout << "1. Ver artistas\n2. Ver canciones\n3. Ver playlists\n4. Importar playlists\n5. My Music++\n6. Salir"<< endl;
    cout << endl;
    cout << ">>";
    string opcion;
    cin >> opcion;
        if(is_number(opcion)){
            int index;
            istringstream(opcion)>>index;
            switch (index){
        case 1:   menuArtistas();
                  menuPrincipal();
                  break;
        case 2:   menuCanciones();
                  menuPrincipal();
                  break;
        case 3:   DesplegarPlaylists();
                  menuPrincipal();
                  break;
        case 4:   MensajeCargaPlaylist("");
                  menuPrincipal();
                  break;
        case 5:   MyMusic(); 
                  menuPrincipal(); 
                  break;
        case 6: break;
        default:  menuPrincipal(); break;
    } 
        }  else {
        menuPrincipal();
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
    if(!fexists(path) && TerminaCon(path,".json")){
        system("cls");
        MensajeCarga("Archivo invalido o inexistente, intente de nuevo.");
    }  
}

 int main(){
    system ("cls");
    MensajeCarga("");
    system ("cls");
    Cargar(path);
    system ("cls");
    cout << "Libreria cargada con exito. Presione cualquier tecla para continuar";
    getch();
    menuPrincipal();
    return 0;
 }
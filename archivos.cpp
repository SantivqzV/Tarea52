/**
 * Santiago Vázquez - A01177850
 * Adrian Gomez - A00835254
 * Saul Ortega Figueroa - A01252717 
 * v1
 * 
 * Fecha de creación: 20/11/2023
 * Fecha de modificación: 22/11/2023
 * 
 * Descripción: 
 * Implementación de un programa para comparar archivos mediante hashes SHA-1, SHA-256 y SHA-512
 * Calcula los hashes de dos archivos y los compara para determinar si son iguales o no. Los 
 * casos de prueba a utilizar nos enseñan 4 casos con diferentes tamaños de documentos y la comparación
 * de los mismos al cambiar una letra. 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "SHA1.h"
#include "SHA256.h"
#include "SHA512.h"

using namespace std;

/**
 * @brief Comparación de archivos
 * 
 * Este métdodo compara el hash de 2 archivos y nos dice si son iguales o no
 * 
 * @param string hashArchivo1
 * @param string hashArchivo2
 * @return Indicación si los archivos son o no son iguales
 * 
 * @note Complejidad de tiempo: O(1)
 * @note Complejidad de espacio: O(1)
*/
void comparar(string hashArchivo1, string hashArchivo2){
    if(hashArchivo1 == hashArchivo2){
        cout << "Los archivos son iguales" << endl;
    }else{
        cout << "Los archivos son diferentes" << endl;
    }
}

/**
 * @brief Leer el contenido del archivo y devolverlo como una cadena
 * 
 * @param char nombreArchivo, nombre del archivo a leer.
 * @return Contenido del archivo como una string
 * 
 * @note Complejidad de tiempo: O(n)
 * @note Comepljidad de espacio: O(1)
*/
string leerArchivo(const char *nombreArchivo){
    //Definir variable para almacenar el contenido del archivo
    string contenidoArchivo;

    //Leer el contenido del archivo
    ifstream archivo(nombreArchivo);
    if(archivo.is_open()){
        getline(archivo, contenidoArchivo);
        archivo.close();
    }else{
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }

    return contenidoArchivo;
}

/**
 * @brief Calcula y compara los hashes SHA-1, SHA-256 y SHA-512 de dos archivos.
 * 
 * Lee el contenido de los dos archivos, calcula sus hashes utilizando SHA-1, SHA-256 y HSA-512
 * y los compara para determinar si son iguales o diferentes
 * 
 * @param char nombreArchivo1, nombre del primer archivo
 * @param char nombreArchivo2, nombre del segundo archivo
 * 
 * @note Complejidad de tiempo: O(n)
 * @note Comepljidad de espacio: O(1)
*/
void hashear(const char* nombreArchivo1, const char* nombreArchivo2){
    //Definir variables para almacenar el contenido de los archivos
    string contenidoArchivo1, contenidoArchivo2;

    //Leer el contenido del primer archivo
    contenidoArchivo1 = leerArchivo(nombreArchivo1);

    //Leer el contenido del segundo archivo
    contenidoArchivo2 = leerArchivo(nombreArchivo2);

    //Hashear el contenido de los archivos usando OpenSSL SHA-512
    string hashArchivo1 = sha512(contenidoArchivo1);
    string hashArchivo2 = sha512(contenidoArchivo2);

    //Imprimir el contenido hasheado de los archivos
    cout << "SHA512" << endl;
    cout << "Hash del archivo " << nombreArchivo1 << ": " << hashArchivo1 << endl;
    cout << "Hash del archivo " << nombreArchivo2 << ": " << hashArchivo2 << endl;

    //Comparar los hashes
    comparar(hashArchivo1, hashArchivo2);

    //Hashear el contenido de los archivos usando OpenSSL SHA-256
    hashArchivo1 = sha256(contenidoArchivo1);
    hashArchivo2 = sha256(contenidoArchivo2);

    //Imprimir el contenido hasheado de los archivos
    cout << endl << "Sha256" << endl;
    cout << "Hash del archivo " << nombreArchivo1 << ": " << hashArchivo1 << endl;
    cout << "Hash del archivo " << nombreArchivo2 << ": " << hashArchivo2 << endl;

    //Comparar los hashes
    comparar(hashArchivo1, hashArchivo2);

    //Hashear el contenido de los archivos usando OpenSSL SHA-1
    hashArchivo1 = sha1(contenidoArchivo1);
    hashArchivo2 = sha1(contenidoArchivo2);

    //Imprimir el contenido hasheado de los archivos
    cout << endl << "Sha1" << endl;
    cout << "Hash del archivo " << nombreArchivo1 << ": " << hashArchivo1 << endl;
    cout << "Hash del archivo " << nombreArchivo2 << ": " << hashArchivo2 << endl;

    //Comprar los hashes
    comparar(hashArchivo1, hashArchivo2);
}


int main(){
    //Nombre de los archivos
    const char *nombreArchivo1 = "a.txt";
    const char *nombreArchivo2 = "b.txt";

    hashear(nombreArchivo1, nombreArchivo2);

}
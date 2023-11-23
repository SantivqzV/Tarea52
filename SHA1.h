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
 * Este archivo contiene la implementación de la función de hash SHA-1
 * 
 * Demuestra el uso del algoritmo usando librerias de OPENSSL para generar un hash a partir de 
 * la cadena dada. La función "sha1" calcula y devuelve el hash SHA-1. 
 *
 * Referencias:
 * OpenSSL Foundation, Inc. (n.d.-a). /docs/man3.0/man3/SHA1.html. https://www.openssl.org/docs/man3.0/man3/SHA1.html
 * How to generate a SHA1 hash in C++. (2015, February 9). PragmaticJoe. https://pragmaticjoe.gitlab.io/posts/2015-02-09-how-to-generate-a-sha1-hash-in-c/
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;


/**
 * @brief Calcula el hash SHA-1 de la cadena dada
 * 
 * Esta función inicializa una estructura SHA_CTX, procesa la cadena para calcular su SHA-1 
 * y luego devuelve el cálculo del hash. 
 * 
 * @param string input, string a ser hasheado
 * @return string con el valor del hash. 
 * 
 * @note Complejidad de tiempo: O(n)
 * @note Complejidad de espacio: O(1)
*/
string sha1(const string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, input.c_str(), input.length());
    SHA1_Final(hash, &sha1);

    stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

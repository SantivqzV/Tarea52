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
 * Este archivo incluye la implementación de una función para calcular el hash SHA-256 de una 
 * string dada. La función convierte la cadena en un hash de tipo SHA-256 y lo devuelve.
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

/**
 * @brief Calcular el hash SHA-256
 * 
 * Esta función inicializa una estructura SHA256-CTX, procesa la cadena y calcula el hash SHA256.
 * Luego finaliza el cáluclo y lo devuelve. 
 * 
 * @param string input, string a ser hasheado
 * @return string con el valor del hash
 * 
 * @note Complejidad de tiempo: O(n)
 * @note Complejidad de espacio: O(1)
*/
string sha256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}
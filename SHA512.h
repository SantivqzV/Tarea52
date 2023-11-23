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
 * Este archivo incluye la implementación de una función para calcular el hash SHA-512 de una 
 * string dada. La función convierte la cadena en un hash de tipo SHA-512 y lo devuelve.
 * 
 * Referencias:
 * https://stackoverflow.com/questions/59112701/sha512-c-program-using-the-openssl-library
 * OpenSSL Foundation, Inc. (n.d.-a). /docs/man1.0.2/man3/SHA512.html. https://www.openssl.org/docs/man1.0.2/man3/SHA512.html
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

/**
 * @brief Calcular el hash SHA-512
 * 
 * Esta función inicializa una estructura SHA512-CTX, procesa la cadena y calcula el hash SHA512.
 * Luego finaliza el cáluclo y lo devuelve. 
 * 
 * @param string input, string a ser hasheado
 * @return string con el valor del hash
 * 
 * @note Complejidad de tiempo: O(n)
 * @note Complejidad de espacio: O(1)
*/
string sha512(const string& input) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, input.c_str(), input.length());
    SHA512_Final(hash, &sha512);

    stringstream ss;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

#include <iostream>
#include <fstream>
#include <string>
#include <openssl/sha.h>

// La función sha1 toma una cadena de entrada y devuelve su hash SHA1 como una cadena hexadecimal.
//En la función main, el código comienza definiendo dos variables para almacenar el contenido de dos archivos.
//Luego, se leen los contenidos de los archivos a.txt y b.txt utilizando la biblioteca fstream
//Si los archivos se abren correctamente, se lee su contenido y se almacena en las variables correspondientes
//Si no se pueden abrir los archivos, se imprime un mensaje de error y se devuelve un código de error.
//Se llama a la función sha1 para calcular el hash SHA-1 del contenido de cada archivo. Los hashes se almacenan en dos variables separadas.
//Finalmente, se comparan los hashes de los dos archivos. Si son iguales, se imprime un mensaje indicando que los archivos son iguales.
//Si son diferentes, se imprime un mensaje indicando que los archivos son diferentes.
// La complejidad radica en la lectura de archivos y en la comparación de los hashes de los archivos.

std::string sha1(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, input.c_str(), input.length());
    SHA1_Final(hash, &sha1);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

int main() {
    // Definir variables para almacenar el contenido de los archivos
    std::string contenidoArchivo1, contenidoArchivo2;

    // Nombre de los archivos
    const char *nombreArchivo1 = "a.txt";
    const char *nombreArchivo2 = "b.txt";

    // Leer el contenido del primer archivo
    std::ifstream archivo1(nombreArchivo1);
    if (archivo1.is_open()) {
        getline(archivo1, contenidoArchivo1);
        archivo1.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo1 << std::endl;
        return 1; // Devolver código de error
    }

    // Leer el contenido del segundo archivo
    std::ifstream archivo2(nombreArchivo2);
    if (archivo2.is_open()) {
        getline(archivo2, contenidoArchivo2);
        archivo2.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo2 << std::endl;
        return 1; // Devolver código de error
    }

    // Hashear el contenido de los archivos usando OpenSSL SHA-1
    std::string hashArchivo1 = sha1(contenidoArchivo1);
    std::string hashArchivo2 = sha1(contenidoArchivo2);

    // Imprimir el contenido hasheado de los archivos
    std::cout << "Hash del archivo " << nombreArchivo1 << ": " << hashArchivo1 << std::endl;
    std::cout << "Hash del archivo " << nombreArchivo2 << ": " << hashArchivo2 << std::endl;

    // Comparar los hashes
    if (hashArchivo1 == hashArchivo2) {
        std::cout << "Los archivos son iguales." << std::endl;
    } else {
        std::cout << "Los archivos son diferentes." << std::endl;
    }

    return 0; // Salida exitosa
}

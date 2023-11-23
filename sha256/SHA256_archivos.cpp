#include <iostream>
#include <fstream>
#include <string>
#include <openssl/sha.h>

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
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

    // Hashear el contenido de los archivos usando OpenSSL SHA256
    std::string hashArchivo1 = sha256(contenidoArchivo1);
    std::string hashArchivo2 = sha256(contenidoArchivo2);

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

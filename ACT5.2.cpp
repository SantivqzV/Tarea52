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
 * Este programa implementa un sistema básico de autenticación de usuarios utilizando
 * hashing de contraseñas con sal y estiramiento de claves. Este código contiene métodos para
 * registrar y autenticar el usuario al igual que utiliza el hash de tipo SHA256 para 
 * asegurar la seguridad de la información sensible de los usuarios como lo es la contraseña. 
 *
 * Referencias:
 * How to include OpenSSL in Visual Studio. (n.d.). Stack Overflow. https://stackoverflow.com/questions/32156336/how-to-include-openssl-in-visual-studio
 * OpenSSL Foundation, Inc. (n.d.). /source/index.html. https://www.openssl.org/source/
 * Mutual authentication always succeeds with OpenSSL. (n.d.). Stack Overflow. https://stackoverflow.com/questions/28392273/mutual-authentication-always-succeeds-with-openssl
 * https://chat.openai.com/share/0b09d2dc-2647-43db-b915-b9975edf79d9
 */
#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>

using namespace std;

/**
 * @class User
 * 
 * @brief Representa un usuario con su username, hash de contraseña y sal
 * 
 * Esta clase almacena el nombre de usuario, el hash de la contraseña y la sal utilizada para 
 * el hashing de la contraseña del usuario
 * 
 * @param string username, nombre del usuario
 * @param string passwordHash, hash de la contraseña
 * @param string salt, sal utilizada para le hash
*/
class User {
public:
    string username;
    string passwordHash;
    string salt;
};

/**
 * @class AuthenticationSystem
 * 
 * @brief Gestiona la autenticación de usuarios
 * 
 * Esta clase maneja las operaciones de registro y autenticación de usuarios. 
 * Utilizando Hashing de contraseña con sal y estiramiento de claves para mejorar la seguridad.
 * 
 * @param vector<User> users, almacena los usuarios registrados
*/
class AuthenticationSystem {
private:
    vector<User> users;

public:
    void registerUser(const string& username, const string& password);
    bool authenticateUser(const string& username, const string& password);
    string generateSalt();
    string hashPassword(const string& password, const string& salt);
};

/**
 * @brief Registra un nuevo usuario.
 * 
 * Registra un usuario tomando un nombre de usuario y una contraseña, genera una sal,
 * hashea la contraseña con esta sal y almacena el nuevo usuario.
 * 
 * @param username Nombre de usuario.
 * @param password Contraseña del usuario.
 * 
 * @note Complejidad de tiempo: O(n) - depende de la longitud de la contraseña.
 * @note Complejidad de espacio: O(1) - uso de memoria constante.
 */
void AuthenticationSystem::registerUser(const string& username, const string& password) {
    User newUser;
    newUser.username = username;
    newUser.salt = generateSalt();
    newUser.passwordHash = hashPassword(password, newUser.salt);
    users.push_back(newUser);

    cout << "User registered successfully.\n";
}

/**
 * @brief Autentica un usuario existente.
 * 
 * Comprueba si un nombre de usuario existe y si la contraseña proporcionada coincide con la almacenada.
 * 
 * @param username Nombre de usuario.
 * @param password Contraseña del usuario.
 * @return true si la autenticación es exitosa, false en caso contrario.
 * 
 * @note Complejidad de tiempo: O(n*m) - n es el número de usuarios y m la longitud de la contraseña.
 * @note Complejidad de espacio: O(1) - uso de memoria constante.
 *
*/
bool AuthenticationSystem::authenticateUser(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username) {
            // Hashea la contraseña proporcionada para compararla con la almacenada
            std::string hashedPasswordAttempt = hashPassword(password, user.salt);

            // Compara las contraseñas hasheadas
            if (hashedPasswordAttempt == user.passwordHash) {
                std::cout << "Inicio de sesión exitoso.\n";
                std::cout << "Contraseña Login hasheada: " << user.passwordHash << "\n";
                std::cout << "Contraseña Registro hasheada: " << hashedPasswordAttempt << "\n";
                return true;
            } else {
                std::cout << "Contraseña incorrecta para el usuario: " << username << "\n";
                std::cout << "Contraseña hasheada: " << hashedPasswordAttempt << "\n";
                return false;
            }
        }
    }
    return false;
}

/**
 * @brief Genera una cadena de sal aleatoria.
 * 
 * Utiliza RAND_bytes para generar una sal aleatoria de tamaño fijo.
 * 
 * @return Una cadena representando la sal generada.
 * 
 * @note Complejidad de tiempo: O(1) - tiempo constante.
 * @note Complejidad de espacio: O(1) - uso de memoria constante.
 */
string AuthenticationSystem::generateSalt() {
    const int saltSize = 16;
    unsigned char buffer[saltSize];
    RAND_bytes(buffer, saltSize);

    string salt;
    for (int i = 0; i < saltSize; ++i) {
        salt += buffer[i];
    }

    return salt;
}

/**
 * @brief Genera el hash de una contraseña con sal.
 * 
 * Combina la contraseña y la sal y utiliza PKCS5_PBKDF2_HMAC para crear un hash seguro.
 * 
 * @param password Contraseña a hashear.
 * @param salt Sal a utilizar.
 * @return El hash de la contraseña.
 * 
 * @note Complejidad de tiempo: O(n) - n es el número de iteraciones del estiramiento de clave.
 * @note Complejidad de espacio: O(1) - uso de memoria constante.
 */
string AuthenticationSystem::hashPassword(const string& password, const string& salt) {
    const int iterations = 10000; // Number of iterations for stretching
    const EVP_MD* md = EVP_sha256();

    string dataToHash = password + salt;
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), 
                      reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(),
                      iterations, md, SHA256_DIGEST_LENGTH, hashedPassword);

    string hashedPasswordStr;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        char buf[3];
        sprintf(buf, "%02x", hashedPassword[i]);
        hashedPasswordStr += buf;
    }

    return hashedPasswordStr;
}

int main(){
    AuthenticationSystem authSystem;

    // Registro de usuario
    authSystem.registerUser("usuario1", "contraseña123");

    // Intento de autenticación
    string usernameAttempt;
    string passwordAttempt;

    cout << "Ingrese el nombre de usuario: ";
    cin >> usernameAttempt;

    cout << "Ingrese la contraseña: ";
    cin >> passwordAttempt;

    if (authSystem.authenticateUser(usernameAttempt, passwordAttempt)) {
        cout << "Inicio de sesión exitoso.\n";
    } else {
        cout << "Nombre de usuario o contraseña incorrectos.\n";
    }

    return 0;
}

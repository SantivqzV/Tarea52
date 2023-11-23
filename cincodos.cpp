#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string passwordHash;
    string salt;
};

class AuthenticationSystem {
private:
    vector<User> users;

public:
    void registerUser(const string& username, const string& password);
    bool authenticateUser(const string& username, const string& password);
    string generateSalt();
    string hashPassword(const string& password, const string& salt);
};

void AuthenticationSystem::registerUser(const string& username, const string& password) {
    User newUser;
    newUser.username = username;
    newUser.salt = generateSalt();
    newUser.passwordHash = hashPassword(password, newUser.salt);
    users.push_back(newUser);

    cout << "User registered successfully.\n";
}

bool AuthenticationSystem::authenticateUser(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username) {
            string hashedPasswordAttempt = hashPassword(password, user.salt);
            return (hashedPasswordAttempt == user.passwordHash);
        }
    }
    return false;
}

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

int main() {
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
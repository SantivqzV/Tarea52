#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>

class User {
public:
    std::string username;
    std::string passwordHash;
    std::string salt;
};

class AuthenticationSystem {
private:
    std::vector<User> users;

public:
    void registerUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    std::string generateSalt();
    std::string hashPassword(const std::string& password, const std::string& salt);
};

void AuthenticationSystem::registerUser(const std::string& username, const std::string& password) {
    User newUser;
    newUser.username = username;
    newUser.salt = generateSalt();
    newUser.passwordHash = hashPassword(password, newUser.salt);
    users.push_back(newUser);

    std::cout << "User registered successfully.\n";
}

bool AuthenticationSystem::authenticateUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username) {
            std::string hashedPasswordAttempt = hashPassword(password, user.salt);
            return (hashedPasswordAttempt == user.passwordHash);
        }
    }
    return false;
}

std::string AuthenticationSystem::generateSalt() {
    const int saltSize = 16;
    unsigned char buffer[saltSize];
    RAND_bytes(buffer, saltSize);

    std::string salt;
    for (int i = 0; i < saltSize; ++i) {
        salt += buffer[i];
    }

    return salt;
}

std::string AuthenticationSystem::hashPassword(const std::string& password, const std::string& salt) {
    const int iterations = 10000; // Number of iterations for stretching
    const EVP_MD* md = EVP_sha256();

    std::string dataToHash = password + salt;
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), 
                      reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(),
                      iterations, md, SHA256_DIGEST_LENGTH, hashedPassword);

    std::string hashedPasswordStr;
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
    std::string usernameAttempt;
    std::string passwordAttempt;

    std::cout << "Ingrese el nombre de usuario: ";
    std::cin >> usernameAttempt;

    std::cout << "Ingrese la contraseña: ";
    std::cin >> passwordAttempt;

    if (authSystem.authenticateUser(usernameAttempt, passwordAttempt)) {
        std::cout << "Inicio de sesión exitoso.\n";
    } else {
        std::cout << "Nombre de usuario o contraseña incorrectos.\n";
    }

    return 0;
}

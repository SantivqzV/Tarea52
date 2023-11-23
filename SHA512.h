#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

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

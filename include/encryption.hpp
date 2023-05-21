#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

class Encryption {
private:
    static std::string privateKey;
    static std::string publicKey;

    static RSA* createRSAKey(const std::string& key, bool isPublicKey);
    static std::string encryptRSA(const std::string& message, RSA* rsaKey);
    static std::string decryptRSA(const std::string& encryptedMessage, RSA* rsaKey);

public:
    static std::string encrypt(const std::string& message, const std::string& publicKey);
    static std::string decrypt(const std::string& encryptedMessage, const std::string& privateKey);
    static std::string decrypt(const std::string& encryptedMessage);
    static std::string getPrivateKey();
    static std::string getPublicKey();
    static std::vector<std::string> generateKeypair();
};

#endif // ENCRYPTION_HPP

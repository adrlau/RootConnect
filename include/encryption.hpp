#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <iostream>
#include <string>

class Encryption {
private:
    static std::string privateKey;
    static std::string publicKey;

public:
    static std::string encrypt(const std::string& message, const std::string& publicKey);
    static std::string decrypt(const std::string& encryptedMessage);
    static std::string getPrivateKey();
    static std::string getPublicKey();
    static void generateKeypair();
};

#endif // ENCRYPTION_HPP

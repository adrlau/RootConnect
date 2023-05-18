/**
 * please note that this code is not secure and should not be used for real encryption purposes. 
 * It's only intended for demonstration purposes, and is not secure enough to be used in production.
*/

#include "encryption.hpp"
#include <iostream>
#include <random>

std::string Encryption::privateKey = "YourPrivateEncryptionKey";
std::string Encryption::publicKey = "YourPublicEncryptionKey";

std::string Encryption::encrypt(const std::string& message, const std::string& publicKey) {
    std::string encryptedMessage;
    for (size_t i = 0; i < message.size(); ++i) {
        encryptedMessage += message[i] ^ publicKey[i % publicKey.size()];
    }
    return encryptedMessage;
}

std::string Encryption::decrypt(const std::string& encryptedMessage) {
    std::string privateKey = getPrivateKey();
    std::string decryptedMessage;
    for (size_t i = 0; i < encryptedMessage.size(); ++i) {
        decryptedMessage += encryptedMessage[i] ^ privateKey[i % privateKey.size()];
    }
    return decryptedMessage;
}

std::string Encryption::getPrivateKey() {
    return privateKey;
}

std::string Encryption::getPublicKey() {
    return publicKey;
}

void Encryption::generateKeypair() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<char> distribution('A', 'Z');

    privateKey = "";
    publicKey = "";
    for (int i = 0; i < 16; ++i) {
        privateKey += distribution(gen);
        publicKey += distribution(gen);
    }

    std::cout << "Generated Keypair:" << std::endl;
    std::cout << "Private Key: " << privateKey << std::endl;
    std::cout << "Public Key: " << publicKey << std::endl;
}

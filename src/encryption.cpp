#include <iostream>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "encryption.hpp"

std::string Encryption::privateKey;
std::string Encryption::publicKey;

std::string Encryption::encrypt(const std::string& message, const std::string& publicKey) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char* ciphertext = new unsigned char[message.size() + EVP_MAX_BLOCK_LENGTH];
    int ciphertextLength = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(publicKey.c_str()), NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, reinterpret_cast<const unsigned char*>(message.c_str()), message.size());
    int finalLength;
    EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &finalLength);
    ciphertextLength += finalLength;

    std::string encryptedMessage(reinterpret_cast<char*>(ciphertext), ciphertextLength);

    delete[] ciphertext;
    EVP_CIPHER_CTX_free(ctx);

    return encryptedMessage;
}


std::string Encryption::decrypt(const std::string& encryptedMessage) {
    return decrypt(encryptedMessage, privateKey);
}

std::string Encryption::decrypt(const std::string& encryptedMessage, const std::string& privateKey) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char* plaintext = new unsigned char[encryptedMessage.size() + EVP_MAX_BLOCK_LENGTH];
    int plaintextLength = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(privateKey.c_str()), NULL);
    EVP_DecryptUpdate(ctx, plaintext, &plaintextLength, reinterpret_cast<const unsigned char*>(encryptedMessage.c_str()), encryptedMessage.size());
    int finalLength;
    EVP_DecryptFinal_ex(ctx, plaintext + plaintextLength, &finalLength);
    plaintextLength += finalLength;

    std::string decryptedMessage(reinterpret_cast<char*>(plaintext), plaintextLength);

    delete[] plaintext;
    EVP_CIPHER_CTX_free(ctx);

    return decryptedMessage;
}

std::string Encryption::getPrivateKey() {
    return privateKey;
}

std::string Encryption::getPublicKey() {
    return publicKey;
}

std::vector<std::string> Encryption::generateKeypair() {
    unsigned char buffer[32];
    RAND_bytes(buffer, sizeof(buffer));

    privateKey = std::string(reinterpret_cast<char*>(buffer), sizeof(buffer));
    publicKey = std::string(reinterpret_cast<char*>(buffer), sizeof(buffer));
    return {privateKey, publicKey};
}

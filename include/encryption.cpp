#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>


/*
* This class is used to encrypt and decrypt messages sent over the network.
It is used by the Message class to encrypt and decrypt the content of the message.

Currently it is not properly implemented and is only a placeholder.
*/

class Encryption {
private:
    static std::string privateKey;
    static std::string publicKey;

public:
    static std::string encrypt(const std::string& message, const std::string& publicKey) { //publicKey is the encryption key of the node you are sending the message to
        RSA* rsa = RSA_new();
        BIO* publicKeyBio = BIO_new_mem_buf(publicKey.c_str(), -1);

        // Read the public key from the BIO
        if (!PEM_read_bio_RSAPublicKey(publicKeyBio, &rsa, nullptr, nullptr)) {
            std::cerr << "Error reading public key" << std::endl;
            return "";
        }

        // Encrypt the message using RSA_public_encrypt
        std::string encryptedMessage(RSA_size(rsa), '\0');
        int encryptedLength = RSA_public_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()), reinterpret_cast<unsigned char*>(encryptedMessage.data()), rsa, RSA_PKCS1_PADDING);

        // Check if the encryption was successful
        if (encryptedLength == -1) {
            std::cerr << "Error encrypting message" << std::endl;
            return "";
        }

        // Resize the encrypted message to the actual length
        encryptedMessage.resize(encryptedLength);

        // Cleanup
        RSA_free(rsa);
        BIO_free(publicKeyBio);
        return encryptedMessage;
    }

        static std::string decrypt(const std::string& encryptedMessage) {
        std::string privateKey = getPrivateKey();
        RSA* rsa = RSA_new();
        BIO* privateKeyBio = BIO_new_mem_buf(privateKey.c_str(), -1);

        // Read the private key from the BIO
        if (!PEM_read_bio_RSAPrivateKey(privateKeyBio, &rsa, nullptr, nullptr)) {
            std::cerr << "Error reading private key" << std::endl;
            return "";
        }

        // Decrypt the encrypted message using RSA_private_decrypt
        std::string decryptedMessage(RSA_size(rsa), '\0');
        int decryptedLength = RSA_private_decrypt(encryptedMessage.size(), reinterpret_cast<const unsigned char*>(encryptedMessage.data()), reinterpret_cast<unsigned char*>(decryptedMessage.data()), rsa, RSA_PKCS1_PADDING);

        // Check if the decryption was successful
        if (decryptedLength == -1) {
            std::cerr << "Error decrypting message" << std::endl;
            return "";
        }

        // Resize the decrypted message to the actual length
        decryptedMessage.resize(decryptedLength);

        // Cleanup
        RSA_free(rsa);
        BIO_free(privateKeyBio);

        return decryptedMessage;
    }



    static std::string getPrivateKey() {
        // Get the encryption key from storage
        return privateKey;
    }

    static std::string getPublicKey() {
        // Get the encryption key from storage
        return publicKey;
    }

    static void generateKeypair() {
        RSA* rsa = RSA_new();
        BIGNUM* bne = BN_new();
        int bits = 2048; // Key size in bits

        // Generate a new keypair using RSA
        if (RSA_generate_key_ex(rsa, bits, bne, nullptr)) {
            // Convert the keypair to PEM format
            BIO* privateKeyBio = BIO_new(BIO_s_mem());
            PEM_write_bio_RSAPrivateKey(privateKeyBio, rsa, nullptr, nullptr, 0, nullptr, nullptr);

            // Get the private key from the BIO
            BUF_MEM* privateKeyMem;
            BIO_get_mem_ptr(privateKeyBio, &privateKeyMem);

            // Extract the private key as a string
            std::string privateKey(privateKeyMem->data, privateKeyMem->length);

            // Convert the public key to PEM format
            BIO* publicKeyBio = BIO_new(BIO_s_mem());
            PEM_write_bio_RSAPublicKey(publicKeyBio, rsa);

            // Get the public key from the BIO
            BUF_MEM* publicKeyMem;
            BIO_get_mem_ptr(publicKeyBio, &publicKeyMem);

            // Extract the public key as a string
            std::string publicKey(publicKeyMem->data, publicKeyMem->length);

            // Do something with the generated keypair
            std::cout << "Generated Keypair:" << std::endl;
            std::cout << "Private Key: " << privateKey << std::endl;
            std::cout << "Public Key: " << publicKey << std::endl;

            //update keys
            Encryption::privateKey = privateKey;
            Encryption::publicKey = publicKey;

            // Cleanup
            RSA_free(rsa);
            BN_free(bne);
            BIO_free(privateKeyBio);
            BIO_free(publicKeyBio);
        } else {
            std::cerr << "Error generating keypair" << std::endl;
        }
    }
};

std::string Encryption::privateKey = "YourPrivateEncryptionKey";
std::string Encryption::publicKey = "YourPublicEncryptionKey";

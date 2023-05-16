#include <iostream>
#include <string>



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
        std::string encryptedMessage;
        encryptedMessage = message + ":" + encryptionKey;
        // Implement encryption algorithm using the encryptionKey
        // Example: encryptedMessage = performEncryption(message, encryptionKey)
        return encryptedMessage;
    }

    static std::string decrypt(const std::string& encryptedMessage) { //privateKey is the encryption key of the node you are sending the message to
        std::string decryptedMessage;
        size_t lastColonPos = encryptedMessage.find_last_of(":");
        decryptedMessage = encryptedMessage.substr(0, lastColonPos);
        // Implement decryption algorithm using the encryptionKey
        // Example: decryptedMessage = performDecryption(encryptedMessage, encryptionKey)
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
};

std::string Encryption::privateKey = "YourEncryptionKey";

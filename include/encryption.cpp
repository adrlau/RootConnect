#include <iostream>
#include <string>

class Encryption {
private:
    std::string encryptionKey;

public:
    Encryption(const std::string& key) : encryptionKey(key) {}

    std::string encrypt(const std::string& message) {
        std::string encryptedMessage;
        // Implement encryption algorithm using the encryptionKey
        // Example: encryptedMessage = performEncryption(message, encryptionKey)
        return encryptedMessage;
    }

    std::string decrypt(const std::string& encryptedMessage) {
        std::string decryptedMessage;
        // Implement decryption algorithm using the encryptionKey
        // Example: decryptedMessage = performDecryption(encryptedMessage, encryptionKey)
        return decryptedMessage;
    }

    std::string getEncryptionKey() const {
        // get the encryption key from storage
        return encryptionKey;
    }
};
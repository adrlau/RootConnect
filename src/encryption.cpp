char> encrypted(rsaSize);

    int encryptedLength = RSA_public_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.c_str()),
                                             reinterpret_cast<unsigned char*>(encrypted.data()), rsaKey, RSA_PKCS1_PADDING);
    if (encryptedLength == -1) {
        std::cerr << "Encryption failed." << std::endl;
        return "";
    }

    return std::string(reinterpret_cast<char*>(encrypted.data()), encryptedLength);
}

std::string Encryption::decryptRSA(const std::string& encryptedMessage, RSA* rsaKey) {
    int rsaSize = RSA_size(rsaKey);
    std::vector<unsigned char> decrypted(rsaSize);

    int decryptedLength = RSA_private_decrypt(encryptedMessage.size(),
                                              reinterpret_cast<const unsigned char*>(encryptedMessage.c_str()),
                                              decrypted.data(), rsaKey, RSA_PKCS1_PADDING);
    if (decryptedLength == -1) {
        std::cerr << "Decryption failed." << std::endl;
        return "";
    }

    return std::string(reinterpret_cast<char*>(decrypted.data()), decryptedLength);
}

std::string Encryption::encrypt(const std::string& message, const std::string& publicKey) {
    RSA* rsaKey = createRSAKey(publicKey, true);
    if (rsaKey == nullptr) {
        std::cerr << "Failed to create RSA public key." << std::endl;
        return "";
    }

    std::string encryptedMessage = encryptRSA(message, rsaKey);
    RSA_free(rsaKey);

    return encryptedMessage;
}

std::string Encryption::decrypt(const std::string& encryptedMessage, const std::string& privateKey) {
    RSA* rsaKey = createRSAKey(privateKey, false);
    if (rsaKey == nullptr) {
        std::cerr << "Failed to create RSA private key." << std::endl;
        return "";
    }

    std::string decryptedMessage = decryptRSA(encryptedMessage, rsaKey);
    RSA_free(rsaKey);

    return decryptedMessage;
}

std::string Encryption::decrypt(const std::string& encryptedMessage) {
    return decrypt(encryptedMessage, privateKey);
}

std::string Encryption::getPrivateKey() {
    return privateKey;
}

std::string Encryption::getPublicKey() {
    return publicKey;
}

std::vector<std::string> Encryption::generateKeypair() {
    std::vector<std::string> keyPair(2);
    // const int keyLength = 2048; // Key length in bits
    const int keyLength = 512; // Key length in bits

    // Generate RSA key pair
    RSA* rsaKeyPair = RSA_new();
    BIGNUM* bne = BN_new();
    unsigned long e = RSA_F4;

    if (!BN_set_word(bne, e) || RSA_generate_key_ex(rsaKeyPair, keyLength, bne, nullptr) != 1) {
        std::cerr << "Failed to generate RSA key pair." << std::endl;
        RSA_free(rsaKeyPair);
        return keyPair;
    }

    // Get private key
    BIO* privateKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateKeyBio, rsaKeyPair, nullptr, nullptr, 0, nullptr, nullptr);
    char* privateKeyBuffer;
    long privateKeySize = BIO_get_mem_data(privateKeyBio, &privateKeyBuffer);
    keyPair[0] = std::string(privateKeyBuffer, privateKeySize);
    BIO_free(privateKeyBio);

    // Get public key
    BIO* publicKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSA_PUBKEY(publicKeyBio, rsaKeyPair);
    char* publicKeyBuffer;
    long publicKeySize = BIO_get_mem_data(publicKeyBio, &publicKeyBuffer);
    keyPair[1] = std::string(publicKeyBuffer, publicKeySize);
    BIO_free(publicKeyBio);

    RSA_free(rsaKeyPair);

    privateKey = keyPair[0];
    publicKey = keyPair[1];

    return keyPair;
}

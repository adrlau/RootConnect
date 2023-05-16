#include <string>
#include <vector>
#include "encryption.cpp"
#include "node.cpp"

class Message {
private:
    std::vector<std::Node> path;
    std::string next;
    std::string encryptedContent;

public:
    Message(const std::vector<std::string>& p, const std::string& n, const std::string& c) : path(p), next(n) {
        encryptedContent = Encryption::encrypt(c, "encryptionkey_for_the_node_or_something"); // Encrypt the content using a suitable encryption algorithm
    }

    Message(const std::vector<std::string>& p, const std::string& c) : path(p), next(p.front()) {
        encryptedContent = Encryption::encrypt(c, "encryptionkey_for_the_node_or_something"); // Encrypt the content using a suitable encryption algorithm
    }

    Message(const std::string& c) : encryptedContent(Encryption::encrypt(c)) {
        // In this case, the path and next will not be included in the message
    }

    // Create Message object from a string representation
    Message(const std::string& s) {
        std::string temp = s;
        std::string delimiter = "/";
        size_t pos = 0;
        std::string token;
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            path.push_back(token);
            temp.erase(0, pos + delimiter.length());
        }
        encryptedContent = temp;
    }

    void setPath(const std::vector<std::string>& p) {
        path = p;
    }

    void setNext(const std::string& n) {
        next = n;
    }

    void setContent(const std::string& c) {
        encryptedContent = Encryption::encrypt(c); // Encrypt the content using a suitable encryption algorithm
    }

    std::vector<std::string> getPath() const {
        return path;
    }

    std::string getNext() const {
        return next;
    }

    std::string getDecryptedContent() const {
        return Encryption::decrypt(encryptedContent); // Decrypt the content using the appropriate decryption algorithm
    }

    std::string toString() const {
        std::string result = "";
        for (const std::string& s : path) {
            result += s + "/";
        }
        result += encryptedContent;
        return result;
    }
};

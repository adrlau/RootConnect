#include <string>
#include <vector>
#include "encryption.cpp"
#include "node.cpp"

class Message {
private:
    std::vector<Node> path;
    std::string next;
    std::string encryptedContent;
    std::string padding = ""; //used in a future implementation to reduce the ability to guess the stage in the path based on the length of the encrypted content

public:
    Message(const std::vector<Node>& p, const std::string& n, const std::string& c) : path(p), next(n) {
        encryptedContent = Encryption::encrypt(c, "encryptionkey_for_the_node_or_something"); // Encrypt the content using a suitable encryption algorithm
    }

    Message(const std::vector<Node>& p, const std::string& c) : path(p), next(p.front().getAddress()) {
        encryptedContent = Encryption::encrypt(c, "encryptionkey_for_the_node_or_something"); // Encrypt the content using a suitable encryption algorithm
    }

    Message(const std::string& c) : encryptedContent(Encryption::encrypt(c)) {
        // In this case, the path and next will not be included in the message
    }

    // Create Message object from a string representation
    Message(const std::string& s) {
        //TODO: implement this constructor that decodes the object, The only usecase for this is to decode the message for relay or getting the content. No need to decode the path. 

        //set path to null
        path = std::vector<Node>();

        //get the next node from the Next-Destination:
        next = s.substr(s.find("Next-Destination:") + 17, s.find("Content:") - s.find("Next-Destination:") - 17);

        //get the content from the Content: 
        encryptedContent = s.substr(s.find("Content:") + 8, s.find("Padding:") - s.find("Content:") - 8);
    }

    void setPath(const std::vector<Node>& p) {
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
        std::string base_content = encryptedContent;

        

        //go from last to first in the path
        for (int i = path.size() - 1; i >= 1; i--) {
            Node node = path[i];

            //take the addres the previous node should send the message to

        }

        return result;
    }
};
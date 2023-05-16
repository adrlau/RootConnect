#include <string>
#include <vector>
#include "node.cpp"

class Message {
private:
    std::string nextAddress;
    std::string content;
    std::string padding = ""; // Used in a future implementation to reduce the ability to guess the stage in the path based on the length of the content
public:
    
    Message(const std::string& n, const std::string& c) : nextAddress(n), content(c) {
    }
    
    // Create Message object from a string representation
    Message(const std::string& s) {
        // Get the next node from the Next-Destination:
        nextAddress = s.substr(s.find("Next-Destination: ") + 17, s.find("Content:") - s.find("Next-Destination:") - 17);

        // Get the content from the Content: 
        content = s.substr(s.find("Content:") + 8, s.find("Padding:") - s.find("Content:") - 8);
    }
    

    std::string getContent(){
        return content;
    }

    void setNextAddress(const std::string& n) {
        nextAddress = n;
    }

    void setContent(const std::string& c) {
        content = c;
    }

    std::string getNextAddress() const {
        return nextAddress;
    }

    int getNextPort(const std::string& nextAddress) {
        size_t colonPos = nextAddress.find(':');
        if (colonPos != std::string::npos) {
            std::string portStr = nextAddress.substr(colonPos + 1);
            try {
                int port = std::stoi(portStr);
                return port;
            } catch (const std::exception& e) {
                std::cerr << "Error converting port to integer: " << e.what() << std::endl;
            }
        }
        return -1;  // or any other value indicating failure to parse the port
    }

    std::string getNextAddress(const std::string& nextAddress) {
        size_t colonPos = nextAddress.find(':');
        if (colonPos != std::string::npos) {
            std::string address = nextAddress.substr(0, colonPos);
            return address;
        }
        return "";  // or any other value indicating failure to parse the address
    }

    bool isDestination(){
        if (nextAddress == "NULL"){
            return true;
        }
        return false;
    }

    std::string toString() const {
        std::string result = "";
        result += "\n";
        result += "Next-Destination: " + nextAddress;
        result += "\n";
        result += "Content: " + content;
        result += "\n";
        return result;
    }

    std::string encode(std::vector<Node> path, Message lastMessage) {
        // Base case: If the path is empty, return the last message's content
        if (path.empty()) {
            return lastMessage.getContent();
        }

        // Take the last node in the path
        Node currentNode = path.back();
        path.pop_back();

        // Create a new message with the current node's address as the next destination
        Message encodedMessage(currentNode.getAddress(), "");

        // Set the last message's toString as the content for the current message
        encodedMessage.setContent(lastMessage.toString());

        // Recursively encode the remaining path using the current message
        std::string encodedPath = encode(path, encodedMessage);

        // Append the encoded path to the content of the current message
        encodedMessage.setContent(encodedMessage.getContent() + encodedPath);

        // Return the encoded message as a string
        return encodedMessage.toString();
    }

};

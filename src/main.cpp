#include "mesh.hpp"
#include "message.hpp"
#include "encryption.hpp"
#include "networking.hpp"
#include <iostream>
#include <vector>

int main() {
    //encryption test
    
    // Generate encryption key pair
    std::vector<std::string> keys = Encryption::generateKeypair();

    // Encrypt and decrypt a message
    std::string message = "Hello, world!";
    std::string encryptedMessage = Encryption::encrypt(message, keys[1]);
    std::string decryptedMessage = Encryption::decrypt(encryptedMessage, keys[0]);

    std::cout << "Original Message: " << message << std::endl;
    std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
    std::cout << "Keypair: " << std::endl << keys[0] << ", " << std::endl << keys[1] << std::endl;


    //mesh test
    Mesh mesh1;
    Mesh mesh2;

    
    std::vector<std::string> keys1 = Encryption::generateKeypair();
    Mesh::Node node1 = mesh1.addNode("127.0.0.1:8080", keys1[1]);//all use same public key to test and decrypt with same private key
    std::vector<std::string> keys2 = Encryption::generateKeypair();
    Mesh::Node node2 = mesh1.addNode("127.0.0.1:8080", keys2[1]);
    std::vector<std::string> keys3 = Encryption::generateKeypair();
    Mesh::Node node3 = mesh2.addNode("127.0.0.1:8080", keys3[1]);
    std::vector<std::string> keys4 = Encryption::generateKeypair();
    Mesh::Node node4 = mesh2.addNode("127.0.0.1:8080", keys4[1]);

    mesh1.addEdge(node1, node2);
    mesh2.addEdge(node3, node4);

    std::cout << "Mesh 1: " << std::endl;
    mesh1.printMesh();
    std::cout << "Mesh 2: " << std::endl;
    mesh2.printMesh();

    // Merge the two meshes
    mesh1.mergeMesh(mesh2);

    //add a edge between node2 and node3
    mesh1.addEdge(node1, node4);
    mesh1.addEdge(node2, node4);

    std::cout << "Merged Mesh: " << std::endl;
    mesh1.printMesh();


    std::vector<Mesh::Node> path = mesh1.findPath(node1, node4);

    std::cout << "Path: ";
    for (const auto& node : path) {
        std::cout << node.publicKey << " -> ";
    }
    std::cout << std::endl;


    //message test
    //just create a simple message without having a send to address and print it out
    Message message1("NULL", "Hello, world!");
    std::cout << "Message: "<< std::endl << message1.toString() << std::endl;

    std::cout << "Testing message encoding and decoding " << std::endl;

    //generate a manual simulated 2 node path and encode the message for a custom path
    std::vector<Mesh::Node> path2 = { node1, node2, node3};

    std::cout << "Path2: ";
    for (const auto& node : path2) {
        std::cout << node.publicKey << " -> ";
    }
    std::cout << std::endl;

    Message message2 = message1.encode(path2);
    std::cout << "Encoded Message: " << std::endl << message2.toString() << std::endl;
    //decode the message
    std::cout << "Decoded Message1: " << std::endl << message2.decode(keys2[0]) << std::endl;

    std::cout << "Decoded Message2: " << std::endl << message2.decode(keys3[0]) << std::endl;

    
    std::cout << "Testing path encoded message encoding and decoding " << std::endl;
    std::cout << "Path: ";
    for (const auto& node : path) {
        std::cout << node.publicKey << " -> ";
    }
    std::cout << std::endl;

    //now with the path generated from the mesh
    Message message4("NULL", "Hello, world!");
    message4 = message4.encode(path);

    std::cout << "Encoded Message: " << std::endl << message4.toString() << std::endl;
    //decode the message
    std::vector<std::string> keysc = {};
    //fill keysc with the private keys of the nodes in the path
    for (const auto& node : path) {
        std::string pub = node.publicKey; //works because the public key is the same as the private key in this implementation of the encryption class
        if (keys1[1] == pub)
        {
            keysc.push_back(keys1[0]);
        }
        else if (keys2[1] == pub)
        {
            keysc.push_back(keys2[0]);
        }
        else if (keys3[1] == pub)
        {
            keysc.push_back(keys3[0]);
        }
        else if (keys4[1] == pub)
        {
            keysc.push_back(keys4[0]);
        }
        else
        {
            std::cout << "Error: public key not found" << std::endl;
        }
    }

    for (size_t i = 0; i < path.size()-1; i++) {
        std::cout << "Decoded Message: " << " node " << path[i].publicKey << " -> " << std::endl << message4.decode(keysc[i+1]) << std::endl;
    }

    //network test
    std::cout << std::endl << std::endl << "Testing networking " << std::endl;

    std::vector<std::string> keys5 = Encryption::generateKeypair();
    Mesh mesh3;
    Mesh::Node node5 = mesh3.addNode("127.0.0.1:8080", keys5[1]);
    //path
    std::vector<Mesh::Node> path3 = { node5, node5};
    //message
    Message message5("NULL", "Hello, world!");
    message5 = message5.encode(path3);

    //send a message from node1 to node1 using the networking class
    Networking networking(node1.bindAddress(), node1.bindPort());
    networking.startListeningThread();
    std::cout << "Started Listening for messages..." << std::endl;

    //send the message
    std::cout << "sending message..." << std::endl;
    networking.sendMessage(node1.bindAddress(), node1.bindPort(), message5.toString());


    return 0;
}

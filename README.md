# RootConnect

A simple baselayer for a chat messaging application/protocol written in C++ for a semester assignment in the course IDATT2004 Network Programming at NTNU (Norwegian University for Science and Technology).
Description

In this project, I, Adrian Gunnar Lauterer, have created the foundation of a simple chat messaging application using onion technology written in C++.
Motivations

## Motivation and Problem Statement
    

    
    In relation to mobile wireless mesh networks i wanted to create a way to securely and privately communicate with others in the network without revealing what you are communicating and with whom. I wanted to use the idea of onion technology to encrypt the messages and route them through the network so that the current only knows where it came from and should go to next, not neccecarily the source and the destination with asymetric encryption to keep the content private.
    Because i wanted to explore the problems with securoty and protection against triangulation choose this problem statement as my project.

    "Create a secure messaging application using onion technology that enables users to send encrypted messages through a network of interconnected nodes."

## Implementation

The RootConnect application is a chat messaging application/protocol implemented in C++. It aims to provide secure and anonymous communication through a network of interconnected nodes. The application is designed to run on Unix systems and is written in a modular manner, allowing for easy replacement of modules.
Encryption and Security

The application uses OpenSSL for encryption, but it currently has an issue where private and public keys are the same. This issue needs to be addressed to ensure proper encryption and security. Future improvements should focus on enhancing the encryption process and fixing the key generation.
Networking

The networking implementation of the RootConnect application needs improvement. Currently, it does not forward and decrypt messages properly. This issue must be resolved to ensure messages are correctly routed and decrypted at the intended destination.
Future Work

There are several areas for future work and improvement in the RootConnect application:

-   Implement an independent wireless mesh network to enable the secure communication protocol to work on top of it. This would involve multiple layers of implementation in the networking stack.
-   Improve encryption by fixing the issue of using the same private and public keys. This is essential for ensuring secure communication between nodes.
-   Develop a mechanism for key and address distribution in the wireless mesh network. This mechanism would be crucial for adding new nodes to the network and ensuring secure communication.
-   Enhance the networking implementation to ensure proper forwarding and decryption of messages. This is vital for the effective functioning of the application.
-   Implement a mechanism for adding new wireless connections to nodes. This would enable expanding the network and increasing connectivity.
-   Develop a way to distribute keys and explore the mesh automatically. One possible approach is to have multiple known nodes in the network that people can connect to in order to obtain information and connect with others.


### Message Format

The message format used in RootConnect is a plain string with line shift separation. The header, which continues until the first double empty line shift, contains information about the message and the path it should take.

#### Example:

```
Next-Destination: [Next Destination]
Content: [Encrypted Content]
```

The encrypted content contains the next destination, and subsequent encrypted content contains the next destination until the last destination is reached, where the encrypted content contains the message.

If the content decrypts to a message that does not contain the Next-Destination header, it indicates the final message and should be displayed to the user.

If the message is not encrypted, it will be sent as plain text, and the Next-Destination header will specify the next destination.

#### Example:
```
    Next-Destination: [Next Destination]
    Content: "Next-Destination: [Next Destination] \n Content: [Plain Text Content]"
```
a problem with this is parsing the message if the fontent or the next destination contains a line shift. This can be solved by using a different format for the message, for example JSON, but this would require a parser for the message format and would make the message format more complex.

### Encryption

RootConnect employs OpenSSL library for encryption and ensures network communication security. The current use of the same private-public keys is insecure, requiring future improvements.

To increase security, RootConnect needs stronger algorithms and personalized key pairs per node. Appropriate measures must be established to share public keys among nodes securely.

Asymmetrical encryption enables encrypting messages by the recipient's public key, ensuring only they can read it. Encrypting the message in multiple layers provides information about the next hop route.

Future updates should offer proper decryption and forwarding of messages, protecting integrity and confidentiality.

Improving encryption algorithms, addressing networking issues, and optimizing key distribution are crucial steps towards a more secure and reliable RootConnect application.


## Related Works and Projects

RootConnect is an independent project developed as part of the assignment for the course IDATT2004 - Network Programming at NTNU. However, there are other projects and technologies related to secure messaging and chat applications.

One notable project is Matrix, an open standard and decentralized communication protocol. Matrix provides end-to-end encryption for secure messaging and supports chat applications with features like group chat, file sharing, and more. The Matrix protocol allows for interoperability between different chat applications, enabling users to communicate securely across different platforms.

Another related project is Signal, a popular messaging application known for its strong encryption and privacy features. Signal uses the Signal Protocol to provide end-to-end encryption, ensuring that only the intended recipients can read the messages.
Contribution

This project was developed solely by Adrian Gunnar Lauterer as part of the assignment for the course IDATT2004 - Network Programming at NTNU.
Video Presentation

Please find the video presentation included in the submitted compressed file. The presentation provides an overview of the chosen problem statement, implemented functionality, programming languages used, and a demonstration of the solution.
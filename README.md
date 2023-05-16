# RootConnect
A simple chatt messaging application written in cpp for a semester assigment in the course IDATT2004 neverksprogrammering at NTNU (Norwegian University for science and technology)


A simple chat messaging application using onion technology and the ip networking protocoll written in C++ 


## ideas

- name rootconnect
-   create a server that can communicate to multiple servers
    -   For the moment store the entire reachable mesh and the structure of the possible paths.
        -   get multiple random possible routes from a to b
            -   from now onwards the message goes from a to 1 to 2 , 3 , 4 and then b
            -   a sends a message to 1 with the information of sending it to 2
            -   2 sends to 3 and so on until the message reaches b.


    Protocol Name: OnionMeshChatProtocol

    Protocol Overview:
        The protocol facilitates the transmission of messages through a specific part of the onion mesh chat network.
        It ensures that the message is securely routed through intermediate nodes before reaching the intended destination.
        Each intermediate node peels off a layer of encryption, revealing the next hop until the message reaches its destination.

    Protocol Steps:
    a. Message Creation and Encryption:
        The sender encrypts the message using multiple layers of encryption, corresponding to the number of hops it will traverse.
        Each encryption layer includes information about the next hop in the route.

    b. Route Determination:
        The sender's client or server (e.g., rootconnect) determines the route for the message based on the stored reachable mesh and path structures.
        It randomly selects multiple possible routes from the sender to the destination.

    c. Onion Encapsulation and Routing:
        The sender's client/server encapsulates the encrypted message in an onion-like structure, with multiple layers of encryption.
        Each layer contains the encrypted message and the information about the next hop in the route.

    d. Onion Routing:
        The sender's client/server sends the onion-encapsulated message to the first node in the selected route.
        Each intermediate node in the route peels off one layer of encryption, revealing the information about the next hop.
        The node then forwards the partially decrypted message to the next node in the route.

    e. Final Destination:
        The last node in the route receives the fully decrypted message and delivers it to the intended recipient.

    Security Considerations:
        The protocol ensures the privacy and confidentiality of messages by encrypting them with multiple layers.
        Each node in the route only has access to the information about the next hop, maintaining the anonymity of the sender and receiver.
        Additional security measures, such as authentication and integrity checks, can be incorporated to enhance the protocol's security.


## message format

plain string with lineshift seperation.
first header that continues until the first dubble empty lineshift is the header.
the header contains the information about the message and the path it should take.

example:
```
Next-Destination: [Next Destination]
Content: [Encrypted Content]
```
with the encrypted content containing the next destination, and a further encrypted content containing the next destination and so on until the last destination is reached where the encrypted content contains the message.

If the Content decrypts to a message that does not contain the Next-Destination header, the message is the final message and should be displayed to the user.

If the message is not encrypted the message will be sent as plain text, and the Next-Destination header will be the next destination.

example:
```
Next-Destination: [Next Destination]
Content: "Next-Destination: [Next Destination] \n Content: Hello World"
```
Encryption should be done with asymetric encryption, and the public key of the next destination should be used to encrypt the message. The message should be encrypted with the public key of the next destination, and the next destination should be encrypted with the public key of the next destination after that and so on until the last destination is reached. The last destination should be encrypted with the public key of the destination.

Maybe for future implementation:
Public keys should be distributed through the network, and the public key of the destination should be known by the sender, this might be out of scope for this project, but it is a good idea to think about it. Should be able to send the public key unencrypted back if one recives a certain message from a node. This could be a message with a specific header, and could in theory still have been sent through the network.


## implementation

this is a simple chat messaging application using onion technology and the ip networking protocoll written in C++.
The application is written in C++ and should work with C++ 17 or 23. It uses the standard library for the most part, but it remains untested on non linux platforms (development and testing on Arch linux 6.3.1-arch1-1 #1 SMP PREEMPT_DYNAMIC Mon, 01 May 2023 17:42:39 +0000 x86_64 GNU/Linux). The application is written in a modular way, where the different parts of the application are separated into different files. 

### dependencies

- iostream
- string
- thread
- cstring
- sys/socket.h
- arpa/inet.h  unix library for internet operations 
- unistd.h

### Implementation details

as specific unix systems are used this is primarily written for unix systems. The application is written in a modular way so that if any part needs to be changed you can easily swap out and replace modules to reimplement this sample application.

I choose to implement this using the default networking stack and not truly create my own networking protocoll. This is because i wanted to be able to utilize ip as a layer to implement this on top of. The applicationshould be portable enough if one wants to implement it on a truly standalone peer to peer beacon to beacon level network, but this is out of scope of this implementation. My primary goal was to be able to send messages from one node to another through a network of nodes, with multiple jumps to protect the identity of the sender and receiver. This will be a sor tof mesh network even if the nodes are fully connected to each other through the world wide web, as the nodes will still create their mesh and find a path for the packages. 

### how to run
    1. clone the repository
    2. run the makefile in the root directory with the command "make" in the terminal
    3. run the application with the command "make run" in the terminal
    4. follow the instructions in the terminal







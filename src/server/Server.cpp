#include "Server.h"

#include <iostream>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

using namespace std;

Server::Server() : executor(dataStore)
{
}

bool Server::start()
{
    // Step 1: Create Socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        cerr << "Failed to create socket." << endl;
        return false;
    }

    cout << "Socket created successfully." << endl;

    // Step 2: Configure Server Address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;          // IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    serverAddress.sin_port = htons(6379);        // Redis default port

    // Step 3: Bind Socket to IP and Port
    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) < 0)
    {
        cerr << "Bind failed." << endl;
        close(serverSocket);
        return false;
    }

    cout << "Bind successful." << endl;

    // Step 4: Start Listening
    if (listen(serverSocket, 5) < 0)
    {
        cerr << "Listen failed." << endl;
        close(serverSocket);
        return false;
    }

    cout << "Server listening on port 6379..." << endl;

    // Keep the server running for now
    while (true)
    {
        cout << "\nWaiting for a client..." << endl;

        sockaddr_in clientAddress{};
        socklen_t clientLength = sizeof(clientAddress);

        int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength);

        if (clientSocket < 0)
        {
            cerr << "Accept failed." << endl;
            continue;
        }

        cout << "Client connected!" << endl;

    while (true)
    {
        char buffer[1024] = {0};

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer),
            0);

        if (bytesReceived <= 0)
        {
            cout << "Client disconnected." << endl;
            break;
        }

        string command(buffer);
        
        if (command == "EXIT\n" || command == "EXIT\r\n" || command == "EXIT" || command == "exit\n" || command == "exit\r\n" || command == "exit")
        {
            string response = "Goodbye!\n";

            send(clientSocket,
                response.c_str(),
                response.length(),
                0);

            break;
        }

        vector<string> tokens = parser.parse(command);

        string response = executor.execute(tokens);

        response += "\n";

        send(clientSocket,
            response.c_str(),
            response.length(),
            0);
    }

    close(clientSocket);
        }

    close(serverSocket);

    return true;


}
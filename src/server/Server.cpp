// #include "Server.h"

// #include <iostream>
// #include <cstring>

// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <vector>

// using namespace std;

// Server::Server() : executor(dataStore)
// {
// }

// bool Server::start()
// {
//     // Step 1: Create Socket
//     serverSocket = socket(AF_INET, SOCK_STREAM, 0);

//     if (serverSocket == -1)
//     {
//         cerr << "Failed to create socket." << endl;
//         return false;
//     }

//     int opt = 1;

//     setsockopt(serverSocket,
//             SOL_SOCKET,
//             SO_REUSEADDR,
//             &opt,
//             sizeof(opt));

//     cout << "Socket created successfully." << endl;

//     // Step 2: Configure Server Address
//     sockaddr_in serverAddress{};

//     serverAddress.sin_family = AF_INET;          // IPv4
//     serverAddress.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
//     serverAddress.sin_port = htons(6379);        // Redis default port

//     // Step 3: Bind Socket to IP and Port
//     if (bind(serverSocket,
//              reinterpret_cast<sockaddr*>(&serverAddress),
//              sizeof(serverAddress)) < 0)
//     {
//         cerr << "Bind failed." << endl;
//         close(serverSocket);
//         return false;
//     }

//     cout << "Bind successful." << endl;

//     // Step 4: Start Listening
//     if (listen(serverSocket, 5) < 0)
//     {
//         cerr << "Listen failed." << endl;
//         close(serverSocket);
//         return false;
//     }

//     cout << "Server listening on port 6379..." << endl;

//     // Keep the server running for now
//     while (true)
//     {
//         cout << "\nWaiting for a client..." << endl;

//         sockaddr_in clientAddress{};
//         socklen_t clientLength = sizeof(clientAddress);

//         int clientSocket = accept(
//             serverSocket,
//             reinterpret_cast<sockaddr*>(&clientAddress),
//             &clientLength);

//         if (clientSocket < 0)
//         {
//             cerr << "Accept failed." << endl;
//             continue;
//         }

//         cout << "Client connected!" << endl;


//         char temp[1024];
//         string receiveBuffer;

//         while (true)
//         {
//             int bytesReceived = recv(clientSocket,
//                                     temp,
//                                     sizeof(temp),
//                                     0);

//             if (bytesReceived <= 0)
//             {
//                 cout << "Client disconnected." << endl;
//                 break;
//             }

//             receiveBuffer.append(temp, bytesReceived);

//             while (true)
//             {
//                 string command;

//                 // -----------------------
//                 // Plain text command
//                 // -----------------------
//                 if (!receiveBuffer.empty() && receiveBuffer[0] != '*')
//                 {
//                     size_t pos = receiveBuffer.find('\n');

//                     if (pos == string::npos)
//                         break;

//                     command = receiveBuffer.substr(0, pos);

//                     receiveBuffer.erase(0, pos + 1);
//                 }

//                 // -----------------------
//                 // RESP command
//                 // -----------------------
//                 else
//                 {
//                     size_t last = receiveBuffer.rfind("\r\n");

//                     if (last == string::npos)
//                         break;

//                     command = receiveBuffer.substr(0, last);

//                     receiveBuffer.erase(0, last + 2);
//                 }

//                 if (!command.empty() && command.back() == '\r')
//                     command.pop_back();

//                 if (command.empty())
//                     continue;

//                 if (command == "EXIT" || command == "exit")
//                 {
//                     string response = "Goodbye!\n";

//                     send(clientSocket,
//                         response.c_str(),
//                         response.length(),
//                         0);

//                     break;
//                 }

//                 cout << "\n======================" << endl;
//                 cout << "Raw Command:\n";
//                 cout << command << endl;

//                 vector<string> tokens = parser.parse(command);

//                 cout << "Tokens: ";
//                 for (const auto &t : tokens)
//                 {
//                     cout << "[" << t << "] ";
//                 }
//                 cout << endl;


//                 string response = executor.execute(tokens);

//                 // Was this a RESP request?
//                 bool isRESP = !command.empty() && command[0] == '*';

//                 if(isRESP)
//                 {
//                     string resp;

//                     if(response == "OK")
//                     {
//                         resp = "+OK\r\n";
//                     }
//                     else if(response == "(nil)")
//                     {
//                         resp = "$-1\r\n";
//                     }
//                     else
//                     {
//                         resp = "$" + to_string(response.length()) + "\r\n";
//                         resp += response + "\r\n";
//                     }

//                     send(clientSocket,
//                         resp.c_str(),
//                         resp.length(),
//                         0);
//                 }

//                 else
//                 {
//                     response += "\n";

//                     send(clientSocket,
//                         response.c_str(),
//                         response.length(),
//                         0);
//                 }
//             }
//         }

//         close(clientSocket);
//     }

//     close(serverSocket);

//     return true;


// }


#include "Server.h"

#include <iostream>
#include <thread>
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

    int opt = 1;

    setsockopt(serverSocket,
               SOL_SOCKET,
               SO_REUSEADDR,
               &opt,
               sizeof(opt));

    cout << "Socket created successfully." << endl;

    // Step 2: Configure Server Address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(6379);

    // Step 3: Bind Socket
    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) < 0)
    {
        cerr << "Bind failed." << endl;
        close(serverSocket);
        return false;
    }

    cout << "Bind successful." << endl;

    // Step 4: Listen
    if (listen(serverSocket, 5) < 0)
    {
        cerr << "Listen failed." << endl;
        close(serverSocket);
        return false;
    }

    cout << "Server listening on port 6379..." << endl;

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

        thread clientThread(&Server::handleClient,
                            this,
                            clientSocket);

        clientThread.detach();
    }

    close(serverSocket);

    return true;
}

void Server::handleClient(int clientSocket)
{
    char temp[1024];
    string receiveBuffer;

    while (true)
    {
        int bytesReceived = recv(clientSocket,
                                 temp,
                                 sizeof(temp),
                                 0);

        if (bytesReceived <= 0)
        {
            cout << "Client disconnected." << endl;
            break;
        }

        receiveBuffer.append(temp, bytesReceived);

        while (true)
        {
            string command;

            // -----------------------
            // Plain Text Command
            // -----------------------
            if (!receiveBuffer.empty() && receiveBuffer[0] != '*')
            {
                size_t pos = receiveBuffer.find('\n');

                if (pos == string::npos)
                    break;

                command = receiveBuffer.substr(0, pos);
                receiveBuffer.erase(0, pos + 1);
            }

            // -----------------------
            // RESP Command
            // -----------------------
            else
            {
                size_t last = receiveBuffer.rfind("\r\n");

                if (last == string::npos)
                    break;

                command = receiveBuffer.substr(0, last);
                receiveBuffer.erase(0, last + 2);
            }

            if (!command.empty() && command.back() == '\r')
                command.pop_back();

            if (command.empty())
                continue;

            if (command == "EXIT" || command == "exit")
            {
                string response = "Goodbye!\n";

                send(clientSocket,
                     response.c_str(),
                     response.length(),
                     0);

                break;
            }

            cout << "\n======================" << endl;
            cout << "Raw Command:" << endl;
            cout << command << endl;

            vector<string> tokens = parser.parse(command);

            cout << "Tokens: ";
            for (const auto &t : tokens)
            {
                cout << "[" << t << "] ";
            }
            cout << endl;

            string response = executor.execute(tokens);

            bool isRESP = !command.empty() && command[0] == '*';

            if (isRESP)
            {
                string resp;

                if (response == "OK")
                {
                    resp = "+OK\r\n";
                }
                else if (response == "(nil)")
                {
                    resp = "$-1\r\n";
                }
                else
                {
                    resp = "$" + to_string(response.length()) + "\r\n";
                    resp += response + "\r\n";
                }

                send(clientSocket,
                     resp.c_str(),
                     resp.length(),
                     0);
            }
            else
            {
                response += "\n";

                send(clientSocket,
                     response.c_str(),
                     response.length(),
                     0);
            }
        }
    }

    close(clientSocket);
}
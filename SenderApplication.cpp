#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

//The Server File

//Replace the ip address with your server IP address
//Port can be whatever you choose, usually one above 1024 to
//prevent choosing a port already in use



int main() {
    unsigned short port = 55555;
    //127.0.0.1 for Loopback
    std::string IPaddr = 0.0.0.0";
    WSADATA wsaData, *dataref;
    int wsaerr;
    WORD wVerReq = MAKEWORD(2,2);
    wsaerr = WSAStartup(wVerReq, dataref);
    if(wsaerr == 0){
        //Successful WSA startup
        std::cout << "WSA/DLL Successfully initialized" << "\n";
        SOCKET serverSocket = INVALID_SOCKET;
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(serverSocket != INVALID_SOCKET){
            //Cannot use returns 0 since it returns a SOCKET WSAAPI type
            std::cout << "Socket successfully initialized" << "\n";
            sockaddr_in service;
            service.sin_family = AF_INET;

            service.sin_addr.s_addr = INADDR_ANY;
            PVOID refAddr = &service.sin_addr.s_addr;
            inet_pton(AF_INET, IPaddr.c_str(), refAddr);
            service.sin_port = htons(port);
            if(bind(serverSocket, (SOCKADDR*)& service, sizeof(service)) != SOCKET_ERROR){
                std::cout << "Successful Binded Socket" << "\n";
                if(listen(serverSocket, 1) != SOCKET_ERROR){
                    std::cout << "Successfully Started Listening" << "\n";
                    SOCKET clientSocket;
                    clientSocket = accept(serverSocket, NULL, NULL);
                    if(clientSocket != INVALID_SOCKET){
                        sockaddr_in client;
                        int size = sizeof(client);
                        std::cout << "Connected with Client" << "\n";
                        std::string ServerMessage;
                        char buffer[500];
                        char recieved[500];
                        int index = 0;
                        do{
                            if(index % 2 == 0){
                                std::cin.getline(buffer, 500);
                                //Even Turns
                                if(send(clientSocket, buffer, sizeof(buffer), 0) == sizeof(buffer)){
                                    std::cout << "Server said: " << buffer << "\n";
                                    index++;
                                }
                                
                            } else{
                                if(recv(clientSocket, recieved, sizeof(recieved), 0) != SOCKET_ERROR){
                                    std::cout << "Client said: " << recieved << "\n";
                                    index++;
                                }   
                            }
                            if(WSAGetLastError() == 10054){
                                std::cout << "Client ended the chat." << "\n";
                                break;
                            }                         
                        } while (buffer != "exit");
                    } else{
                        std::cout << "Failed to Connect with Client" << "\n";
                        std::cout << "Error: " << WSAGetLastError();
                    }
                } else {
                    std::cout << "Failed to Listen" << "\n";
                    std::cout << "Error: " << WSAGetLastError() << "\n";
                    closesocket(serverSocket);
                }
                WSACleanup();
            } else{
                std::cout << "Failed to bind" << "\n";
                std::cout << "Error: " << WSAGetLastError() << "\n";
                closesocket(serverSocket);
                WSACleanup();
            }
        } else{
            //On Failed socket initializing
            std::cout << "Socket failed initializing" << "\n";
            std::cout << "Error: " << WSAGetLastError() << "\n";
            WSACleanup();
        }
    } else{
        //On Failed WSA/DLL Startup
        std::cout << "Error occurred in WSA Startup";
        WSACleanup();
    }
    
    return 1;
}

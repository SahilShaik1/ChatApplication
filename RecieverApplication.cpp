#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>



//Use following command to operate
//cd "c:\Users\sahil\Documents\C++\C++\NetworkProgramming\" ; if ($?) { g++ ServerSocketApplication.cpp -o ServerSocketApplication -lws2_32 } ; if ($?) { .\ServerSocketApplication }


//The Client Application
//change port and ip to your needs.





int main() {
    WSADATA wsaData, *dataref;
    int wsaerr;
    WORD wVerReq = MAKEWORD(2,2);
    wsaerr = WSAStartup(wVerReq, dataref);
    std::string serverIP = "0.0.0.0";

    if(wsaerr == 0){
        //Successful Startup
        std::cout << "WSA Clientside Started" << "\n";
        SOCKET ServerSocket = INVALID_SOCKET;
        ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(ServerSocket != INVALID_SOCKET){
            std::cout << "Clientside socket initialized" << "\n";
            sockaddr_in clientService;
            clientService.sin_family = AF_INET;
            const unsigned short port = 55555;
            PVOID cRefAddr = &clientService.sin_addr.s_addr;
            inet_pton(AF_INET, serverIP.c_str(), cRefAddr);
            clientService.sin_port = htons(port);
            if(connect(ServerSocket, (SOCKADDR*)&clientService, sizeof(clientService)) != SOCKET_ERROR){
                std::cout << "Successfully Connected with Server" << "\n";
                char msgRec[500];
                char msgSend[500];
                char fileStr[500];
                int index = 0;
                do{ 
                    if(index % 2 == 0){
                        //Even Turns
                        if(recv(ServerSocket, msgRec, sizeof(msgRec), 0) != SOCKET_ERROR){
                            if(msgRec[0] == '/' && msgRec[1] == '0'){
                                std::cout << "Server is about to send a file" << "\n";
                                std::string name = "";
                                while(msgRec[0] != '<'){
                                    recv(ServerSocket, msgRec, sizeof(msgRec), 0);
                                    if(msgRec[0] != '<'){
                                        name += msgRec;
                                    } else {
                                        break;
                                    }
                                }
                                std::ofstream fileRecieved(name);
                                recv(ServerSocket, msgRec, sizeof(msgRec), 0);
                                fileRecieved << msgRec;
                                while(msgRec[0] != '|'){
                                    recv(ServerSocket, msgRec, sizeof(msgRec), 0);
                                    if(msgRec[0] == '|'){
                                        break;
                                    }
                                    if(msgRec[0] == '['){
                                        fileRecieved << "\n";
                                    } else{
                                        fileRecieved << msgRec;
                                    }
                                }
                                fileRecieved.close();
                            }
                            else{
                                std::cout << "Server said: " << msgRec << "\n";
                                index++;
                            }
                        }
                    } else{
                        //Odd Turns
                        std::cin.getline(msgSend, 500);
                        if(send(ServerSocket, msgSend, sizeof(msgSend), 0) == sizeof(msgSend)){
                            std::cout << "Client said: " << msgSend << "\n";
                            index++;
                        }
                    }
                    if(WSAGetLastError() == 10054){
                        std::cout << "The Chat has been closed." << "\n";
                        break;
                    }
                } while (true);
            } else {
                std::cout << "Failed to Connect with Server" << "\n";
                std::cout << "Error: " << WSAGetLastError() << "\n";
            }        
        }
    }
    return 0;
}

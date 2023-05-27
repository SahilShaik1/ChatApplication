#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>


//Client application
//Change serverIP to the ip of the server you want to connect to
int main() {
    WSADATA wsaData, *dataref;
    int wsaerr;
    WORD wVerReq = MAKEWORD(2,2);
    wsaerr = WSAStartup(wVerReq, dataref);
    std::string serverIP = "0.0.0.0";

    if(wsaerr == 0){
        //Successful Startup
        std::cout << "WSA Clientside Started" << "\n";
        SOCKET reciever = INVALID_SOCKET;
        reciever = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(reciever != INVALID_SOCKET){
            std::cout << "Clientside socket initialized" << "\n";
            sockaddr_in clientService;
            clientService.sin_family = AF_INET;
            const unsigned short port = 55555;
            PVOID cRefAddr = &clientService.sin_addr.s_addr;
            inet_pton(AF_INET, serverIP.c_str(), cRefAddr);
            clientService.sin_port = htons(port);
            /*
            if(bind(reciever, (SOCKADDR*)&clientService, sizeof(clientService)) != SOCKET_ERROR){
                std::cout << "Successfully Binded" << "\n";
            } else {
                std::cout << "Failed to bind" << "\n";
                std::cout << "Error: " << WSAGetLastError() << "\n";
            }
            */
            if(connect(reciever, (SOCKADDR*)&clientService, sizeof(clientService)) != SOCKET_ERROR){
                std::cout << "Successfully Connected with Server" << "\n";
                char msgRec[500];
                char msgSend[500];
                std::cout << "Message: " << msgRec;
                do{
                    if(WSAGetLastError() == 10054){
                        std::cout << "The Chat has been closed." << "\n";
                        break;
                    }
                    if (recv(reciever, msgRec, sizeof(msgRec), 0) != SOCKET_ERROR){
                        std::cout << "Successfully recieved message" << "\n";
                        std::cout << "Message: " << "\n";
                        std::cout << msgRec << "\n";
                    }

                } while (true);
            } else {
                std::cout << "Failed to Connect with Server" << "\n";
                std::cout << "Error: " << WSAGetLastError() << "\n";
            }        
        }
    }
    do
    {
        std::cout << "Type enter to exit";
    } while (std::cin.get() != '\n');
    return 0;
}

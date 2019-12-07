// include the need libraries and header files 
#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

// Error return output
#define Error -1;

// main program
int main ()
{
// Create a socket
int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
if (listening_socket < 0)
{
    std::cerr << "Please connect a socket!" << std::endl;
    return Error
}
// The socket will be binded to an IP/Port
sockaddr_in new_socket_address;
new_socket_address.sin_family = AF_INET;
// convert port to machine correct byte (either little endian or big endian)
new_socket_address.sin_port = htons(50000);
// convert an ip address string to a number using this function
inet_pton(AF_INET, "0.0.0.0", &new_socket_address.sin_addr);

if (bind(listening_socket, (sockaddr*)&new_socket_address, sizeof(new_socket_address)) < 0)
{
    std::cerr << "sorry it can't bind to the IP/port" << std::endl;
    return Error
}
// Check the socket for listening
if (listen(listening_socket, SOMAXCONN)  < 0)
{
    std::cerr << "Failed to listen to that port!" << std::endl;
    return Error
}
// Accept calls
sockaddr_in new_client;
socklen_t new_clientSize = sizeof(new_client);
char new_host[NI_MAXHOST];
char new_service[NI_MAXSERV];

// accept connections 
int clientSocket = accept(listening_socket, (sockaddr*)&new_client, &new_clientSize);
if (clientSocket < 0)
{
    std::cerr << "There was a problem reaching client" << std::endl;
    return Error
}

// Close the selected listening Port
close(listening_socket);
// cleaning the data
memset(new_host, 0,  NI_MAXHOST);
memset(new_service, 0, NI_MAXSERV);
int server_name = getnameinfo((sockaddr*)&new_client, sizeof(new_client), new_host, NI_MAXHOST, new_service, NI_MAXSERV, 0);

if (server_name)
{
    std::cout << "This" << new_host << " is connected to " << new_service << std::endl;
}
else
{
    inet_ntop(AF_INET, &new_client.sin_addr, new_host, NI_MAXHOST);
    std::cout << "This client " << new_host << " is connected to " << ntohs(new_client.sin_port) << std::endl;
}

// show message
char buffer[4096];
while (true)
{
    memset(buffer, 0, 4096);

    int received_bytes = recv(clientSocket, buffer, 4096, 0);
    if (received_bytes < 0)
    {
        std::cerr << "There is a problem while connecting" << std::endl;
        return Error
        break;
    }
    if (received_bytes == 0)
    {
        std::cout << "Hello, there. The client has disconnected" << std::endl;
        break;
    }

    std::cout << "The client has received: " << std::string(buffer, 0, received_bytes) << std::endl;
    int return_message = send(clientSocket, buffer, received_bytes+1, 0);
   // std::cout <<"You had send: " << "*** " << return_message << " ***" << std::endl;
}

// Close socket
close(clientSocket);
    return 0;
}
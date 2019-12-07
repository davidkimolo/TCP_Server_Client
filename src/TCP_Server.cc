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
new_socket_address.sin_port = htons(52000);
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

// Close the selected listening Port
// Close socket

    return 0;
}
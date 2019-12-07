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
if (listening_socket == -1)
{
    std::cerr << "Please connect a socket!" << std::endl;
    return Error
}
// The socket will be binded to an IP/Port
// Select the socket for listening
// Accept calls
// Close the selected listening Port
// Close socket

    return 0;
}
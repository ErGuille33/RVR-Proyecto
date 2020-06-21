#include <string.h>

#include "Serializable.h"
#include "Socket.h"

Socket::Socket(const char * address, const char * port):sd(-1)
{
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(address, port, &hints, &res);
    
    if(rc!= 0)
    {
        std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;
    }

    sa =  *res->ai_addr;
    sa_len = sizeof(struct sockaddr);

    sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);


    freeaddrinfo(res);
}

int Socket::recv(Serializable &obj, Socket * &sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sock->sd, (void*)buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);
    if ( bytes <= 0 )
    {
        return -1;
    }
    obj.from_bin(buffer);
    return 0;
}

int Socket::send(Serializable& obj, const Socket& sock)
{
    int aux;

    obj.to_bin();
    
    char *charData = obj.data();

    aux = sendto(sock.sd, charData, obj.size(), 0, &sock.sa, sock.sa_len);

    std::cout << aux << " Mensaje enviado" << std::endl;
    return aux;
}

bool operator== (const Socket &s1, const Socket &s2)
{
    sockaddr_in* sock1 = (struct sockaddr_in *)&s1.sa;
    sockaddr_in* sock2 = (struct sockaddr_in *)&s2.sa;


    return (sock1->sin_family == sock2->sin_family && sock1->sin_addr.s_addr == sock2->sin_addr.s_addr
    && sock1->sin_port == sock2->sin_port);
};

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};


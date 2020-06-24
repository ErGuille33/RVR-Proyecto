#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <iostream>
#include <stdexcept>
//#include "Chat.h"

#include <ostream>

class Socket;
class Serializable;
class PlayerInfo;

bool operator== (const Socket &s1, const Socket &s2);

std::ostream& operator<<(std::ostream& os, const Socket& dt);

class Socket
{
public:
    
    static const int32_t MAX_MESSAGE_SIZE = 14;

    Socket(const char * address, const char * port);

    Socket(struct sockaddr * _sa, socklen_t _sa_len):sd(-1), sa(*_sa),
        sa_len(_sa_len){};

    virtual ~Socket(){};

    int recv(Serializable &obj, Socket * &sock);
    int recvInit(Serializable &obj, Socket * &sock);

    int recv(Serializable &obj)
    {
        Socket * s = 0;

        return recv(obj, s);
    }

    int send(Serializable& obj, const Socket& sock);

    int bind()
    {
        return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
        
    }

    friend std::ostream& operator<<(std::ostream& os, const Socket& dt);

    friend bool operator== (const Socket &s1, const Socket &s2);

    int sd;

    struct sockaddr sa;
    socklen_t       sa_len;

};

#endif /* SOCKET_H_ */


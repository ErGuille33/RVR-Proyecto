#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>

#include "Serializable.h"
#include "Socket.h"
#include "GameManager.h"

class ChatMessage: public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2
    };

    ChatMessage(){};

    ChatMessage(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type;

    std::string nick;
    std::string message;
};

class ChatServer
{
public:
    ChatServer(const char * s, const char * p): socket(s, p), gm()
    {
        int aux;
        aux = socket.bind();
    };

    void do_messages(Socket* sock1, Socket* sock2);

    bool accept_players();

private:

    std::vector<Socket *> clients;

    GameManager gm;
    Socket socket;
};

class ChatClient
{
public:

    ChatClient(const char * s, const char * p):socket(s, p) {};
    virtual ~ChatClient(){};

    void input_thread();

    void net_thread();

    Socket socket;
};


/////////////////////////////////////////////////////////////////////////////


class ClientPlayer : public Player, public ChatClient {
    public:
        ClientPlayer(const char * s, const char * p, const char * n, int id) : Player(n, id), ChatClient(s, p) {}

        virtual void login() {
            connect(socket.sd, &socket.sa, socket.sa_len);

            socket.send(*this, socket);

            std::cout << "LOGIN" << std::endl;
        }
};

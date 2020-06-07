#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>

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
    ChatServer(const char * s, const char * p): socket(s, p)
    {
        int aux;
        aux = socket.bind();
    };

    void do_messages(Socket* sock1, Socket* sock2);

    bool accept_players();

private:

    std::vector<Socket *> clients;


    Socket socket;
};

class ChatClient
{
public:

    ChatClient(const char * s, const char * p, const char * n):socket(s, p),
        nick(n){};
    virtual ~ChatClient(){  logout();};
 
    void login();

    void logout();

    void input_thread();

    void net_thread();

private:

    Socket socket;

    std::string nick;
};


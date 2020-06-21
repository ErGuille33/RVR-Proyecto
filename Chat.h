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

class PlayerInfo : public Serializable {

    public:
    PlayerInfo() {}
    PlayerInfo(int id, string name, int health, int ammo, int beer, int action) : Serializable() {
        _id = id;
        _name = name;
        _health = health;
        _beer = beer;
        _ammo = ammo;
        _action = action;
    }

    void to_bin();
    int from_bin(char * data);

    int _id;
    string _name;
    int _health;
    int _beer;
    int _ammo;
    int _action;

    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 5 + sizeof(char) * 8;

};


class ClientPlayer : public Player, public ChatClient {
    public:
        ClientPlayer(const char * s, const char * p, const char * n, int id) : Player(n, id), ChatClient(s, p) {}

        virtual void login() {
            connect(socket.sd, &socket.sa, socket.sa_len);

            PlayerInfo pi(_id, _name, _health, _ammo, _beer, currActionInt8);
            std::cout << pi._health << std::endl;
            socket.send(pi, socket);

            std::cout << "LOGIN" << std::endl;
        }
};

////////////////////////////////////////////////////////////

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

    ClientPlayer* client1;
    ClientPlayer* client2;

    GameManager gm;
    Socket socket;
};

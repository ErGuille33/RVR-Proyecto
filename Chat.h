#ifndef _GHAT_H
#define _CHAT_H
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
#include <iostream>

using namespace std;
using std::string;
class ChatMessage : public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN = 0,
        MESSAGE = 1,
        LOGOUT = 2
    };

    ChatMessage(){};

    ChatMessage(const std::string &n, const std::string &m) : nick(n), message(m){};

    void to_bin();

    int from_bin(char *bobj);

    uint8_t type;

    std::string nick;
    std::string message;
};

class ChatClient
{
public:
    ChatClient(const char *s, const char *p) : socket(s, p){};
    virtual ~ChatClient(){};

    void input_thread();

    void net_thread();

    Socket socket;
};

/////////////////////////////////////////////////////////////////////////////

class PlayerInfo : public Serializable
{

public:
    PlayerInfo() {}
    PlayerInfo(int id, string name, int health, int ammo, int beer, int action) : Serializable()
    {
        _id = id;
        _name = name;
        _health = health;
        _beer = beer;
        _ammo = ammo;
        _action = action;
        _turnoJugador = 0;
    }

    void to_bin();
    int from_bin(char *data);

    int _id;
    string _name;
    int _health;
    int _beer;
    int _ammo;
    int _action;
    int _turnoJugador;

    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 6 + sizeof(char) * 8;
};

class ClientPlayer : public Player, public ChatClient
{
public:
    ClientPlayer(const char *s, const char *p, const char *n, int id) : Player(n, id), ChatClient(s, p) {}

    virtual void login()
    {
        connect(socket.sd, &socket.sa, socket.sa_len);
        pi = new PlayerInfo(_id, _name, _health, _ammo, _beer, currActionInt8);
        socket.send(*pi, socket);

        piEnemy = new PlayerInfo(0, "", 3, 0, 0, 0);
        std::cout << "LOGIN" << std::endl;
        playerLoop();
    }

    virtual void playerLoop()
    {

        while (pi->_health > 0 && piEnemy->_health > 0)
        {
            waitForInput();
            showStats();
            input();
        }
        if (pi->_health == 0)
        {
            cout << "Has muerto. Game Over" << endl;
        }
        else if (piEnemy->_health == 0){
            cout << "Has ganado. Eres un máquina" << endl;
        }
    }

    void waitForInput()
    {
        Socket *outsocket;
        do
        {
            
            std::cout << "Primera iteracion del wait for input 1" << socket.recv(*pi,outsocket) << std::endl;
            std::cout << pi->_turnoJugador << "turno " << std::endl;
            std::cout << pi->_id << " id  " << std::endl;
            _health = pi->_health;
            _ammo = pi->_ammo;
            _beer = pi->_beer;
            std::cout << "Primera iteracion del wait for input 2" << socket.recv(*piEnemy,outsocket) << std::endl;
        
        } while (pi->_turnoJugador == 0);
       
        
    }

    void input()
    {
         std::cout << _name << " introduce acción: 0-Cargar 1-Disparar 2-Defensa 3-Curación 4-SuperDisparo 5-Nada" << std::endl;

        string aux;
        getline(std::cin, aux);

        int numb;
        numb = stoi(aux);

        pi->_action = numb;
        socket.send(*pi, socket);
    }

    void showStats()
    {
        std::cout << _name << " Vidas: " << pi->_health << " Balas: " << pi->_ammo << " Cervezas: " << pi->_beer << std::endl;
        std::cout << piEnemy->_name << " Enemigo vidas: " << piEnemy->_health << " Balas: " << piEnemy->_ammo << " Cervezas: " << piEnemy->_beer << std::endl;
    }
    PlayerInfo *pi;
    PlayerInfo *piEnemy;
};

////////////////////////////////////////////////////////////

class ChatServer
{
public:
    ChatServer(const char *s, const char *p) : socket(s, p), gm()
    {
        int aux;
        aux = socket.bind();
        std::cout << aux << "bind" <<std::endl;
    };

    void do_messages(Socket *sock1, Socket *sock2);

    bool accept_players();

private:
    std::vector<Socket *> clients;

    ClientPlayer *client1;
    ClientPlayer *client2;

    GameManager *gm;
    Socket socket;
};
#endif
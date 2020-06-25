#include "Chat.h"

void ChatMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;
    char *tmp = _data;

    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    nick[8] = '\0';
    memcpy(tmp, nick.c_str(), sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    message[80] = '\0';
    memcpy(tmp, message.c_str(), 80 * sizeof(char));
    tmp += 80 * sizeof(char);
}

int ChatMessage::from_bin(char *bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;

    char *tmp = _data;

    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    memcpy(&nick[0], tmp, sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    nick[8] = '\0';

    memcpy(&message[0], tmp, sizeof(char) * 80);
    tmp += sizeof(char) * 80;
    message[80] = '\0';

    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatServer::do_messages(Socket *sock1, Socket *sock2)
{/*
    std::cout << "do_messages" << std::endl;
    while (true)
    {
        ChatMessage obj;

        socket.recv(obj, sock1);
        socket.send(obj, *sock2);

        socket.recv(obj, sock2);
        socket.send(obj, *sock1);
    }*/
}

bool ChatServer::accept_players()
{
    std::cout << "accept_players" << std::endl;

    listen(socket.sd, 16);
    gm = new GameManager();
        PlayerInfo* obj = new PlayerInfo(0, "", 3, 0, 1, 0);
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(struct sockaddr_in);

        int sd_client1 = accept(socket.sd, (struct sockaddr *)&client_addr, &client_len);
        std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
        Socket *sock1 = new Socket((struct sockaddr *)&client_addr, client_len);
        sock1->sd = sd_client1;
        std::cout << socket.recvInit(*obj, sock1) << "Cout del recieve" << std::endl;
        PlayerInfo *newplayer1 = new PlayerInfo(0,obj->_name, obj->_health, obj->_ammo, obj->_beer, obj->_action);
        std::cout << newplayer1->_name << " se ha conectado" << std::endl;

        int sd_client2 = accept(socket.sd, (struct sockaddr *)&client_addr, &client_len);
        std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
        Socket *sock2 = new Socket((struct sockaddr *)&client_addr, client_len);
        sock2->sd = sd_client2;
        std::cout << socket.recvInit(*obj, sock2)<< "Cout del recieve" << std::endl;
        PlayerInfo *newplayer2 = new PlayerInfo(1, obj->_name, obj->_health, obj->_ammo, obj->_beer, obj->_action);
        std::cout << newplayer2->_name << " se ha conectado" << std::endl;

        gm->joinPlayers(newplayer1, newplayer2, sock1, sock2, &socket);

        gm->mainGameLoop();
        return false;
}

/////////////////////////////////////////////////////////////////////////////

void ChatClient::input_thread()
{
  /*  while (true)
    {
        std::string msg;
        std::getline(std::cin, msg);

        ChatMessage em("jose", msg);
        em.type = ChatMessage::MESSAGE;

        int cosa = socket.send(em, socket);
    }*/
}

void ChatClient::net_thread()
{/*
    while (true)
    {
        ChatMessage em;

        socket.recv(em);

        std::cout << &em.nick[0] << ": " << &em.message[0] << std::endl;
    }*/
}

////////////////////////////////////////////////////////////////////////////

void PlayerInfo::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;
    char *tmp = _data;

    //Vidas
    memcpy(tmp, &_health, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Balas
    memcpy(tmp, &_ammo, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Cervezas
    memcpy(tmp, &_beer, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Accion
    memcpy(tmp, &_action, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Id
    memcpy(tmp, &_id, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Turno de escoger 1 = si 0 = no;
    memcpy(tmp, &_turnoJugador, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Name
    _name[8] = '\0';
    memcpy(tmp, _name.c_str(), sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    std::cout << _name << "nombre mensaje "<< std::endl;
}

int PlayerInfo::from_bin(char *data)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;

    char *tmp = _data;

    //Vidas
    memcpy(&_health, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Balas
    memcpy(&_ammo, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Cervezas
    memcpy(&_beer, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Accion
    memcpy(&_action, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Id
    memcpy(&_id, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Turno de escoger 1 = su , 0 = no
    memcpy(&_turnoJugador, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Name
    memcpy(&_name[0], tmp, sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    _name[8] = '\0';

    return 0;
}

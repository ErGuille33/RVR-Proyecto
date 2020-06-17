#include "Chat.h"

void ChatMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;
    char * tmp = _data;

    memcpy(tmp, &type , sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    nick[8] = '\0';
    memcpy(tmp, nick.c_str(), sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    message[80] = '\0';
    memcpy(tmp, message.c_str(), 80 * sizeof(char) );
    tmp += 80 *sizeof(char);
}

int ChatMessage::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);
    _size = MESSAGE_SIZE;

    char * tmp = _data;

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

void ChatServer::do_messages(Socket* sock1, Socket* sock2)
{
    std::cout << "do_messages" << std::endl;
    while(true) {
        ChatMessage obj;

        socket.recv(obj, sock1);
        socket.send(obj, *sock2);

        socket.recv(obj, sock2);
        socket.send(obj, *sock1);
    }
}

bool ChatServer::accept_players() {
    std::cout << "accept_players" << std::endl;


    listen(socket.sd,16);
    while(true)
    {
        ChatMessage obj;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(struct sockaddr_in);

        int sd_client1 = accept(socket.sd, (struct sockaddr *) &client_addr, &client_len);
        std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
        Socket* sock1 = new Socket((struct sockaddr*)&client_addr, client_len);
        sock1->sd = sd_client1;
        socket.recv(obj, sock1);
        std::cout << obj.nick << std::endl;
        Player* newplayer1 = new Player();
        newplayer1->from_bin(obj.data());

        
        int sd_client2 = accept(socket.sd, (struct sockaddr *) &client_addr, &client_len);
        std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
        Socket* sock2 = new Socket((struct sockaddr*)&client_addr, client_len);
        sock2->sd = sd_client2;
        socket.recv(obj, sock2);
        Player* newplayer2 = new Player();
        newplayer2->from_bin(obj.data());

        gm.joinPlayers(newplayer1, newplayer2);

        std::thread t(&GameManager::mainGameLoop, gm);
        t.detach();
    }

}

/////////////////////////////////////////////////////////////////////////////

void ChatClient::input_thread()
{
    while (true)
    {
        std::string msg;
        std::getline(std::cin, msg);

        ChatMessage em("jose", msg);
        em.type = ChatMessage::MESSAGE;
        std::cout << "antes de send" << std::endl;
        int cosa = socket.send(em, socket);
    }
}

void ChatClient::net_thread()
{
    while(true)
    {
        ChatMessage em;
         
        socket.recv(em);

        std::cout << &em.nick[0] << ": " << &em.message[0] << std::endl;
    }
}


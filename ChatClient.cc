#include <string>
#include <unistd.h>
#include <string.h>
#include "Game.h"

extern "C" void * _client_thread(void *arg)
{
    Client * server = static_cast<Client *>(arg);

    server->net_thread();

    return 0;
}

int main(int argc, char **argv)
{
    ClientPlayer* ec = new ClientPlayer(argv[1], argv[2], argv[3], 0);

    pthread_attr_t attr;
    pthread_t id;

    Game* g = new Game(ec);
    std::cout << "Game running..." << std::endl;
	g->run();

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&id, &attr, _client_thread, static_cast<void *>(&ec));
    
	delete g;

}





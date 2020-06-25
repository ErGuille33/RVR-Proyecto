#include "GameManager.h"
#include "Chat.h"

using namespace std;

void GameManager::sendResults(){
    playerInfo1->_ammo = player1->getAmmo();
    playerInfo1->_health = player1->getHealth();
    playerInfo1->_beer = player1->getBeer();
    playerInfo1->_turnoJugador = 1;

    sock1->send(*playerInfo1,*sock1);
    sock1->send(*playerInfo2,*sock1);



    playerInfo2->_ammo = player2->getAmmo();
    playerInfo2->_health = player2->getHealth();
    playerInfo2->_beer = player2->getBeer();
    playerInfo2->_turnoJugador = 1;

    sock2->send(*playerInfo2,*sock2);
    sock2->send(*playerInfo1,*sock2);
    std::cout << "Pueden salir ya mis nenes" << std::endl;

}

void GameManager::selectionPhase()
{
    Socket *outsocket;


    sock1->recv(*playerInfo1,outsocket);
    playerInfo1->_turnoJugador = 0;
    sock1->send(*playerInfo1,*sock1);
    sock1->send(*playerInfo2,*sock1);
     std::cout << "No puedes jubar 1" << std::endl;

    sock2->recv(*playerInfo2,outsocket);
    playerInfo2->_turnoJugador = 0;
    sock2->send(*playerInfo2,*sock2);
     sock2->send(*playerInfo1,*sock2);
     std::cout << "No puedes jubar 2" << std::endl;

    player1->_currentAction = static_cast<Action>(playerInfo1->_action);
    player2->_currentAction = static_cast<Action>(playerInfo2->_action);
}

int GameManager::mainGameLoop(){
    {
        
        while (player1->getHealth() > 0 && player2->getHealth() > 0)
        {
            
            selectionPhase();

            battlePhase();
            
            showStats(player1);
            showStats(player2);

            sendResults();
            
        }

        if (player1->getHealth() <= 0)
        {
            cout << player2->getName() << " Wins" << endl;
            playerInfo2->_health = 10;
            sock2->send(*playerInfo2,*sock2);
            sock2->send(*playerInfo1,*sock2);

        }
        else {
            cout << player1->getName() << " Wins" << endl;
            playerInfo1->_health = 20;
            sock1->send(*playerInfo1,*sock1);
            sock1->send(*playerInfo2,*sock1);
        }
        return 0;
    }
}
void GameManager::battlePhase()
{
    switch (player1->_currentAction)
    {
        //
        //Accion de cargar del primer jugador
        //

    case Action::cargar:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            player1->Reload();
            player2->Reload();
            break;
        case Action::disparo:
            if (player2->getAmmo() > 0)
            {
                player1->addHealth(-1);
                player2->addAmmo(-1);
            }
            else
            {
                player1->Reload();
                cout << player2->getName() << " no tienes balas" << endl;
            }
            break;
        case Action::defensa:
            player1->Reload();
            break;
        case Action::curacion:
            player1->Reload();
            player2->Heal();
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot())
            {
                player2->addAmmo(-3);
                player1->addHealth(-1);
            }
            else
            {
                player1->Reload();
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
            }
            break;
        case Action::idle:
            player1->Reload();
            break;
        }
        break;
        //
        //Accion de disparo del primer jugador
        //
    case Action::disparo:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            if (player1->getAmmo() > 0)
            {
                player2->addHealth(-1);
                player1->addAmmo(-1);
            }
            else
            {
                player2->Reload();
                cout << player1->getName() << " no tienes balas" << endl;
            }
            break;
        case Action::disparo:
            if (player2->getAmmo() > 0 && player1->getAmmo() > 0)
            {
                player1->addAmmo(-1);
                player2->addAmmo(-1);
            }
            else
            {
                if (player2->getAmmo() <= 0 && player1->getAmmo() > 0)
                {
                    player1->addAmmo(-1);
                    player2->addHealth(-1);
                    cout << player2->getName() << " no tienes balas" << endl;
                }
                else if (player1->getAmmo() <= 0 && player2->getAmmo() > 0)
                {
                    player2->addAmmo(-1);
                    player1->addHealth(-1);
                    cout << player1->getName() << " no tienes balas" << endl;
                }
                else
                {
                    cout << "Nadie tiene balas" << endl;
                }
            }
            break;
        case Action::defensa:
            if (player1->getAmmo() > 0)
                player1->addAmmo(-1);
            else
                cout << player1->getName() << " no tienes balas" << endl;
            break;
        case Action::curacion:
            if (player1->getAmmo() > 0)
            {
                player2->addHealth(-1);
                player1->addAmmo(-1);
                if (player2->getBeer() > 0)
                {
                    player2->addBeer(-1);
                }
            }
            else
            {
                cout << player1->getName() << " no tienes balas" << endl;
                player2->Heal();
            }
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot())
            {
                player2->addAmmo(-3);
                player1->addHealth(-1);
                player1->addAmmo(-1);
            }
            else
            {
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
                if (player1->getAmmo() > 0)
                {
                    player2->addHealth(-1);
                    player1->addAmmo(-1);
                }
                else
                    cout << player1->getName() << " no tienes balas" << endl;
            }
            break;
        case Action::idle:
            if (player1->getAmmo() > 0)
            {
                player2->addHealth(-1);
                player1->addAmmo(-1);
            }
            break;
        }
        break;

        //
        //Acción de defensa del primer jugador
        //
    case Action::defensa:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            player2->Reload();
            break;
        case Action::disparo:
            if (player2->getAmmo() > 0)
            {
                player2->addAmmo(-1);
            }
            else
            {
                cout << player2->getName() << " no tienes balas" << endl;
            }
            break;
        case Action::defensa:
            break;
        case Action::curacion:
            player2->Heal();
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot())
            {
                player2->addAmmo(-3);
                player1->addHealth(-1);
            }
            else
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
            break;
        case Action::idle:
            break;
        }
        break;
        //
        //Accion de curacion del primer jugador
        //
    case Action::curacion:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            player2->Reload();
            player1->Heal();
            break;
        case Action::disparo:
            if (player2->getAmmo() > 0)
            {
                player1->addHealth(-1);
                player2->addAmmo(-1);
                if (player1->getBeer() > 0)
                {
                    player1->addBeer(-1);
                }
            }
            else
            {
                cout << player2->getName() << " no tienes balas" << endl;
                player1->Heal();
            }
            break;
        case Action::defensa:
            player1->Heal();
            break;
        case Action::curacion:
            player1->Heal();
            player2->Heal();
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot())
            {
                player2->addAmmo(-3);
                player1->addHealth(-1);
            }
            else
            {
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
                player1->Heal();
            }
            break;
        case Action::idle:
            player1->Heal();
            break;
        }
        break;

    //
    //ACCION DE SUPER DISPARO DEL PRIMER JUGADOR
    //
    case Action::superdisparo:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            if (player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addHealth(-1);
            }
            else
            {
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
                player2->Reload();
            }
            break;
        case Action::disparo:
            if (player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addHealth(-1);
                player2->addAmmo(-1);
            }
            else
            {
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
                if (player2->getAmmo() > 0)
                {
                    player1->addHealth(-1);
                    player2->addAmmo(-1);
                }
                else
                    cout << player2->getName() << " no tienes balas" << endl;
            }
            break;
        case Action::defensa:
            if (player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addHealth(-1);
            }
            else
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
            break;
        case Action::curacion:
            if (player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addHealth(-1);
            }
            else
            {
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
                player2->Heal();
            }
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot() && player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addAmmo(-3);
            }
            else if (player2->canISuperShoot() && !player1->canISuperShoot())
            {
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
                player2->addAmmo(-3);
                player1->addHealth(-1);
            }
            else if (!player2->canISuperShoot() && player1->canISuperShoot())
            {
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
                player1->addAmmo(-3);
                player2->addHealth(-1);
            }
            else
            {
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
            }
            break;
        case Action::idle:
            if (player1->canISuperShoot())
            {
                player1->addAmmo(-3);
                player2->addHealth(-1);
            }
            else
            {
                cout << player1->getName() << " no tienes balas suficientes para el super disparo" << endl;
            }
            break;
        }
        break;
    //
    //ACCION DE idle
    //
    case Action::idle:
        switch (player2->_currentAction)
        {
        case Action::cargar:
            player2->Reload();
            break;
        case Action::disparo:
            if (player2->getAmmo() > 0)
            {
                player1->addHealth(-1);
                player2->addAmmo(-1);
            }
            else
                cout << player2->getName() << " no tienes balas" << endl;
            break;
        case Action::defensa:
            break;
        case Action::curacion:
            player2->Heal();
            break;
        case Action::superdisparo:
            if (player2->canISuperShoot())
            {
                player2->addAmmo(-3);
                player1->addHealth(-1);
            }
            else
            {
                cout << player2->getName() << " no tienes balas suficientes para el super disparo" << endl;
            }
            break;
        case Action::idle:
            break;
        }
        break;
    default:
        break;
    }
}

void GameManager::joinPlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain) {
    
    player1->setAll(playerone->_id, playerone->_name, 3, 0, 1, playerone->_action);
    player2->setAll(playertwo->_id, playertwo->_name, 3, 0, 1, playertwo->_action);
    playerInfo1 = playerone;
    playerInfo2 = playertwo;

    playerInfo1->_turnoJugador = 1;
    playerInfo2->_turnoJugador = 1;

    sock1 = sockone;
    sock2 = socktwo;

    socket = socketMain;

    sock1->send(*playerInfo1,*sock1);
    sock1->send(*playerInfo2,*sock1);

    sock2->send(*playerInfo2,*sock2);
    sock2->send(*playerInfo1,*sock2);
}


#include "GameManager.h"

using namespace std;

void GameManager::selectionPhase(Player *player)
{
    string aux = "";
    int numb;

    do
    {
        cout << player->getName() << " introduce acción: 0-Cargar 1-Disparar 2-Defensa 3-Curación 4-SuperDisparo 5-Nada " << endl;
        getline(cin, aux);
        numb = stoi(aux);
    } while (numb < 0 || numb > 6);
    player->_currentAction = static_cast<Action>(numb);
}

int GameManager::mainGameLoop(){
    {
        std::cout << player1->getName() << std::endl;
        std::cout << player2->getName() << std::endl;
        while (player1->getHealth() > 0 && player2->getHealth() > 0)
        {
            selectionPhase(player1);
            selectionPhase(player2);

            battlePhase();
            showStats(player1);
            showStats(player2);
        }

        if (player1->getHealth() <= 0)
        {
            cout << player2->getName() << " Wins" << endl;
        }
        else
            cout << player1->getName() << " Wins" << endl;
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

void GameManager::joinPlayers(Player* playerone, Player* playertwo) {
    player1 = playerone;
    player2 = playertwo;
}


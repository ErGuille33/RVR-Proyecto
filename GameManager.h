#include <iostream>
#include <string>

using namespace std;

enum Action
{
    cargar,
    disparo,
    defensa,
    curacion,
    superdisparo,
    idle
};

class Player
{
private:
    int _id;
    string _name;
    int _health = 3;
    int _beer = 2;
    int _ammo = 0;

public:
    Player(string nombre, int id)
    {
        _name = nombre;
        _id = id;
    };
    ~Player(){};

    int getHealth() { return _health; };
    int addHealth(int hp)
    {
        _health = _health + hp;
        return _health;
    };

    int getId() { return _id; };
    string getName() { return _name; };

    int getAmmo() { return _ammo; };
    int addAmmo(int num)
    {
        _ammo = _ammo + num;
        return _ammo;
    };

    int getBeer() { return _beer; };
    int addBeer(int num)
    {
        _beer = _beer + num;
        return _beer;
    };

    void Heal()
    {
        if (getBeer() > 0)
        {
            if (getHealth() < 3)
            {
                addHealth(1);
                addBeer(-1);
            }
            else
                cout << getName() << " ya estás a máxima vida" << endl;
        }
        else
            cout << getName() << " no quedan cervezas" << endl;
    }

    void Reload()
    {
        if (getAmmo() < 6)
            addAmmo(1);
        else
            cout << getName() << " cargador lleno" << endl;
    }

    bool canISuperShoot()
    {
        if (getAmmo() >= 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Action _currentAction;
};

class GameManager
{
private:
    Player *player1;
    Player *player2;

public:
    GameManager(Player *player_one, Player *player_two)
    {
        player1 = player_one;
        player2 = player_two;
    };
    ~GameManager()
    {
        delete player1;
        delete player2;
    };
    //Devuelve la situación de ambos jugadores
    void showStats(Player *player)
    {
        cout << player->getName() << " Vidas: " << player->getHealth() << " Balas: " << player->getAmmo() << " Cervezas: " << player->getBeer() << endl;
    }
    //Para seleccionar la acción
    void selectionPhase(Player *player)
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

    //Este método consiste en un switch enorme que contemplará todos los casos posibles a la hora de batirse en duelo
    void battlePhase()
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

    int mainGameLoop()
    {
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
    }
};

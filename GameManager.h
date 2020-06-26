#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <iostream>
#include <string>
#include <string.h>

#include "Socket.h"
#include "Serializable.h"

class PlayerInfo;

using namespace std;

enum Action
{
    cargar,
    disparo,
    defensa,
    curacion,
    superdisparo,
    idle,
    conecct
};

class Player
{
protected:
    int _id;
    string _name;
    int _health = 3;
    int _beer = 1;
    int _ammo = 0;

    Action currAction = Action::idle;
    int currActionInt8 = 5;

public:
    Player() {}
    Player(string nombre, int id)
    {
        _name = nombre;
        _id = id;
        _health = 3;
        _ammo = 0;
        _beer = 1;
        currAction = Action::idle;
        currActionInt8 = 5;    
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

    void setCurrAction(int act) {
        currActionInt8 = act;
        currAction= static_cast<Action>(currAction);
    }

    void setId(int newid) {
        _id = newid;
    }

    void setAll(int id, string name, int health, int ammo, int beer, int action) {
        _id = id;
        _name = name;
        _health = health;
        _ammo = ammo;
        _beer = beer;
        currAction = static_cast<Action>(action);
    }

    Action _currentAction;

};

class GameManager
{
private:
    Player *player1;
    Player *player2;
    PlayerInfo* playerInfo1;
    PlayerInfo* playerInfo2;

    Socket* sock1;
    Socket* sock2;

    Socket* socket;

public:
    GameManager() {
        player1 = new Player("a", 0);
        player2 = new Player("b", 0);
       
    }
    ~GameManager()
    {
        delete player1;
        delete player2;
        delete sock1;
        delete sock2;
        delete socket;
      


    };
    //Devuelve la situación de ambos jugadores
    void showStats(Player *player)
    {
        cout << player->getName() << " Vidas: " << player->getHealth() << " Balas: " << player->getAmmo() << " Cervezas: " << player->getBeer() << endl;
    }

    void sendResults();
    //Para seleccionar la acción
    void selectionPhase();

    //Este método consiste en un switch enorme que contemplará todos los casos posibles a la hora de batirse en duelo
    void battlePhase();

    int mainGameLoop();

    void joinPlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain);
    
};
#endif
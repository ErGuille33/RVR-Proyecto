#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

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

class Player: public Serializable
{
private:
    int _id;
    string _name;
    int _health = 3;
    int _beer = 2;
    int _ammo = 0;

    Action currAction;
    uint8_t currActionInt8;

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

    void setCurrAction(Action act) {
        currAction = act;
        currActionInt8 = static_cast<uint8_t>(currAction);
    }

    Action _currentAction;
    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 3;

    void to_bin() {

        alloc_data(MESSAGE_SIZE);

        memset(_data, 0, MESSAGE_SIZE);
        _size = MESSAGE_SIZE;
        char* tmp = _data;

        //Vidas
        memcpy(tmp, &type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);
        //Balas
        memcpy(tmp, &type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);
        //Cervezas
        memcpy(tmp, &type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);
        //Accion
        memcpy(tmp, &type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);
        //Id
        memcpy(tmp, &type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);

    }
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
    void selectionPhase(Player *player);

    //Este método consiste en un switch enorme que contemplará todos los casos posibles a la hora de batirse en duelo
    void battlePhase();

    int mainGameLoop();
    
};
#endif
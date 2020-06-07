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
    void selectionPhase(Player *player);

    //Este método consiste en un switch enorme que contemplará todos los casos posibles a la hora de batirse en duelo
    void battlePhase();

    int mainGameLoop();
    
};
#endif
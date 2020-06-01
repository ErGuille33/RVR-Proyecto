#include <iostream>
#include <string>
#include "GameManager.h"

using namespace std;

int main()
{
    string nombre;
    cout << "Jugador 1 Introduce tu nombre: " << endl;
    getline(cin, nombre);

    Player *player1 = new Player(nombre, 0);

    cout << "Jugador 2 Introduce tu nombre: " << endl;
    getline(cin, nombre);

    Player *player2 = new Player(nombre, 1);

    cout << player1->getName() << " y " << player2->getName() << " conectados" << endl;

    GameManager gm(player1, player2);
    gm.mainGameLoop();

    return 0;
}
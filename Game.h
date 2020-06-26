#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include <string>
#include <iostream>
#include "Chat.h"
#include "Button.h"
#include "GameObject.h"

enum TexturesName{Background, Recarga, Ataque, Beer, Escudo, Superataque, Wood, Heart, Ammo, Cerveza, Bandit1, Bandit2, Bandit3, CowBoy1, CowBoy2, CowBoy3,
 Ready, Muerto, Win, Recarga1, Ataque1, Beer1, Escudo1, Superataque1};
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 24;
const string RUTA = "Assets/";
const uint32_t FRAME_RATE = 30;
const double speed = 10;


class Game
{
private:

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	Texture* texturas_[NUM_TEXTURES];

	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};
	TexturesAtributes atributes_[NUM_TEXTURES] = { "background.png", 1, 1, "Reload.png", 1, 1, "Ataque.png", 1, 1, "beer.png", 1, 1, "Escudo.png", 1, 1, 
	"SuperAtaque.png", 1, 1, "Wood.png", 1, 1, "heart.png", 1, 1, "ammo.png", 1, 1, "beer0.png", 1, 1, "Bd1.png", 1, 1, "Bd3.png", 1, 1, "Bd5.png", 1, 1,
	"Cb1.png", 1, 1, "Cb2.png", 1, 1, "Cb4.png", 1, 1, "Flecha1.png", 1, 1, "Muerto.png", 1, 1, "Win.png", 1, 1,"Reload1.png", 1, 1, "Ataque1.png", 1, 1, "Beer1.png", 1, 1, "Escudo1.png", 1, 1, 
	"SuperAtaque1.png", 1, 1};

	ClientPlayer* player;

	Button* recargaB;
	Button* ataqueB;
	Button* beerB;
	Button* escudoB;
	Button* superataqueB;
	Button* readyB;

	GameObject recargaE;
	GameObject escudoE;
	GameObject ataqueE;
	GameObject beerE;
	GameObject superataqueE;

	GameObject wood;

	GameObject heart1;
	GameObject heart2;
	GameObject heart3;

	GameObject enemyHeart1;
	GameObject enemyHeart2;
	GameObject enemyHeart3;

	GameObject ammo1;
	GameObject ammo2;
	GameObject ammo3;
	GameObject ammo4;
	GameObject ammo5;
	GameObject ammo6;

	GameObject enemyAmmo1;
	GameObject enemyAmmo2;
	GameObject enemyAmmo3;
	GameObject enemyAmmo4;
	GameObject enemyAmmo5;
	GameObject enemyAmmo6;

	GameObject beer1;
	GameObject enemyBeer;

	GameObject win;
	GameObject lose;

	GameObject cowboy;
	GameObject bandit;

	int enviar = 5;

public:
	Game(ClientPlayer* cp);
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();
	void showStats();

	static void recargar(ClientPlayer* cp);
	static void disparar(ClientPlayer* cp);
	static void defender(ClientPlayer* cp);
	static void beer(ClientPlayer* cp);
	static void superdisparo(ClientPlayer* cp);
	static void ready(ClientPlayer* cp);
	
	
};
	
	


	


#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include <string>
#include <iostream>
#include "Chat.h"
#include "Button.h"

enum TexturesName{Background, Recarga, Ataque, Beer, Escudo, Superataque};
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 6;
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
	TexturesAtributes atributes_[NUM_TEXTURES] = { "background.png", 1, 1, "Reload.png", 1, 1, "Ataque.png", 1, 1, "beer.png", 1, 1, "Escudo.png", 1, 1, "SuperAtaque.png", 1, 1 };

	ClientPlayer* player;

	Button* recargaB;
	Button* ataqueB;
	Button* beerB;
	Button* escudoB;
	Button* superataqueB;

	int enviar;

public:
	Game(ClientPlayer* cp);
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();

	static void recargar(ClientPlayer* cp);
	static void disparar(ClientPlayer* cp);
	static void defender(ClientPlayer* cp);
	static void beer(ClientPlayer* cp);
	static void superdisparo(ClientPlayer* cp);
};
	
	


#include "Game.h"

void Game::recargar(ClientPlayer* cp){
	cp->pi->_action = 0;
}
void Game::disparar(ClientPlayer* cp){
	cp->pi->_action = 1;
}
void Game::defender(ClientPlayer* cp){
	cp->pi->_action = 2;
}
void Game::beer(ClientPlayer* cp){
	cp->pi->_action = 3;
}
void Game::superdisparo(ClientPlayer* cp){
	cp->pi->_action = 4;
}

Game::Game(ClientPlayer* cp) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Pistolero", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	std::cout << "Loading textures..." << std::endl;
	for (int i = 0; i < NUM_TEXTURES; i++) {
		texturas_[i] = new Texture(renderer_, (RUTA + atributes_[i].nombre), atributes_[i].row, atributes_[i].col);
	}

	player = cp;
	player->login();

	recargaB = new Button(200, 200, 100, 50, texturas_[Recarga], player, recargar);
	ataqueB = new Button(10, 10, 100, 50, texturas_[Ataque], player, disparar);
	escudoB = new Button(150, 10, 100, 50, texturas_[Escudo], player, defender);
	beerB = new Button(10, 100, 100, 50, texturas_[Beer], player, beer);
	superataqueB = new Button(150, 100, 100, 50, texturas_[Superataque], player, superdisparo);

}

void Game::render() {
	SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, texturas_[Background]->getTexture(), NULL, NULL);
	recargaB->render();
	ataqueB->render();
	beerB->render();
	escudoB->render();
	superataqueB->render();
	SDL_RenderPresent(renderer_);
}

void Game::handleEvents() {
	SDL_Event evt;
	bool handled = false;
	player->pulsado = false;
	while (SDL_PollEvent(&evt) && !exit) {
		if (evt.type == SDL_QUIT) {
			exit = true;
		}
		player->pulsado = recargaB->handleEvent(evt);
		if(!player->pulsado) player->pulsado = ataqueB->handleEvent(evt);
		if(!player->pulsado) player->pulsado = beerB->handleEvent(evt);
		if(!player->pulsado) player->pulsado = escudoB->handleEvent(evt);
		if(!player->pulsado) player->pulsado = superataqueB->handleEvent(evt);
		if(player->pulsado) {
			std::cout << "Pulsado " << player->pi->_action << std::endl;
			enviar = player->pi->_action;
		}
	}
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		render();
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}
	}
}

void Game::update() {
	if(!player->update(enviar)) {
		exit = true;
	}
}

Game::~Game() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete texturas_[i];

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}


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

	recargaB = new Button(125, 210, 150, 100, texturas_[Recarga], player, recargar);
	ataqueB = new Button(50, 10, 150, 100, texturas_[Ataque], player, disparar);
	escudoB = new Button(225, 10, 150, 100, texturas_[Escudo], player, defender);
	beerB = new Button(50, 100, 150, 100, texturas_[Beer], player, beer);
	superataqueB = new Button(225, 100, 150, 100, texturas_[Superataque], player, superdisparo);

	wood.setValue(375, 0, 91, 600, texturas_[Wood]);

	heart1.setValue(10, 520, 47, 50, texturas_[Heart]);
	heart2.setValue(60,520, 47, 50, texturas_[Heart]);
	heart3.setValue(110,520, 47, 50, texturas_[Heart]);

	enemyHeart1.setValue(440, 520, 47, 50, texturas_[Heart]);
	enemyHeart2.setValue(490, 520, 47, 50, texturas_[Heart]);
	enemyHeart3.setValue(540, 520, 47, 50, texturas_[Heart]);

	ammo1.setValue(190, 465, 20, 50, texturas_[Ammo]);
	ammo2.setValue(220, 465, 20, 50, texturas_[Ammo]);
	ammo3.setValue(250, 465, 20, 50, texturas_[Ammo]);
	ammo4.setValue(190, 525, 20, 50, texturas_[Ammo]);
	ammo5.setValue(220, 525, 20, 50, texturas_[Ammo]);
	ammo6.setValue(250, 525, 20, 50, texturas_[Ammo]);

	enemyAmmo1.setValue(610, 465, 20, 50, texturas_[Ammo]);
	enemyAmmo2.setValue(640, 465, 20, 50, texturas_[Ammo]);
	enemyAmmo3.setValue(670, 465, 20, 50, texturas_[Ammo]);
	enemyAmmo4.setValue(610, 525, 20, 50, texturas_[Ammo]);
	enemyAmmo5.setValue(640, 525, 20, 50, texturas_[Ammo]);
	enemyAmmo6.setValue(670, 525, 20, 50, texturas_[Ammo]);

	beer1.setValue(300, 520, 50, 50, texturas_[Cerveza]);
	enemyBeer.setValue(720, 520, 50, 50, texturas_[Cerveza]);

}

void Game::render() {
	SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, texturas_[Background]->getTexture(), NULL, NULL);
	recargaB->render();
	ataqueB->render();
	beerB->render();
	escudoB->render();
	superataqueB->render();
	wood.render();
	heart1.render();
	heart2.render();
	heart3.render();
	enemyHeart1.render();
	enemyHeart2.render();
	enemyHeart3.render();
	ammo1.render();
	ammo2.render();
	ammo3.render();
	ammo4.render();
	ammo5.render();
	ammo6.render();
	enemyAmmo1.render();
	enemyAmmo2.render();
	enemyAmmo3.render();
	enemyAmmo4.render();
	enemyAmmo5.render();
	enemyAmmo6.render();
	beer1.render();
	enemyBeer.render();
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

void Game::showStats(){
	//Vida
	if(player->pi->_health == 3){
		heart1.setEnabled(true);
		heart2.setEnabled(true);
		heart3.setEnabled(true);
	}
	else if(player->pi->_health == 2){
		heart1.setEnabled(true);
		heart2.setEnabled(true);
		heart3.setEnabled(false);
	}
	else if(player->pi->_health == 1){
		heart1.setEnabled(true);
		heart2.setEnabled(false);
		heart3.setEnabled(false);
	}
	else if(player->pi->_health == 0){
		heart1.setEnabled(false);
		heart2.setEnabled(false);
		heart3.setEnabled(false);
	}
	//VIda enemigo
	if(player->piEnemy->_health == 3){
		enemyHeart1.setEnabled(true);
		enemyHeart2.setEnabled(true);
		enemyHeart3.setEnabled(true);
	}
	else if(player->piEnemy->_health == 2){
		enemyHeart1.setEnabled(true);
		enemyHeart2.setEnabled(true);
		enemyHeart3.setEnabled(false);
	}
	else if(player->piEnemy->_health == 1){
		enemyHeart1.setEnabled(true);
		enemyHeart2.setEnabled(false);
		enemyHeart3.setEnabled(false);
	}
	else if(player->piEnemy->_health == 0){
		enemyHeart1.setEnabled(false);
		enemyHeart2.setEnabled(false);
		enemyHeart3.setEnabled(false);
	}
	//Municion
	if(player->pi->_ammo == 6){
		ammo1.setEnabled(true);
		ammo2.setEnabled(true);
		ammo3.setEnabled(true);
		ammo4.setEnabled(true);
		ammo5.setEnabled(true);
		ammo6.setEnabled(true);
	}
	else if(player->pi->_ammo == 5){
		ammo1.setEnabled(true);
		ammo2.setEnabled(true);
		ammo3.setEnabled(true);
		ammo4.setEnabled(true);
		ammo5.setEnabled(true);
		ammo6.setEnabled(false);
	}
	else if(player->pi->_ammo == 4){
		ammo1.setEnabled(true);
		ammo2.setEnabled(true);
		ammo3.setEnabled(true);
		ammo4.setEnabled(true);
		ammo5.setEnabled(false);
		ammo6.setEnabled(false);
	}
	else if(player->pi->_ammo == 3){
		ammo1.setEnabled(true);
		ammo2.setEnabled(true);
		ammo3.setEnabled(true);
		ammo4.setEnabled(false);
		ammo5.setEnabled(false);
		ammo6.setEnabled(false);
	}
	else if(player->pi->_ammo == 2){
		ammo1.setEnabled(true);
		ammo2.setEnabled(true);
		ammo3.setEnabled(false);
		ammo4.setEnabled(false);
		ammo5.setEnabled(false);
		ammo6.setEnabled(false);
	}
	else if(player->pi->_ammo == 1){
		ammo1.setEnabled(true);
		ammo2.setEnabled(false);
		ammo3.setEnabled(false);
		ammo4.setEnabled(false);
		ammo5.setEnabled(false);
		ammo6.setEnabled(false);
	}
	else if(player->pi->_ammo == 0){
		ammo1.setEnabled(false);
		ammo2.setEnabled(false);
		ammo3.setEnabled(false);
		ammo4.setEnabled(false);
		ammo5.setEnabled(false);
		ammo6.setEnabled(false);
	}
	//Municion Enemiga
	if(player->piEnemy->_ammo == 6){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(true);
		enemyAmmo3.setEnabled(true);
		enemyAmmo4.setEnabled(true);
		enemyAmmo5.setEnabled(true);
		enemyAmmo6.setEnabled(true);
	}
	else if(player->piEnemy->_ammo == 5){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(true);
		enemyAmmo3.setEnabled(true);
		enemyAmmo4.setEnabled(true);
		enemyAmmo5.setEnabled(true);
		enemyAmmo6.setEnabled(false);
	}
	else if(player->piEnemy->_ammo == 4){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(true);
		enemyAmmo3.setEnabled(true);
		enemyAmmo4.setEnabled(true);
		enemyAmmo5.setEnabled(false);
		enemyAmmo6.setEnabled(false);
	}
	else if(player->piEnemy->_ammo == 3){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(true);
		enemyAmmo3.setEnabled(true);
		enemyAmmo4.setEnabled(false);
		enemyAmmo5.setEnabled(false);
		enemyAmmo6.setEnabled(false);
	}
	else if(player->piEnemy->_ammo == 2){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(true);
		enemyAmmo3.setEnabled(false);
		enemyAmmo4.setEnabled(false);
		enemyAmmo5.setEnabled(false);
		enemyAmmo6.setEnabled(false);
	}
	else if(player->piEnemy->_ammo == 1){
		enemyAmmo1.setEnabled(true);
		enemyAmmo2.setEnabled(false);
		enemyAmmo3.setEnabled(false);
		enemyAmmo4.setEnabled(false);
		enemyAmmo5.setEnabled(false);
		enemyAmmo6.setEnabled(false);
	}
	else if(player->piEnemy->_ammo == 0){
		enemyAmmo1.setEnabled(false);
		enemyAmmo2.setEnabled(false);
		enemyAmmo3.setEnabled(false);
		enemyAmmo4.setEnabled(false);
		enemyAmmo5.setEnabled(false);
		enemyAmmo6.setEnabled(false);
	}
	//Cerveza
	if(player->pi->_beer == 1){
		beer1.setEnabled(true);
	}
	else if(player->pi->_beer == 0){
		beer1.setEnabled(false);
	}
	//Cerveza enemiga
	if(player->piEnemy->_beer == 1){
		enemyBeer.setEnabled(true);
	}
	else if(player->piEnemy->_beer == 0){
		enemyBeer.setEnabled(false);
	}
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			showStats();
			render();
			update();
			handleEvents();
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


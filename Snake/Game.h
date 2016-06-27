#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "Queue.h"
#include "GameButton.hpp"

enum State {menu, playing, win, lose};


// Classe Game

class Game
{
public:
	Game();
	//~Game();

	void run();									// Loop principal do jogo
	void eventHandler();						// Gerenciador de eventos
	void update(float);							// Atualiza conteúdo do jogo
	void draw();								// Exibe conteúdo na janela

private:
	sf::RenderWindow mainWindow;				// Janela
	unsigned int windowWidth, windowHeight;		// Largura e altura da janela
	State currentState;							// Estado atual do jogo

	Tile background;
	Tile food;
	GameButton newGameButton;
	GameButton exitButton;
	Direction currentDirection;

	int currentButton;

	Queue snake;
};
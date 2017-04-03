#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "StaticStack.h"
#include "GameButton.hpp"

enum State { menu, playing, win, lose};
enum GameStacks {none, stack1, stack2, stack3};

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

	// Layout do jogo (será excluído)
	sf::Sprite sLayout;
	sf::Texture tLayout;

	// Pilhas do jogo
	StaticStack <Tile> * stack1;
	StaticStack <Tile> * stack2;
	StaticStack <Tile> * stack3;

	// Imagens básicas do jogo
	Tile background;
	Tile bahamut;
	Tile monsterStack;
	Tile stack1Edge;
	Tile stack2Edge;
	Tile stack3Edge;
	Tile healthAndMoves;
	Tile youWin;
	Tile youLose;

	// Pilhas selecionadas/ estado do botão
	GameStacks currentStack;
	GameStacks nextStack;
	GameButton playButton;

	// Textos do jogo
	sf::Font font;
	sf::Text labelStack1;
	sf::Text labelStack2;
	sf::Text labelStack3;
	sf::Text labelMonsterStack;

	// Atributos do jogador
	sf::Vector2i HealthPosition;
	sf::Vector2i MovesPosition;
	int totalHealth;
	int remainingHealth;
	int totalMoves;
	int remainingMoves;
	Tile health[3];
	Tile moves[7];
};

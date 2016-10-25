#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>
enum Direction {up, down, left, right};

class Queue
{
private:
	struct Node {
		Tile img;
		Node* next;
	};

	Node* first;
	int queueSize;

	bool checkAutokillAux(sf::Vector2f headPos, Node* node);
public:
	Queue();

	// Operacoes de fila
	void push(int direction);
	void pushAux(Node* node, int direction);
	void pop();
	bool empty();
	int size();

	// Operacoes para o jogo
	bool checkFood(sf::Vector2f foodPos);
	bool checkAutokill();
	bool checkCollision();
	void update(float gameTime, int direction);
	void recursiveUpdate(Node* node, sf::Vector2f lastPos);
	void draw(sf::RenderTarget & target);
	sf::Vector2f getHeadPosition();

};

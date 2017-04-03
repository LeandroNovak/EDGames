#include "Queue.h"
#include <iostream>

Queue::Queue()
{
	first =	nullptr;
	queueSize = 0;
}

void Queue::push(int direction)
{
	if (first == nullptr) {
		first = new Node;
		first->img.load("bd", 375, 275);
		first->next = nullptr;
	}
	else {
		pushAux(first, direction);
	}
}

void Queue::pushAux(Node* node, int direction)
{
	if (node->next == nullptr) {
		Node* tnode = new Node;
		
		if (direction == Direction::up) {
			tnode->img.load("bd", node->img.getPosition().x, node->img.getPosition().y - 25);
		}
		else if (direction == Direction::down) {
			tnode->img.load("bd", node->img.getPosition().x, node->img.getPosition().y + 25);
		}
		else if (direction == Direction::left) {
			tnode->img.load("bd", node->img.getPosition().x - 25, node->img.getPosition().y);
		}
		else if (direction == Direction::right) {
			tnode->img.load("bd", node->img.getPosition().x + 25, node->img.getPosition().y);
		}

		tnode->next = nullptr;
		node->next = tnode;
		queueSize++;
	}
	else {
		pushAux(node->next, direction);
	}
}

void Queue::pop()
{
	if (first != nullptr) {
		if (first->next != nullptr) {
			Node* tempPtr = first->next;
			delete first;
			first = tempPtr;
		}
		else {
			delete first;
		}
		queueSize--;
	}
}

bool Queue::empty()
{
	return first == NULL;
}

int Queue::size()
{
	return queueSize;
}

bool Queue::checkFood(sf::Vector2f foodPos)
{
	if (first->img.getPosition().x == foodPos.x && first->img.getPosition().y == foodPos.y)
		return true;
	else
		return false;
}

bool Queue::checkAutokill()
{
	Node* aux;
	aux = first;
	sf::Vector2f posHead = first->img.getPosition();

	if (aux->next != nullptr)
		aux = aux->next;
		
	while (aux->next != nullptr)
	{
		if (aux->img.getPosition() == posHead)
			return true;
		else
			aux = aux->next;
	}
	return false;
}

bool Queue::checkAutokillAux(sf::Vector2f headPos, Node* node)
{
	if (headPos == node->img.getPosition())
		return true;
	else if (node->next != nullptr)
		return checkAutokillAux(headPos, node->next);
	else 
		return false;
}

bool Queue::checkCollision()
{
	if (first->img.getPosition().x < 25.f || first->img.getPosition().y < 25.f ||
		first->img.getPosition().x > 750.f || first->img.getPosition().y > 550.f)
		return true;
	else
		return false;
}

void Queue::update(float gameTime, int direction)
{
	if (!empty()) {
		sf::Vector2f tempPos = first->img.getPosition();
		if (direction == Direction::up) {
			first->img.setPosition(first->img.getPosition().x, first->img.getPosition().y - 25);
		}
		else if (direction == Direction::down) {
			first->img.setPosition(first->img.getPosition().x, first->img.getPosition().y + 25);
		}
		else if (direction == Direction::left) {
			first->img.setPosition(first->img.getPosition().x - 25, first->img.getPosition().y);
		}
		else if (direction == Direction::right) {
			first->img.setPosition(first->img.getPosition().x + 25, first->img.getPosition().y);
		}
		if (first->next != nullptr) {
			recursiveUpdate(first->next, tempPos);
		}
	}
}

void Queue::recursiveUpdate(Node * node, sf::Vector2f lastPos)
{
	sf::Vector2f tempPos2 = node->img.getPosition();
	node->img.setPosition(lastPos);
	if (node->next != nullptr) {
		recursiveUpdate(node->next, tempPos2);
	}
}

void Queue::draw(sf::RenderTarget & target)
{
	if (!empty()) {
		Node* aux = first;
		aux->img.draw(target);
		while (aux->next != nullptr)
		{
			aux = aux->next;
			aux->img.draw(target);
		}
		aux->img.draw(target);
	}
}

sf::Vector2f Queue::getHeadPosition()
{
	return first->img.getPosition();
}

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile();

	void load(std::string filename, int x, int y);			// Carrega imagem em arquivo e atribui posição da imagem
	void load(std::string filename, int x, int y, int id);	// Carrega imagem em arquivo e atribui posição da imagem
	void draw(sf::RenderTarget &, sf::RenderStates);		// Desenha imagem na janela
	void draw(sf::RenderTarget &);
	void changeLocation(std::string);						// Altera a pasta padrão de sprites
	void setPosition(float, float);							// Atribui ao sprite uma posição definida pelo usuário
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();								// Retorna a posição do _sprite
	sf::Vector2f getSize();
	int getId();
	void operator=(Tile);

private:
	std::string defaultLocation;
	std::string defaultSufix;
	std::string _filename;
	sf::Texture _texture;
	sf::Sprite _sprite;
	int _id;
};

#endif // !TILE_H
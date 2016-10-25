#include "Tile.h"

// Construtor
Tile::Tile()
{
	defaultLocation = "Content/";
	defaultSufix = ".png";
	_id = -1;
}

// Carrega a imagem .png a partir do seu nome e insere na posição x,y
void Tile::load(std::string filename, int x, int y)
{
	_texture.loadFromFile(defaultLocation + filename + defaultSufix);
	_sprite.setTexture(_texture);
	_sprite.setPosition(x, y);
	_filename = filename;
	_id = -1;
}

// Carrega a imagem .png a partir do seu nome, insere na posição x,y e atribui uma id a imagem
void Tile::load(std::string filename, int x, int y, int id)
{
	_texture.loadFromFile(defaultLocation + filename + defaultSufix);
	_sprite.setTexture(_texture);
	_sprite.setPosition(x, y);
	_id = id;
	_filename = filename;
}

void Tile::commonLoad(std::string filename, int x, int y)
{
	_texture.loadFromFile(filename);
	_sprite.setTexture(_texture);
	_sprite.setPosition(x, y);
}

// Exibe a imagem na janena
void Tile::draw(sf::RenderTarget & window, sf::RenderStates states)
{
	window.draw(_sprite);
}

void Tile::draw(sf::RenderTarget & window)
{
	window.draw(_sprite);
}

// Altera a localizacao padrao das imagens
void Tile::changeLocation(std::string newLocation)
{
	defaultLocation = newLocation;
}

void Tile::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

void Tile::setPosition(sf::Vector2f newPosition)
{
	_sprite.setPosition(newPosition);
}

sf::Vector2f Tile::getPosition()
{
	return _sprite.getPosition();
}

sf::Vector2f Tile::getSize()
{
	return (sf::Vector2f)_texture.getSize();
}

int Tile::getId()
{
	return _id;
}

void Tile::operator=(Tile _tile)
{
	this->load(_tile._filename, _tile.getPosition().x, _tile.getPosition().y, _tile._id);
}

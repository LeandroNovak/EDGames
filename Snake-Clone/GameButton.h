#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

static int buttonID = 0;

class GameButton
{
public:
	GameButton();
	
	sf::Vector2f getSpritePosition();
	sf::Vector2u getSpriteSize();
	void setSpritePosition(unsigned int x, unsigned int y);
	void setTextAttributes(std::string fontName, std::string text, sf::Color color, int size, sf::Text::Style style, int x, int y);
	void load(std::string filenamePressed, std::string filenameReleased, int x , int y);
	void commonLoad(std::string filenamePressed, std::string filenameReleased, int x , int y);
	sf::Vector2i getPosition();
	sf::Vector2i getSize();
	void setState(bool);
	bool getState();
	void setFocus(bool);
	void draw(sf::RenderTarget&, sf::RenderStates);
	void draw(sf::RenderTarget&);

private:
	bool buttonState;

	sf::Texture buttonNotPressedTexture;
	sf::Texture buttonPressedTexture;
	sf::Sprite buttonSprite;

	sf::Font buttonFont;
	std::string buttonTextString;
	sf::Text buttonText;

	std::string defaultLocation;
	std::string defaultSufix;

};


#include "GameButton.hpp"

GameButton::GameButton()
{
	buttonID++;
	defaultLocation = "Content/";
	defaultSufix = ".png";
	buttonState = false;
}

sf::Vector2f GameButton::getSpritePosition()
{
	return buttonSprite.getPosition();
}

sf::Vector2u GameButton::getSpriteSize()
{
	return buttonNotPressedTexture.getSize();
}

void GameButton::setSpritePosition(unsigned int x, unsigned int y)
{
	buttonSprite.setPosition(x, y);
}

void GameButton::setTextAttributes(std::string fontName, std::string text, sf::Color color, int size, sf::Text::Style style, int x, int y)
{
	buttonFont.loadFromFile("Content/" + fontName);
	buttonTextString = text;

	buttonText.setFont(buttonFont);
	buttonText.setString(buttonTextString);
	buttonText.setColor(color);
	buttonText.setCharacterSize(size);
	buttonText.setStyle(style);
	buttonText.setPosition(x, y);
}

void GameButton::load(std::string filenamePressed, std::string filenameReleased, int x , int y)
{
	buttonNotPressedTexture.loadFromFile(defaultLocation + filenameReleased + defaultSufix);
	buttonPressedTexture.loadFromFile(defaultLocation + filenamePressed + defaultSufix);
	buttonSprite.setTexture(buttonNotPressedTexture);
	buttonSprite.setOrigin(buttonNotPressedTexture.getSize().x / 2, buttonNotPressedTexture.getSize().y / 2);
	buttonSprite.setPosition(x, y);
}

sf::Vector2i GameButton::getPosition()
{
	return (sf::Vector2i) buttonSprite.getPosition();
}

sf::Vector2i GameButton::getSize()
{
	return (sf::Vector2i) buttonNotPressedTexture.getSize();
}

void GameButton::setState(bool newState)
{
	buttonState = newState;
}

bool GameButton::getState()
{
	return buttonState;
}

void GameButton::setFocus(bool focus)
{
	if (focus)
		buttonSprite.setTexture(buttonPressedTexture);
	else
		buttonSprite.setTexture(buttonNotPressedTexture);
}

void GameButton::draw(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(buttonSprite);
	//target.draw(buttonText);
}

void GameButton::draw(sf::RenderTarget & target)
{
	target.draw(buttonSprite);
	target.draw(buttonText);
}



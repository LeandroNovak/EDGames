/*****************************************
 * Game.cpp
 * Classe Game, possui o gameLoop do jogo
******************************************/
#include "Game.h"

// Construtor da classe Game
// Recebe por parâmetro sf::VideoMode com largura e altura da janela de jogo,
// uma string contendo o nome da janela e sf::Style o estilo da janela.

Game::Game() : mainWindow(sf::VideoMode(800, 600), "EDGame", sf::Style::Close)
{
	mainWindow.setFramerateLimit(5);						// Força a taxa de frames limite do jogo
	mainWindow.setVerticalSyncEnabled(false);				// Desativa a sincronização Vertical
	
	currentState = State::menu;
	currentDirection = Direction::right;
	currentButton = 0;
	
	background.load("bg", 0, 0);

	newGameButton.load("ngs", "ngu", 400, 360);
	newGameButton.setFocus(true);

	exitButton.load("exs", "exu", 400, 520);

	snake.push(currentDirection);

	food.load("fd", (rand() % 25) * 25, (rand() % 25) * 25);
}

// Loop principal do jogo
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time gameTime = sf::seconds(1.f / 5.f);

	while (mainWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		
		if (timeSinceLastUpdate > gameTime)
		{
			timeSinceLastUpdate -= gameTime;
			eventHandler();
			update(gameTime.asSeconds());
		}
		draw();
	}
}

// Gerenciador de eventos
void Game::eventHandler()
{
	sf::Event event;
	sf::Mouse mouse;
	
	while (mainWindow.pollEvent(event))
	{
		// Eventos verificados no menu do jogo
		if (currentState == State::menu)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mainWindow.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
				{
					mainWindow.close();
					break;
				}
				if (event.key.code == sf::Keyboard::Key::Up)
				{
					newGameButton.setFocus(true);
					exitButton.setFocus(false);
					currentButton = 0;
					break;
				}
				if (event.key.code == sf::Keyboard::Key::Down)
				{
					newGameButton.setFocus(false);
					exitButton.setFocus(true);
					currentButton = 1;
					break;
				}
				if (event.key.code == sf::Keyboard::Key::End || event.key.code == sf::Keyboard::Key::Space)
				{
					if (currentButton == 0)
					{
						currentState = State::playing;
						break;
					}
					if (currentButton == 1)
					{
						mainWindow.close();
						break;
					}				
				}
			}
		}
		
		// Eventos verificados durante a fase
		if (currentState == State::playing)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mainWindow.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
				{
					mainWindow.close();
					break;
				}
				else if (event.key.code == sf::Keyboard::Key::Up && currentDirection != down)
				{
					currentDirection = Direction::up;
					break;
				}
				else if (event.key.code == sf::Keyboard::Key::Down && currentDirection != up)
				{
					currentDirection = Direction::down;
					break;
				}
				else if (event.key.code == sf::Keyboard::Key::Left && currentDirection != right)
				{
					currentDirection = Direction::left;
					break;
				}
				else if (event.key.code == sf::Keyboard::Key::Right && currentDirection != left)
				{
					currentDirection = Direction::right;
					break;
				}
				break;
			}
		}
	}
}

// Atualiza conteúdo do jogo
void Game::update(float timeAsSeconds)
{
	sf::Mouse mouse;
	// Atualização no menu
	if (currentState == State::menu)
	{
		// Verifica se o botão foi pressionado e altera o estado do jogo para jogando se necessario
		//if (newGameButton.getState() == true)
		//{
		//	currentState = State::playing;
		//}
	}
	if (currentState == State::playing)
	{
		snake.update(timeAsSeconds, currentDirection);
		if (snake.checkFood(food.getPosition()))
		{
			food.load("fd", (rand() % 31) * 25, (rand() % 24) * 25);
			snake.push(currentDirection);
		}
	}
}

// Exibe conteúdo na janela do jogo
void Game::draw()
{
	// Conteúdo a ser desenhado durante o menu
	mainWindow.clear(sf::Color::White);

	if (currentState == State::menu)
	{
		background.draw(mainWindow);
		newGameButton.draw(mainWindow);
		exitButton.draw(mainWindow);
	}

	// Conteúdo a ser desenhado durante a fase
	if (currentState == State::playing)
	{
		background.draw(mainWindow);
		snake.draw(mainWindow);
		food.draw(mainWindow);
	}
	mainWindow.display();
}

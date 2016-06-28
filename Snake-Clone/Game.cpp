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
	score = 0;
	
	background.load("bg", 0, 0);
	edges.load("eds", 0, 0);

	title.load("tt", 0, 20);
	
	newGameButton.load("ngs", "ngu", 400, 360);
	newGameButton.setFocus(true);

	exitButton.load("exs", "exu", 400, 520);
	gameOverScreen.load("go", 0, 0);

	snake.push(currentDirection);

	food.load("fd", ((rand() % 31) + 1) * 25, (100 + ((rand() % 17) + 1) * 25));
	font.loadFromFile("Content/fnt.ttf");
	textScore.setFont(font);
	textScore.setPosition(30, 20);
	textScore.setCharacterSize(30);
	textScore.setColor(sf::Color(20,25,0, 255));
	textScore.setString("Score: 0");

	soundBuffer.loadFromFile("Content/brl.ogg");
	sound.setBuffer(soundBuffer);
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
	
		if (currentState == State::lose)
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
				else if (event.key.code == sf::Keyboard::Key::Space)
				{
					mainWindow.close();
					break;
				}
			}
		}
	}
}

// Atualiza conteúdo do jogo
void Game::update(float timeAsSeconds)
{
	sf::Mouse mouse;

	if (currentState == State::playing)
	{
		snake.update(timeAsSeconds, currentDirection);
		if (snake.checkFood(food.getPosition()))
		{
			food.load("fd", (rand() % 31) * 25, (rand() % 24) * 25);
			score++;
			std::string temp = std::to_string(score);
			textScore.setString("Score: " + (sf::String)temp);
			snake.push(currentDirection);
		}
		if (snake.checkAutokill())
		{
			textScore.setPosition(800/2 - 150, 600/2 + 50);
			textScore.setString("(press space to exit)");
			currentState = State::lose;
		}
		if (snake.checkCollision())
		{
			textScore.setPosition(800/2 - 150, 600/2 + 50);
			textScore.setString("(press space to exit)");
			currentState = State::lose;
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
		title.draw(mainWindow);
		newGameButton.draw(mainWindow);
		exitButton.draw(mainWindow);
	}

	// Conteúdo a ser desenhado durante a fase
	if (currentState == State::playing)
	{
		background.draw(mainWindow);
		edges.draw(mainWindow);
		snake.draw(mainWindow);
		mainWindow.draw(textScore);
		food.draw(mainWindow);
		sound.play();
	}

	if (currentState == State::lose)
	{
		background.draw(mainWindow);
		gameOverScreen.draw(mainWindow);
		mainWindow.draw(textScore);
	}
	mainWindow.display();
}
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
	mainWindow.setFramerateLimit(30);						// Força a taxa de frames limite do jogo
	mainWindow.setVerticalSyncEnabled(false);				// Desativa a sincronização Vertical
	
	currentState = State::menu;					
	currentStack = GameStacks::none;
	nextStack = GameStacks::none;

	// Carrega o Layout
	tLayout.loadFromFile("Content/layout.png");
	sLayout.setTexture(tLayout);				
	sLayout.setPosition(sf::Vector2f(0.f, 0.f));

	// Carrega o background e o monstro
	background.load("bg2", 0, 0);
	bahamut.load("bahamut3", 260, 200);

	//Carrega o botão de play presente no menu
	playButton.load("buttonP", "buttonR", mainWindow.getSize().x / 2, mainWindow.getSize().y - 100);
	playButton.setTextAttributes("Unique.ttf", "Jogar", sf::Color::White, 42, sf::Text::Style::Regular, 
		playButton.getSpritePosition().x - 50, 
		playButton.getSpritePosition().y - 35);

	// Carrega a fonte a ser usada no jogo
	font.loadFromFile("Content/Unique.ttf");

	// Inicializa as pilhas e carrega as imagens das bordas e o texto delas
	stack1 = new StaticStack <Tile>(3);
	Tile block1;
	block1.load("block1", 26, 319, 3);
	stack1->push(block1);

	Tile block2;
	block2.load("block2", 283, 319, 2);
	stack1->push(block2);

	Tile block3;
	block3.load("block3", 540, 319, 1);
	stack1->push(block3);

	stack1Edge.load("redEdge", 17, 311);
	labelStack1.setFont(font);
	labelStack1.setString("Pilha do Jogador");
	labelStack1.setColor(sf::Color::White);
	labelStack1.setCharacterSize(26);
	labelStack1.setStyle(sf::Text::Style::Regular);
	labelStack1.setPosition(stack1Edge.getPosition().x + 35, stack1Edge.getPosition().y + 245);

	stack2 = new StaticStack <Tile>(3);
	stack2Edge.load("redEdge", 274, 311);
	labelStack2.setFont(font);
	labelStack2.setString("Pilha Intermediaria");
	labelStack2.setColor(sf::Color::White);
	labelStack2.setCharacterSize(26);
	labelStack2.setStyle(sf::Text::Style::Regular);
	labelStack2.setPosition(stack2Edge.getPosition().x + 15, stack2Edge.getPosition().y + 245);

	stack3 = new StaticStack <Tile>(3);
	stack3Edge.load("redEdge", 531, 311);
	labelStack3.setFont(font);
	labelStack3.setString("Pilha Final");
	labelStack3.setColor(sf::Color::White);
	labelStack3.setCharacterSize(26);
	labelStack3.setStyle(sf::Text::Style::Regular);
	labelStack3.setPosition(stack3Edge.getPosition().x + 65, stack3Edge.getPosition().y + 245);

	monsterStack.load("finalStack", 559, 78);
	labelMonsterStack.setFont(font);
	labelMonsterStack.setString("Pilha do Monstro");
	labelMonsterStack.setColor(sf::Color::White);
	labelMonsterStack.setCharacterSize(26);
	labelMonsterStack.setStyle(sf::Text::Style::Regular);
	labelMonsterStack.setPosition(monsterStack.getPosition().x + 5, monsterStack.getPosition().y + 195);

	// Atributos do jogador
	totalHealth = 3;
	remainingHealth = 3;
	totalMoves = 7;
	remainingMoves = 7;

	healthAndMoves.load("playerinfos", 14, 8);

	HealthPosition = sf::Vector2i(22, 18);
	MovesPosition = sf::Vector2i(22, 74);
	health[2].load("health1", 22, 18);
	health[1].load("health2", 92, 18);
	health[0].load("health3", 162, 18);

	for (int i = 0; i < 7; i++) 
		moves[i].load("move", 202 - (i * 30), 74);
}

// Loop principal do jogo
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time gameTime = sf::seconds(1.f / 30.f);

	while (mainWindow.isOpen())
	{
		eventHandler();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > gameTime) 
		{
			timeSinceLastUpdate -= gameTime;
			eventHandler();
		}

		update(gameTime.asSeconds());
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
		if (currentState == State::menu) {
			switch (event.type)
			{
			case sf::Event::Closed:
				mainWindow.close();
				break;

			// Verifica se o botão "jogar" foi pressionado ou se a tecla espaco foi pressionada
			case sf::Event::MouseButtonPressed:
				if (mouse.getPosition(mainWindow).x > playButton.getPosition().x - playButton.getSize().x / 2 &&
					mouse.getPosition(mainWindow).x < playButton.getPosition().x + playButton.getSize().x / 2 &&
					mouse.getPosition(mainWindow).y > playButton.getPosition().y - playButton.getSize().y / 2 &&
					mouse.getPosition(mainWindow).y < playButton.getPosition().y + playButton.getSize().y / 2) 
				{
					if (event.key.code == sf::Mouse::Left) 
						playButton.setState(true);
				}
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Space) 
					playButton.setState(true);
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
				// Seleciona a pilha de origem
				if (event.key.code == sf::Keyboard::Key::Q) 
					currentStack = GameStacks::stack1;

				else if (event.key.code == sf::Keyboard::Key::W) 
					currentStack = GameStacks::stack2;

				else if (event.key.code == sf::Keyboard::Key::E)
					currentStack = GameStacks::stack3;

				// Seleciona a pilha de destino
				else if (event.key.code == sf::Keyboard::Key::Num1)
					nextStack = GameStacks::stack1;

				else if (event.key.code == sf::Keyboard::Key::Num2)
					nextStack = GameStacks::stack2;

				else if (event.key.code == sf::Keyboard::Key::Num3)
					nextStack = GameStacks::stack3;
			}

			std::cout << "Current Stack: " << currentStack << std::endl;
			std::cout << "Next Stack: " << nextStack << std::endl << std::endl;
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
		if (playButton.getState() == true) 
		{
			currentState = State::playing;
			bahamut.load("bahamut3", 260, 18);
		}

		// Verifica se o mouse esta sobre o botão
		if (mouse.getPosition(mainWindow).x > playButton.getPosition().x - playButton.getSize().x / 2 &&
			mouse.getPosition(mainWindow).x < playButton.getPosition().x + playButton.getSize().x / 2 &&
			mouse.getPosition(mainWindow).y > playButton.getPosition().y - playButton.getSize().y / 2 &&
			mouse.getPosition(mainWindow).y < playButton.getPosition().y + playButton.getSize().y / 2) 
			playButton.setFocus(true);
		else 
			playButton.setFocus(false);
	}

	// Atualização durante a fase
	if (currentState == State::playing) 
	{
		// Verifica as pilhas selecionadas e move de uma pilha para outra
		if (currentStack == GameStacks::stack1 && nextStack == GameStacks::stack1) 
		{
			// Impossível, volta para o estado inicial

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack1 && nextStack == GameStacks::stack2) 
		{
			if (!stack1->isEmpty() && !stack2->isFull()) 
			{
				if (stack2->isEmpty()) 
				{
					Tile aux = Tile(stack1->pop());
					stack2->push(aux);
					remainingMoves--;
				}
				else if (stack1->getTop().getId() > stack2->getTop().getId()) 
				{
					Tile aux = Tile(stack1->pop());
					stack2->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack1 && nextStack == GameStacks::stack3) 
		{
			if (!stack1->isEmpty() && !stack3->isFull()) 
			{
				if (stack3->isEmpty()) 
				{
					Tile aux = stack1->pop();
					stack3->push(aux);
					remainingMoves--;
				}
				else if (stack1->getTop().getId() > stack3->getTop().getId()) 
				{
					Tile aux = Tile(stack1->pop());
					stack2->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack2 && nextStack == GameStacks::stack1) 
		{
			if (!stack2->isEmpty() && !stack1->isFull()) 
			{
				if (stack1->isEmpty()) 
				{
					Tile aux = stack2->pop();
					stack1->push(aux);
					remainingMoves--;
				}
				if (stack2->getTop().getId() > stack1->getTop().getId()) 
				{
					Tile aux = stack2->pop();
					stack1->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack2 && nextStack == GameStacks::stack2) 
		{
			// Impossível, volta para o estado inicial
			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack2 && nextStack == GameStacks::stack3) 
		{
			if (!stack2->isEmpty() && !stack3->isFull()) 
			{
				if (stack3->isEmpty()) 
				{
					Tile aux = stack2->pop();
					stack3->push(aux);
					remainingMoves--;
				}
				if (stack2->getTop().getId() > stack3->getTop().getId()) 
				{
					Tile aux = stack2->pop();
					stack3->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack3 && nextStack == GameStacks::stack1) 
		{
			if (!stack3->isEmpty() && !stack1->isFull()) 
			{
				if (stack1->isEmpty()) 
				{
					Tile aux = stack3->pop();
					stack1->push(aux);
					remainingMoves--;
				}
				if (stack3->getTop().getId() > stack1->getTop().getId()) 
				{
					Tile aux = stack3->pop();
					stack1->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack3 && nextStack == GameStacks::stack2) 
		{
			if (!stack3->isEmpty() && !stack2->isFull()) {
				if (stack2->isEmpty()) 
				{
					Tile aux = stack3->pop();
					stack2->push(aux);
					remainingMoves--;
				}
				if (stack3->getTop().getId() > stack2->getTop().getId()) 
				{
					Tile aux = stack3->pop();
					stack2->push(aux);
					remainingMoves--;
				}
			}

			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}

		if (currentStack == GameStacks::stack3 && nextStack == GameStacks::stack3) 
		{
			// Impossível, volta para o estado inicial
			currentStack = GameStacks::none;
			nextStack = GameStacks::none;
		}
	}
	if (remainingMoves == 0) 
	{
		remainingHealth--;
		remainingMoves = 7;
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
		playButton.draw(mainWindow);
		bahamut.draw(mainWindow);
	}

	// Conteúdo a ser desenhado durante a fase
	if (currentState == State::playing) 
	{
		background.draw(mainWindow);
		bahamut.draw(mainWindow);
		monsterStack.draw(mainWindow);
		stack1Edge.draw(mainWindow);
		stack2Edge.draw(mainWindow);
		stack3Edge.draw(mainWindow);
		mainWindow.draw(labelMonsterStack);
		mainWindow.draw(labelStack1);
		mainWindow.draw(labelStack2);
		mainWindow.draw(labelStack3);
		healthAndMoves.draw(mainWindow);
		//mainWindow.draw(sLayout);

		for (int i = 0; i < remainingHealth; i++) 
			health[i].draw(mainWindow);

		for (int i = 0; i < remainingMoves; i++) 
			moves[i].draw(mainWindow);

		// Atribui a posição de cada tile na pilha
		// Pilha 1
		if (!stack1->isEmpty()) 
		{
			int sSize = 0;
			StaticStack <Tile> pAux(3);
			while (!stack1->isEmpty()) 
			{
				stack1->getTop().draw(mainWindow);
				Tile tAux = stack1->pop();
				pAux.push(tAux);
				sSize++;
			}

			for (int i = sSize - 1; i >= 0; i--) 
			{
				Tile tAux = pAux.pop();
				//tAux.setPosition(26, 553 - (77 * (i + 1)));
				tAux.setPosition(26, 318 + (77 * i));
				//tAux.setPosition(26, 554 - (77 * i));

				tAux.draw(mainWindow);
				stack1->push(tAux);
			}
		}

		if (!stack2->isEmpty()) {
			int sSize = 0;
			StaticStack <Tile> pAux(3);
			while (!stack2->isEmpty()) 
			{
				stack2->getTop().draw(mainWindow);
				Tile tAux = stack2->pop();
				pAux.push(tAux);
				sSize++;
			}

			for (int i = sSize - 1; i >= 0; i--) 
			{
				Tile tAux = pAux.pop();
				//tAux.setPosition(283, 553 - (77 * (i + 1)));
				tAux.setPosition(283, 318 + (77 * i));
				//tAux.setPosition(283, 554 - (77 * i));

				tAux.draw(mainWindow);
				stack2->push(tAux);
			}
		}

		if (!stack3->isEmpty()) 
		{
			int sSize = 0;
			StaticStack <Tile> pAux(3);

			while (!stack3->isEmpty()) 
			{
				stack3->getTop().draw(mainWindow);
				Tile tAux = stack3->pop();
				pAux.push(tAux);
				sSize++;
			}
			
			int posy = 319;

			for (int i = sSize - 1; i >= 0; i--) 
			{
				Tile tAux = pAux.pop();
				//tAux.setPosition(540, 553 - (77 * (i + 1)));
				//tAux.setPosition(540, 554 - (77 * i));
				tAux.setPosition(540, 318 + (77 * i));
				tAux.draw(mainWindow);
				stack3->push(tAux);
			}
		}
	}
	mainWindow.display();
}

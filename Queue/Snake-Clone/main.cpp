/******************************************
 * Função main do jogo, cria um objeto do 
 * tipo Game e chama o loop principal.
*******************************************/

#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	game.run();

	return 0;
}

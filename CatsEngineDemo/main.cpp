#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

int main(int argc, char ** argv)
{
	Game game;
	if (!game.Init()) return -1;

	game.Run();

	return 0;
}
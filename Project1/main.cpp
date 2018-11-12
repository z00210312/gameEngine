#include "gameWindow.h"
#include "time.h"
//#include <Windows.h>

int main() {
	//FreeConsole();
	srand((unsigned int)time(NULL));
	int width = 1200;
	int height = 800;
	gameWindow newGameWindow("hello world!", width, height);
	newGameWindow.gameLoop();
	//::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	return 0;
}
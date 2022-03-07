#include <Windows.h>
#include "Games.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Games theGame;
		if (theGame.Init("Game Of Life", 265, 265))
		{
			
			theGame.start();
			return 0;
		}

	return 1;
}
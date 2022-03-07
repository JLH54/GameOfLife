#include "Games.h"
#include <Windows.h>
#include <time.h>
#include <SDL.h>
#define BRICKS 91
#define NOMBRE_BRICK 13
bool Games::CreateGameWindow(const std::string& title, int width, int height)
{
	m_Window = SDL_CreateWindow(
		"Game of life",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_UTILITY);

	if (m_Window == nullptr)
	{
		SDL_Log("Error : %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool Games::CreateRenderer()
{
	m_Graphics = SDL_CreateRenderer(
		m_Window,
		0,
		SDL_RENDERER_ACCELERATED
	);

	if (m_Graphics == nullptr)
	{
		SDL_Log("Error : %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void Games::Close()
{
	SDL_DestroyRenderer(m_Graphics);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Games::Load()
{
	m_cellWidth = 50;
	m_cellHeight = 50;
	CreateGrid(5, 5);
}

void Games::ProcessInput()
{
	SDL_Event events;
	SDL_PollEvent(&events);
	switch (events.type)
	{
	case SDL_QUIT:
		m_Running = false;
		break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		key = SDL_GetKeyboardState(nullptr);
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (events.button.button)
		{
		case SDL_BUTTON_LEFT:
			m_MouseState[0] = true;
			break;
		case SDL_BUTTON_MIDDLE:
			m_MouseState[1] = true;
			break;
		case SDL_BUTTON_RIGHT:
			m_MouseState[2] = true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch (events.button.button)
		{
		case SDL_BUTTON_LEFT:
			m_MouseState[0] = false;
			break;
		case SDL_BUTTON_MIDDLE:
			m_MouseState[1] = false;
			break;
		case SDL_BUTTON_RIGHT:
			m_MouseState[2] = false;
			break;
		}
		break;

	case SDL_MOUSEMOTION:
		m_MouseX = events.motion.x;
		m_MouseY = events.motion.y;
		break;
	}
}

void Games::UpdateLogic()
{
	//Game Logic
	//pour avoir la position de la cellule, il faudra faire un calcul pour savoir il est ou
	//donc pour avoir son x il faudra faire le max dans les x et diviser par le width(qui est 50)
	//pour les y il faudra diviser par sa taille aussi
	//NE PAS OUBLIER LES OFFSETS
	if (m_MouseState[0])
	{
		if (!m_IsClicked)
		{
			SDL_Log("Click gauche");
			m_IsClicked = true;
		}
		else
		{
			m_IsClicked = false;
		}
		
	}
}

void Games::RenderFrame()
{
	//Draw
	DrawGrid();

	SDL_SetRenderDrawColor(m_Graphics, 0, 255, 0, 255);
	SDL_Rect rect = { m_MouseX, m_MouseY, 10, 10 };
	SDL_RenderFillRect(m_Graphics, &rect);
}

void Games::CreateGrid(int w, int h)
{
	m_gridWidth = w;
	m_gridHeight = h;
	m_Grid.resize(w * h);

}

void Games::DrawGrid()
{
	int offset = 3;
	int offsetx = 2;
	SDL_SetRenderDrawColor(m_Graphics, 255, 255, 255, 255);
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		int x = (i % m_gridWidth)* (50 + offset) + offsetx;
		int y = (i / m_gridWidth) * (50 + offset);
		SDL_Rect rect = { x, y, m_cellWidth, m_cellHeight };
		if (m_Grid[i] == 0)
		{
			SDL_RenderDrawRect(m_Graphics, &rect);
		}
		else
		{
			SDL_RenderFillRect(m_Graphics, &rect);
		}
		
	}
}

bool Games::Init(const std::string& title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Error : %s\n", SDL_GetError());
		return true;
	}

	if (CreateGameWindow(title, width, height))
	{
		if (CreateRenderer())
		{
			m_Running = true;
			return true;
		}
	}
	return false;
}

void Games::start()
{
	Load();
	const unsigned int FPS = 60;
	const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

	while (m_Running)
	{
		const clock_t start = clock();
		ProcessInput();
		UpdateLogic();


		SDL_SetRenderDrawColor(m_Graphics, 145, 145, 145, 255);
		SDL_RenderClear(m_Graphics);

		RenderFrame();
		SDL_RenderPresent(m_Graphics);
		int restTime = start + FRAME_TARGET_TIME - clock();
		if (restTime > 0)
		{
			Sleep(restTime);
		}
	}

	Close();
}

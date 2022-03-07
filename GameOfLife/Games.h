#pragma once
#include <string>
#include <vector>
struct SDL_Window;
struct SDL_Renderer;

class Games
{
private:
	bool CreateGameWindow(const std::string& title, int width, int height);
	bool CreateRenderer();
	void Close();

	void Load();
	void ProcessInput();
	void UpdateLogic();
	void RenderFrame();

	void CreateGrid(int w, int h);
	void DrawGrid();

	SDL_Window* m_Window;
	SDL_Renderer* m_Graphics;

	bool m_Running = false;
	const unsigned char* key = nullptr;

	std::vector<int> m_Grid;
	int m_gridWidth;
	int m_gridHeight;
	int m_cellWidth;
	int m_cellHeight;
						//	Bouton gauche Bouton milieu Bouton droit
	bool m_MouseState[3] = { false, false, false };
	int m_MouseX = 0;
	int m_MouseY = 0;

	bool m_IsClicked = false;
public:
	bool Init(const std::string& title, int width, int height);
	void start();
};


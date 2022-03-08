#pragma once
#include <vector>
#include <SDL.h>

class Grid
{
private:
	void CreateGrid(int w, int h);
	void survival(int idx);
	std::vector<int> m_Grid;
	int m_gridWidth;
	int m_gridHeight;
	int m_cellWidth;
	int m_cellHeight;
	int idx;
	

public:
	void InitGrid(int w, int h);
	void GridUpdate(int mouseX, int mouseY);
	void DrawGrid(SDL_Renderer* graphics, int mouseX, int mouseY);
	int GetCellWidth();
	int GetCellHeight();
};


#include "Grid.h"

void Grid::CreateGrid(int w, int h)
{
	m_gridWidth = w;
	m_gridHeight = h;
	m_cellWidth = w;
	m_cellHeight = h;
	m_Grid.resize(w * h);
}

void Grid::survival(int idx)
{
	if (m_Grid[idx] == 0)
	{
		for (int i = 0; i < 8; i++)
		{

		}
	}
	else
	{

	}
}

void Grid::DrawGrid(SDL_Renderer* graphics, int mouseX, int mouseY)
{
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		int x = (i % m_gridWidth) * 50 ;
		int y = (i / m_gridWidth) * 50 ;
		SDL_Rect rect = { x, y, m_cellWidth, m_cellHeight };
		if (m_Grid[i] == 0)
		{
			
			SDL_SetRenderDrawColor(graphics, 255, 255, 255, 255);
			SDL_RenderDrawRect(graphics, &rect);
		}
		else if (m_Grid[i] == 1)
		{
			SDL_SetRenderDrawColor(graphics, 255, 234, 0, 255);
			SDL_RenderFillRect(graphics, &rect);
		}
	}
}

int Grid::GetCellWidth()
{
	return m_cellWidth;
}

int Grid::GetCellHeight()
{
	return m_cellHeight;
}

void Grid::InitGrid(int w, int h)
{
	m_gridHeight = h;
	m_gridWidth = w;
	CreateGrid(m_gridHeight, m_gridWidth);
}

void Grid::GridUpdate(int mouseX, int mouseY)
{
	int m_x = mouseX / m_cellHeight;
	int m_y = mouseY / m_cellWidth;
	int idx = m_y * m_gridHeight + m_x % m_gridWidth;
	if (m_Grid[idx] == 0)
	{
		m_Grid[idx] = 1;
	}
	else
	{
		m_Grid[idx] = 0;
	}
}


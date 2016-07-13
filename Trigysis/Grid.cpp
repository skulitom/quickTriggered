#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		std::vector<int> hold;
		hold.push_back(0);
		for(int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			this->net.push_back(hold);
		}
		hold.clear();
	}
}

Grid::~Grid()
{

}
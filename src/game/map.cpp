#include "map.hpp"

int minesNum;
int closedCellNum;

Cell map[MAP_WIDTH][MAP_HEIGHT];

bool IsCellInMap(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}


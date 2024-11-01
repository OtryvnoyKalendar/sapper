#pragma once

#include "cell.hpp"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

bool IsCellInMap(int x, int y);

extern Cell map[MAP_WIDTH][MAP_HEIGHT];
extern int minesNum;
extern int closedCellNum;


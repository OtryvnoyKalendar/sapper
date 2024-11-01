#include <ctime>
#include <cstdlib>
#include <cstring>

#include "game.hpp"
#include "map.hpp"

void NewGame() {
	srand(time(NULL));
	memset(map, 0, sizeof(map));

	game.failed = false;
	minesNum = 20;
	closedCellNum = MAP_WIDTH*MAP_HEIGHT;
	
	for(int i = 0; i < minesNum; i++) {
		int x = rand() % MAP_WIDTH;
		int y = rand() % MAP_HEIGHT;
		
		if(map[x][y].mine)
			i--;
		else {
			map[x][y].mine = true;

			for(int dx = -1; dx < 2; dx++)
				for(int dy = -1; dy < 2; dy++)
					if(IsCellInMap(x+dx, y+dy))
						map[x+dx][y+dy].mineAroundNum += 1;
		}
	}
}



// логика класса

//in file: render.cpp
//void Game::RenderGraphics();

void Game::UpdateGameLogic() {
	if(minesNum == closedCellNum)
		NewGame();
}

Game::Game() {
	NewGame();
}

Game::~Game() {

}


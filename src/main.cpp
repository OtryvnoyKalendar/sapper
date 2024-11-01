#include "window.hpp"
#include "game.hpp"
#include "map.hpp"

Game game;
// флаг главного цикла
bool quit = false;

void QuitMainLoop() {
	quit = true;
}

void OpenFields(int x, int y) {
	if(!IsCellInMap(x, y) || map[x][y].open)
		return;
	
	closedCellNum--;
	map[x][y].open = true;
	if(map[x][y].mineAroundNum == 0)
		for(int dx = -1; dx < 2; dx++)
			for(int dy = -1; dy < 2; dy++)
				OpenFields(x+dx, y+dy);
	if(map[x][y].mine) {
		game.failed = true;
		for(int i = 0; i < MAP_WIDTH; i++)
			for(int j = 0; j < MAP_WIDTH; j++)
				map[i][j].open = true;
	}
}

void MainLoop() {
	// обработчик событий
	SDL_Event e;
	// включить ввод текста
	SDL_StartTextInput();
	
	while(!quit) {
		// обработка событий в очереди
		while(SDL_PollEvent(&e) != 0) {
			// Запрос пользователя закрыть программу
			if(e.type == SDL_QUIT) {
				QuitMainLoop();
			}
			// введённый текст с текущим положением курсора
			/*else if(e.type == SDL_TEXTINPUT) {
				SDL_GetMouseState(&x, &y);
			}*/
			// нажатия мышкой
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x = (e.button.x / (float)SCREEN_WIDTH)*MAP_WIDTH;
				int y = MAP_HEIGHT-(e.button.y / (float)SCREEN_HEIGHT)*MAP_HEIGHT;
				if (e.button.button == SDL_BUTTON_LEFT) {
					if(game.failed) {
						NewGame();
					}
					else {
						if(IsCellInMap(x, y) && !map[x][y].flag)
							OpenFields(x, y);
					}
				}
				else if (e.button.button == SDL_BUTTON_RIGHT) {
					if(IsCellInMap(x, y))
						map[x][y].flag = !map[x][y].flag;
					//printf("Right mouse button clicked at (%d, %d)\n", e.button.x, e.button.y);
				}
			}
			// зажатая клавиша
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
					QuitMainLoop();
			}
		}

		// логика игры
		game.UpdateGameLogic();
		// рендерить графику
		game.RenderGraphics();

		// обновить экран
		SDL_GL_SwapWindow(gWindow);
	}
}

int main(int argc, char* args[]) {
	// запустить SDL и создать окно
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	}
	else {
		//главный цикл программы
		MainLoop();
		
		// отключить ввод текста
		SDL_StopTextInput();
	}

	// освободить ресурсы и закрыть SDL
	close();
	return 0;
}


#pragma once

class Game {
public:
	bool failed;
	
	void UpdateGameLogic();
	void RenderGraphics();
	Game();
	~Game();
};

void NewGame();

extern Game game;


#include "game.hpp"
#include "glcore.hpp"
#include "map.hpp"

void DrawLine(float x1, float y1, float x2, float y2) {
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
}

void ShowNum(int num) {
	glLineWidth(3);
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
		if(num != 1 && num != 4)
			DrawLine(0.3, 0.85, 0.7, 0.85);
		if(num != 0 && num != 1 && num != 7 && num != 7)
			DrawLine(0.3, 0.5, 0.7, 0.5);
		if(num != 1 && num != 4 && num != 7)
			DrawLine(0.3, 0.15, 0.7, 0.15);
		
		if(num != 5 && num != 6)
			DrawLine(0.7, 0.5, 0.7, 0.85);
		if(num != 2)
			DrawLine(0.7, 0.5, 0.7, 0.15);

		if(num != 1 && num != 2 && num != 3 && num != 7)
			DrawLine(0.3, 0.5, 0.3, 0.85);
		if(num == 0 || num == 2 || num == 6 || num == 8)
			DrawLine(0.3, 0.5, 0.3, 0.15);
	glEnd();
}

void ShowMine() {
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 0, 0);
		glVertex2f(0.3, 0.3);
		glVertex2f(0.7, 0.3);
		glVertex2f(0.7, 0.7);
		glVertex2f(0.3, 0.7);
	glEnd();
}

void ShowField() {
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.8, 0.8, 0.8); glVertex2f(0, 1);
		glColor3f(0.7, 0.7, 0.7); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.6, 0.6, 0.6); glVertex2f(1, 0);
	glEnd();
}

void ShowFieldOpen() {
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.3, 0.3, 0.3); glVertex2f(0, 1);
		glColor3f(0.3, 0.6, 0.3); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.3, 0.5, 0.3); glVertex2f(1, 0);
	glEnd();
}

void ShowFlag() {
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(0.25, 0.75);
		glVertex2f(0.85, 0.5);
		glVertex2f(0.25, 0.25);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex2f(0.25, 0.75);
		glVertex2f(0.25, 0.f);
	glEnd();
}

// логика класса

void Game::RenderGraphics() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glScalef(2.0 / MAP_WIDTH, 2.0 / MAP_HEIGHT, 1);
	glTranslatef(-MAP_WIDTH*0.5, -MAP_HEIGHT*0.5, 0);
	
	for(int i = 0; i < MAP_WIDTH; i++)
		for(int j = 0; j < MAP_HEIGHT; j++) {
			glPushMatrix();
			glTranslatef(i, j, 0);
				
			if(map[i][j].open) {
				ShowFieldOpen();
				if(map[i][j].mine)
					ShowMine();
				else if(map[i][j].mineAroundNum > 0)
					ShowNum(map[i][j].mineAroundNum);
			}
			else {
				ShowField();
				if(map[i][j].flag)
					ShowFlag();
			}

			glPopMatrix();
		}
}


#pragma once

#include <string>
#include <stdio.h>

#include "glcore.hpp"

// Запустить SDL, создать окно и инициализировать OpenGl
bool init();
// Инициализировать матрицы и очистить цвета
bool initGL();
// Обработчик ввода
void handleKeys( unsigned char key, int x, int y );
// рендер на экране
void render();
// освободить данные и выключить SDL
void close();

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow; // окно, в котором будем рендерить
extern SDL_GLContext gContext; // контекст OpenGL


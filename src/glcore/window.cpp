#include "window.hpp"
#include "main.hpp"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const char* windowName = "Сапёр";

// окно, в котором будем рендерить
SDL_Window* gWindow = NULL;
// контекст OpenGL
SDL_GLContext gContext;

bool init() {
	bool success = true;

	// инициализировать SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
		// использовать OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

		// создать окно
		gWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else {
			// создать контекст
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL ) {
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else {
				// использовать Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );

				// инициализировать OpenGL
				if( !initGL() ) {
					printf( "Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL() {
	bool success = true;
	GLenum error = GL_NO_ERROR;

	// инициализировать проекционную матрицу
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	// проверяет ошибки
	error = glGetError();
	if( error != GL_NO_ERROR ) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}

	// инициализировать матрицу Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// проверить ошибки
	error = glGetError();
	if( error != GL_NO_ERROR ) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	// инициализировать очистку цветов
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	// проверяет ошибки
	error = glGetError();
	if( error != GL_NO_ERROR ) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	return success;
}

void close() {
	// закрыть окно
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// отключить SDL подсистемы
	SDL_Quit();
}


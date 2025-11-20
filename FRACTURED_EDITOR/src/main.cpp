
#include <glad/glad.h>
#include <Window.h>
#include <SDL.h>

int main(int argc, char* argv[]) {
	
	bool running = true;

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)){
		printf("SDL Init is failed: %s\n", SDL_GetError());
		return -1;
	}

	if (!SDL_GL_LoadLibrary(NULL)) {
		printf("SDL Gl library load is failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);


	FRACTURED_WINDOW::Window window = FRACTURED_WINDOW::Window("Engine Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_OPENGL);

	if (!window.GetWindow()) {
		printf("Window can't be created.");
		return -1;
	}

	if (!window.setGLContext())
		return -1;

	SDL_GL_MakeCurrent(window.GetWindow().get(), window.GetGLContext());

	SDL_GL_SetSwapInterval(1);

	if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
		printf("Glad can't be loaded.\n");
		return -1;
	}

	glViewport(0, 0, window.GetWidth(), window.GetHeight());
	
	SDL_Event event{};

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE)
					running = false;
				break;
			default:
				break;

			}	

		}
		
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(window.GetWindow().get());
	}

	return 0;


}
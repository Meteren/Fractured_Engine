#include "Window.h"


namespace FRACTURED_WINDOW {

	Window::Window(std::string windowHeader, int windowWidth, int windowHeight, int originX, int originY, bool vsync, Uint32 flags) 
		: windowHeader{ windowHeader }, windowWidth{ windowWidth }, windowHeight{windowHeight}, originX{originX}, originY{originY}
	{

		createWindow(flags);

		if (vsync) {
			if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) {
				printf("Error while enabling vsync: %s\n", SDL_GetError());
			}
		}			
					
	}
	
	bool Window::setGLContext()
	{
		if (windowPtr) {
			sdlGLContext = SDL_GL_CreateContext(windowPtr.get());
			if (!sdlGLContext) {
				printf("Context can't be created: %s\n", SDL_GetError());
				return false;
			}
			else {
				printf("Context is created.\n");
			}

		}
		else {
			printf("Window null context can't be created.");
			return false;
		}

	}

	void Window::setWindowHeader(const std::string& windowHeader)
	{
		this->windowHeader = windowHeader;
		SDL_SetWindowTitle(windowPtr.get(),this->windowHeader.c_str());
	}

	void Window::createWindow(Uint32 flags)
	{
		windowPtr = Windowptr(SDL_CreateWindow(windowHeader.c_str(), windowWidth, windowHeight, flags));

		if (!windowPtr) {

			printf("Window creation is failed: %s\n", SDL_GetError());

		}
		else {
			printf("Window creation is succeeded.\n");
		}

	}

	Window::~Window()
	{
	}
}



#pragma once

#include <Utilities/SDL_Wrapper.h>
#include <string>
#include <stdio.h>

namespace FRACTURED_WINDOW{

	class Window
	{
	public:

		Window() : Window("Default", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED) {

		}

		Window(std::string windowHeader, int windowWidth, int windowHeight, int originX, int originY, bool vsync = true,
			Uint32 flags = (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_CAPTURE));

		~Window();

		inline const int GetWidth() const {
			return windowWidth;
		}

		inline const int GetHeight() const {
			return windowHeight;
		}

		inline const int GetOriginX() const {
			return originX;
		}

		inline const int GetOriginY() const {
			return originY;
		}

		inline Windowptr& GetWindow(){
			return windowPtr;
		}

		inline const SDL_GLContext& GetGLContext() const {
			return sdlGLContext;
		}

		bool setGLContext();

		void setWindowHeader(const std::string& windowHeader);
	

	private:
		Windowptr windowPtr;
		int windowWidth;
		int windowHeight;
		int originX;
		int originY;
		std::string windowHeader;
		SDL_GLContext sdlGLContext;

		void createWindow(Uint32 flags);

	};
}




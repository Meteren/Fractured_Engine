#pragma once

#include <memory>

#include <SDL.h>


namespace FRACTURED_UTILS {
	struct SDL_Destroyer {

		void operator()(SDL_Window* window) const;

		void operator()(SDL_Gamepad* controller) const;

		void operator()(SDL_Cursor* cursor) const;


	};

}


typedef std::shared_ptr<SDL_Gamepad> Controller;

typedef std::shared_ptr<SDL_Cursor> Cursor;

static Controller makeSharedController(SDL_Gamepad* controller);

static Cursor makeSharedCursor(SDL_Cursor* cursor);

typedef std::unique_ptr<SDL_Window, FRACTURED_UTILS::SDL_Destroyer> Windowptr;
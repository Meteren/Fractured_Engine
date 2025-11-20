#include "SDL_Wrapper.h"

namespace FRACTURED_UTILS {

	void SDL_Destroyer::operator()(SDL_Window* window) const
	{
		SDL_DestroyWindow(window);

	}

	void SDL_Destroyer::operator()(SDL_Gamepad* controller) const
	{

	}

	void SDL_Destroyer::operator()(SDL_Cursor* cursor) const
	{
		SDL_DestroyCursor(cursor);
	}

	Controller makeSharedController(SDL_Gamepad* gamepad)
	{
		return Controller(gamepad);
	}

	Cursor makeSharedCursor(SDL_Cursor* cursor)
	{
		return Cursor(cursor);
	}
}



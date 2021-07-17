#include <te.hpp>



void t3v::engine::update_input()
{
	//getting all the new events
	while(SDL_PollEvent(&m_event))
	{
	}
	m_keyboard_state=(uint8_t*)SDL_GetKeyboardState(NULL);
}
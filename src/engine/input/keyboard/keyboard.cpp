#include <te.hpp>

bool t3v::engine::key_is_pressed(uint8_t scancode)
{
	return m_keyboard_state[scancode];
}

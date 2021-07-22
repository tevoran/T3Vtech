#ifndef TE_RENDER_H
#define TE_RENDER_H

#include <SDL2/SDL.h>

/*there renderer layer is used for communication between
the high level API and the different renderers*/
int te_start_renderer(unsigned long FLAGS);
void te_update();
void te_quit();

void te_render(te_color pixel_color, int x, int y);

#endif
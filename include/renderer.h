#ifndef RENDERER_H
#define RENDERER_H

typedef enum {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
} Color;

typedef struct {
	int width;
	int height;

	char title[100];

	Color* framebuffer;
} Viewport;

Viewport create_viewport(int width, int height, char title[100], Color bg_color);
void render(Viewport* viewport);
void clear_framebuffer(Viewport* viewport);

#endif

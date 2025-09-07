#ifndef RENDERER_H
#define RENDERER_H

typedef struct {
	int width;
	int height;

	char title[100];

	int* framebuffer;
} Viewport;

Viewport create_viewport(int width, int height, char title[100]);
void render(Viewport* viewport);
void clear_framebuffer(Viewport* viewport);

#endif

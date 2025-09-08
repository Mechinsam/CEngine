#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

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
	Color bg_color;
} Viewport;

Viewport create_viewport(int width, int height, char title[100], Color bg_color)
{
	Viewport viewport;
	viewport.width = width;
	viewport.height =  height;
	snprintf(viewport.title, sizeof(viewport.title), "%s", title);
	viewport.framebuffer = malloc(width * height * sizeof(Color));
	viewport.bg_color = bg_color;

	return viewport;
}

void render(Viewport* viewport)
{
	printf("%s\n", viewport->title);
	// border
	printf("+");
	for (int i=0; i < 80; i++)
	{
		printf("-");
	}
	printf("+");
	printf("\n");
	
	for (int y=0; y < viewport->height; y+=2)
	{
		printf("|");
		for (int x=0; x < viewport->width; x++)
		{
			Color top = viewport->framebuffer[y * viewport->width + x];
			Color bottom = BLACK;

			if (y+1 < viewport->height)
			{
				bottom = viewport->framebuffer[(y+1)  * viewport->width + x];
			}

			// display
			printf("\033[4%dm", viewport->bg_color);
			if (top && bottom) {
				printf("\033[3%d;4%dm▀", top, bottom);
			}
			else if (top)
				printf("\033[3%dm▀", top);
			else if (bottom)
				printf("\033[3%dm▄", bottom);
			else
				printf(" ");
			
			printf("\033[0m");
		}
		printf("|");
		printf("\n");
	}

	// border
	printf("+");
	for (int i=0; i < 80; i++)
	{
		printf("-");
	}
	printf("+");
	printf("\n");
}

void clear_framebuffer(Viewport* viewport)
{
	for (int y=0; y < viewport->height; y++)
	{
		for (int x=0; x < viewport->width; x++)
		{
			viewport->framebuffer[y * viewport->width + x] = BLACK;
		}
	}
}

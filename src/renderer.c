#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

typedef struct {
	int width;
	int height;

	char title[100];

	int* framebuffer;
} Viewport;

Viewport create_viewport(int width, int height, char title[100])
{
	Viewport viewport;
	viewport.width = width;
	viewport.height =  height;
	snprintf(viewport.title, sizeof(viewport.title), "%s", title);
	viewport.framebuffer = malloc(width * height * sizeof(int));

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
			int top = viewport->framebuffer[y * viewport->width + x];
			int bottom = 0;

			if (y+1 < viewport->height)
			{
				bottom = viewport->framebuffer[(y+1)  * viewport->width + x];
			}

			// display
			if (top && bottom) printf("█");
			else if (top) printf("▀");
			else if (!top && bottom) printf("▄");
			else printf(" ");
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
			viewport->framebuffer[y * viewport->width + x] = 0;
		}
	}
}

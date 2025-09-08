#include <stdio.h> // used for output
#include <stdlib.h> // rng
#include <time.h> // seed for rng

#include "../include/renderer.h"
#include "../include/input.h"

// import sleep function depending on OS
#ifdef _WIN32
	#include <windows.h>
	#define SLEEP(s) Sleep((s) * 1000)
#else
	#include <unistd.h>
	#define SLEEP(s) usleep((s) * 1000000)
#endif


#define WIDTH 80
#define HEIGHT 40
#define FRAMERATE 60.0


void old_update(int framebuffer[WIDTH][HEIGHT], int *pos_x, int *pos_y)
{
	if (kbhit())
	{
		char c = getchar();

		switch (c)
		{
			case 'w':
				*pos_y -= 1;
				break;
			case 'a':
				*pos_x -= 1;
				break;
			case 's':
				*pos_y += 1;
				break;
			case 'd':
				*pos_x += 1;
				break;
			default:
				break;
		}
	}
	framebuffer[*pos_x][*pos_y] = RED;
}

void update(Viewport* viewport, int *pos_x, int *pos_y, int *speed_x, int *speed_y, Color *current_color)
{
	*pos_x += *speed_x; *pos_y += *speed_y;

	if (*pos_x < 0 || *pos_x > WIDTH - 1){
		*speed_x = -*speed_x;
		*current_color = 1+rand() % 7;
	} 
	if (*pos_y < 0 || *pos_y > HEIGHT -1) {
		*speed_y = -*speed_y;
		*current_color = 1+rand() % 7;
	}

	if (*pos_x < 0) *pos_x = 0;
	if (*pos_x > WIDTH-1) *pos_x = WIDTH-1;
	if (*pos_y < 0) *pos_y = 0;
	if (*pos_y > HEIGHT-1) *pos_y = HEIGHT-1;

	
	viewport->framebuffer[*pos_y * viewport->width + *pos_x] = *current_color;
}


int main()
{
	//init_keyboard();
	
	srand(time(NULL));
	Viewport viewport = create_viewport(WIDTH, HEIGHT, "Bouncing demo - CEngine", GREEN);

	int pos_x = rand() % (WIDTH-1);
	int pos_y = rand() % (WIDTH-1);
	Color current_color = 1+rand() % 7;
	int speed_x = 1, speed_y = 1;

	int running = 1;
	printf("\033c");
	while (running)
	{
		printf("\033[H");
		clear_framebuffer(&viewport);

		// update
		update(&viewport, &pos_x, &pos_y, &speed_x, &speed_y, &current_color);
	
		render(&viewport);
		SLEEP(1.0/FRAMERATE);
	}

	return 0;
}

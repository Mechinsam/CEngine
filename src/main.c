#include <stdio.h> // used for output
#include <stdlib.h> // rng
#include <time.h> // seed for rng

// import sleep function depending on OS
#ifdef _WIN32
	#include <windows.h>
	#define SLEEP(s) Sleep((s) * 1000)
#else
	#include <unistd.h>
	#define SLEEP(s) usleep((s) * 1000000)
#endif


#define WIDTH 80
#define HEIGHT 30
#define FRAMERATE 60.0


void render(int framebuffer[WIDTH][HEIGHT])
{
	// border
	for (int i=-2; i < 80; i++)
	{
		printf("-");
	}
	printf("\n");
	
	for (int y=0; y < HEIGHT; y++)
	{
		printf("|");
		for (int x=0; x < WIDTH; x++)
		{
			//printf("%d", framebuffer[x][y]);
			if (framebuffer[x][y] == 1) {
				printf("█");
			} else {
				printf(" ");
			}
		}
		printf("|");
		printf("\n");
	}

	// border
	for (int i=-2; i < 80; i++)
	{
		printf("-");
	}
	printf("\n");
}

void clear_framebuffer(int framebuffer[WIDTH][HEIGHT])
{
	for (int y=0; y < HEIGHT; y++)
	{
		for (int x=0; x < WIDTH; x++)
		{
			framebuffer[x][y] = 0;
		}
	}
}


void update(int framebuffer[WIDTH][HEIGHT])
{
	int rand_x = rand() % ((WIDTH-1) - 0 + 1) + 0;
	int rand_y = rand() % ((HEIGHT-1) - 0 + 1) + 0;
	framebuffer[rand_x][rand_y] = 1;

}

int main()
{
	srand(time(NULL));
	int framebuffer[WIDTH][HEIGHT] = {0};

	while (true)
	{
		printf("\033[H");
		clear_framebuffer(framebuffer);

		// update
		update(framebuffer);
	
		render(framebuffer);
		SLEEP(1.0/FRAMERATE);
	}

	return 0;
}

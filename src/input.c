// idk what 90% of this does

#include <stdio.h>
#include <termios.h>
#include <sys/select.h>
#include <signal.h>
#include <stdlib.h>

#include <unistd.h>

// save original terminal settings
struct termios orig_termios;

void reset_terminal_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode() {
	struct termios new_termios;
	tcgetattr(STDIN_FILENO, &orig_termios);		// save original settings
	new_termios = orig_termios;					// dupe settings
	new_termios.c_lflag &= ~(ICANON | ECHO);	// disable line buffering and echo
	new_termios.c_cc[VMIN] = 1;					// idk what this does
	new_termios.c_cc[VTIME] = 0;				// no timeout i think
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // apply new settings
}

int kbhit(void) {
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);

	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void handle_sigint(int _signal)
{
	reset_terminal_mode();
	exit(0);
}

void init_keyboard()
{
	set_conio_terminal_mode();
	signal(SIGINT, handle_sigint);
	atexit(reset_terminal_mode);
}

#include "main.h"

/**
* handle_signal - Handle a signal
* @signum: The signal number to handle
*
* This function is a signal handler for specific signals.
*/
void handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		exit(0);
	}
}

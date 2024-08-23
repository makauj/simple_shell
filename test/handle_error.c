#include "main.h"

/**
 * handle_error - function to handle error messages
 * @msg: pointer to the error message
 */

void handle_error(const char *msg)
{
	write(STDERR_FILENO, msg, _strlen(msg));
}

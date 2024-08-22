#include "main.h"

/**
 * handle_error - function to handle error messages
 * @msg: pointer to the error message
 */

void handle_error(const char *msg)
{
	perror(msg);
}

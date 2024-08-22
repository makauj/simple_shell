#include "main.h"

/**
 * display_prompt - function to handle display
 */

void display_prompt(void)
{
	write(STDOUT_FILENO, PROMPT, _strlen(PROMPT) - 1);
}

#include "shell.h"

/**
 * exit_shell - function that takes in two arguments: args and front.
 * @args: array of strings that contains the arguments passed to the shell.
 * @front: a pointer to the start of the array.
 * Return: If there is a second argument in args, NULL.
 */

int exit_shell(char **args, char **front)
{
	int status = 0;

	if (args[1] != NULL)
	{
	status = atoi(args[1]);
	}

	exit(status);
}

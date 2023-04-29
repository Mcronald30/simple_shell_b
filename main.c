#include "shell.h"

/**
 * main - runs shell commands
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @env: Enviromnet variable
 * Return: Always 0
 */

int main(int argc, char *argv[], char **env)
{
	char *prompt = "$ ";
	char *buffer = NULL;
	size_t buffer_size = 0;
	bool pipe = false;

	while (argc > 0)
	{
		if (!pipe)
			write(STDOUT_FILENO, prompt, 2);

		if (!read_input(&buffer, &buffer_size, pipe))
			continue;

		char **args;
		size_t n;

		if (tokenize_input(buffer, " ", &args, &n))
		{
		if (builtin_commands(args, n))
		{

		free_vector(args, n);
		continue;
		}

	char *fullpath = NULL;

	if (!get_full_path(args[0], &fullpath))
	{
		print_error(argv[0], args[0], "not found");
		free_vector(args, n)
		continue;
	}

	execute_command(fullpath, args, n, env);
	free(fullpath);
		}
	free(buffer);
	}
	return (0);
}

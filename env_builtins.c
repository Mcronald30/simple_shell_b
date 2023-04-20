#include "shell.h"

/**
 * env_shell - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Return: 0
 */
int env_shell(char **args, char **front)
{
	char **environ = env;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (1);
}


/**
 * set_env - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Return: 0
 */
int set_env(char **args, char **front)
{
	char **env_var = NULL, **new_env, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; env[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; env[index]; index++)
		new_env[index] = env[index];

	free(environ);
	env = new_env;
	env[index] = new_value;
	env[index + 1] = NULL;

	return (0);
}

/**
 * unset_env - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: 0 success
 */
int unset_env(char **args, char **front)
{
	char **env_var, **new_env;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; env[size]; size++)

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; env[index]; index++)
	{
		if (*env_var == env[index])
		{
			free(*env_var);
			continue;
		}
		new_env[index2] = env[index];
		index2++;
	}
	free(env);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}

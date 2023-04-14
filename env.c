#include "shell.h"

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 * O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **env_copy;
	size_t size;
	int index;

	for (size = 0; env[size]; size++)

	env_copy = malloc(sizeof(char *) * (size + 1));
	if (!env_copy)
		return (NULL);

	for (index = 0; env[index]; index++)
	{
		env_copy[index] = malloc(_strlen(env[index]) + 1);

		if (!env_copy[index])
		{
			for (index--; index >= 0; index--)
				free(env_copy[index]);
			free(env_copy);
			return (NULL);
		}
		_strcpy(env_copy[index], env[index]);
	}
	env_copy[index] = NULL;

	return (env_copy);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; env[index]; index++)
		free(env[index]);
	free(env);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; env[index]; index++)
	{
		if (_strncmp(var, env[index], len) == 0)
			return (&env[index]);
	}

	return (NULL);
}

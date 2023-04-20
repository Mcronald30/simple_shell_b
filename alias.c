#include "shell.h"

/**
 * shell_alias - prints all aliases, desired aliases.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_alias(char **args, char **front)
{
	alias_t *dir = aliases;
	int i, len = 0;
	char *value;

	if (!args[0])
	{
		while (dir)
		{
			print_alias(dir);
			dir = dir->next;
		}
		return (len);
	}
	for (i = 0; args[i]; i++)
	{
		dir = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (dir)
			{
				if (_strcmp(args[i], dir->name) == 0)
				{
					print_alias(dir);
					break;
				}
				dir = dir->next;
			}
			if (!dir)
				len = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (len);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value.
 * @var_name: Name of the alias.
 * @value: Value of the alias.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *dir = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (dir)
	{
		if (_strcmp(var_name, dir->name) == 0)
		{
			free(dir->value);
			dir->value = new_value;
			break;
		}
		dir = dir->next;
	}
	if (!dir)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return (NULL);
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *dir;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		dir = aliases;
		while (dir)
		{
			if (_strcmp(args[i], dir->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(dir->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, dir->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			dir = dir->next;
		}
	}

	return (args);
}

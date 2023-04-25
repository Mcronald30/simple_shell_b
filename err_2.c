#include "shell.h"

char *err_126(char **args);
/**
 * err_126 - Prints error for permission denied failures.
 * @args: An array of arguments.
 * Return: error.
 */
char *err_126(char **args)
{
	char *err_126(char **args)
{
	char *err, *his_str;
	int len;

	his_str = _itoa(his);
	if (!his_str)
		return (NULL);

	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(his_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(his_str);
	return (err);
}

char *err_127(char **args);
/**
 * err_127 - Print error for command not found failures.
 * @args: An array of arguments.
 * Return: error.
 */
char *err_127(char **args)
{
	char *err, *his_str;
	int len;

	his_str = _itoa(his);
	if (!his_str)
		return (NULL);

	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(his_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, his_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");

	free(his_str);
	return (err);
}

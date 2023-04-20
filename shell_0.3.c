#include "shell.h"

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/**
 * token_len - a function that takes in a string and a delimiter.
 * @str: the string to be searched.
 * @delim: a delimiter character.
 * Return: the len of str.
 */
int token_len(char *str, char *delim)
{
	int len = 0;
	char *token = strtok(str, delim);

	while (token != NULL)
	{
		len++;
		token = strtok(NULL, delim);
	}
	return (len);
}

/**
 * count_tokens - the number of tokens (substrings)
 * in the string when split by the delimiter.
 * @str: the string to be searched.
 * @delim: a delimiter character.
 * Return: the number of tokens in str when split by delim.
 */
int count_tokens(char *str, char *delim)
{
	int count = 0;
	char *token = strtok(str, delim);

	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}
	return (count);
}

/**
 * _strtok -  Tokonizing a string cuharacter.
 * @line: function takes in a string line
 * @delim: a delimiter character.
 * Return: a pointer to an array of strings where each element
 * of the array is a token in line that is split by delim.
 */
char **_strtok(char *line, char *delim)
{
	int count = count_tokens(line, delim);
	char **tokens = malloc((count + 1) * sizeof(char *));

	if (tokens == NULL)
	{
		return (NULL);
	}

	char *token = strtok(line, delim);
	int i = 0;

	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}

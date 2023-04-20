#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */

int num_len(int num)
{
	int len = 0;

	if (num == 0)
	{
	return (1);
	}
	else if (num < 0)
	len++;
	num = -num;

	while (num > 0)
	{
	len++;
	num /= 10;
	}
	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	int len = num_len(num);
	char *str = malloc((len + 1) * sizeof(char));

	if (num < 0)
	{
	str[0] = '-';
	num = -num;
	}

	str[len] = '\0';
	for (int i = len - 1; i >= 0; i--)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	int argc = 0;

	if (args[argc] != NULL)
	{
	argc++;
	}
	printf("Error %d: ", err);
	for (int i = 0; i < argc; i++)
	{
		printf("%s", args[i]);
		if (i < argc - 1)
		{
			printf(", ");
		}
	}
	printf("\n");
	return (err);
}

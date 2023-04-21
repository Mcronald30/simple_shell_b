#include "shell.h"

/***
 * _realloc - Reallocates a memory block.
 * @ptr: A pointer to the block of memory to be reallocated.
 * @old_size: The size of the block of memory to be reallocated, in bytes.
 * @new_size: The new size the block of memory, in bytes.
 * Return: a pointer to the reallocated block of memory.
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	if (new_size == old_size)
	return (ptr);

	if (new_size == 0)
	{
	free(ptr);
	return (NULL);
	}
        void *new_ptr = malloc(new_size);
	if (!new_ptr)
	{
	free(ptr);
	return (NULL);
	}

        if (ptr)
	{
	size_t copy_size = old_size < new_size ? old_size : new_size;
	memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	}
        return (new_ptr);
}

/**
 * assign_lineptr - Reassigns the lineptr variable.
 * @lineptr: A pointer to a pointer to a character.
 * @n:  A pointer to a size_t value, representing
 * the size of the buffer pointed to by lineptr.
 * @buffer: A pointer to a character thatt read input.
 * @b: A size_t value, representing the length of the line read from input.
 * Return: no value, hence the void return type.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
        size_t new_size = 120;

        if (*lineptr == NULL || *n < b)
	{
		if (b > new_size)
			new_size = b;

                char *new_ptr = realloc(*lineptr, new_size);

		if (new_ptr == NULL)
		{
			return;
		}
		*lineptr = new_ptr;
		*n = new_size;
	}

	_strcpy(*lineptr, buffer);
	free(buffer);
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: A pointer to a pointer to a character.
 * @n: a pointer to a variable that specifies the size of the buffer pointed.
 * @stream:  a pointer to a FILE object.
 * Return: the number of characters read from the input stream.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input != 0)
	{
		return (-1);
	}

	fflush(stream);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
	{
		return (-1);
	}

	while (c != '\n')
	{
	r = read(STDIN_FILENO, &c, 1);

	if (r == -1 || (r == 0 && input == 0))
	{
	free(buffer);
	return (-1);
	}

	if (r == 0 && input != 0)
	{
	input++;
	break;
	}

	if (input >= 120)
	{
	
	buffer = realloc(buffer, input + 1);
	if (!buffer)
	{
	free(buffer);
	return (-1);
	}
	}
	buffer[input] = c;
	input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	input = 0;
	return (ret);
}

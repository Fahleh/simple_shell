#include "shell.h"

/**
 * _printf -  A function that prints a string
 * @fmt: format specifier.
 */

void _printf(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);

	vprintf(fmt, args);

	va_end(args);

}

/**
 * _handleSignal - handles  Ctrl+c
 * @sig: parameter.
 */

void _handleSignal(int sig)
{
	(void)sig;
}

/**
 * _getLine - A function that reads a file line by line
 * @line: Pointer to location where line will be read into.
 * @s: Buffer size
 * @stream: Input stream being read
 *
 * Return: Number of characters read.
 */

ssize_t _getLine(char **line, size_t *s, FILE *stream)
{
	int c;
	size_t i = 0;
	char *temp;

	if (!line || !s)
	{
		return (-1);
	}
	if (*line == NULL || *s == 0)
	{
		*s = INPUT_BUFFER;  /* Initial buffer size */
		*line = (char *)malloc(*s);
		if (*line == NULL)
		{
			perror("malloc");
			return (-1);
		}
	}
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i >= *s - 1)
		{
			*s *= 2;
			temp = (char *)realloc(*line, *s);
			if (temp == NULL)
			{
				free(*line);
				*line = NULL;
				perror("realloc");
				return (-1);
			}
			*line = temp;
		}
		(*line)[i++] = (char)c;
	}
	if (i == 0 && c == EOF)
		return (-1);
	(*line)[i] = '\0';  /* Null-terminate the string */
	return (i);
}


/**
 * _strTok - A function that splits a string into substings(tokens).
 * @str: string to be tokenized
 * @delim: token delimiter
 * Return: token
 */

char *_strTok(char *str, const char *delim)
{
	static char *lastToken;
	char *token;

	if (str != NULL)
	{
		lastToken = str;
	}
	else if (lastToken == NULL)
	{
		return (NULL);  /* No more tokens */
	}
	/* Find the next delimiter in the string */
	token = lastToken;

	/* Skip-over starting delims */
	while (*lastToken != '\0' && strchr(delim, *lastToken) != NULL)
	{
		lastToken++;
	}
	if (*lastToken != '\0')
	{
		token = lastToken;
		while (*lastToken != '\0' && strchr(delim, *lastToken) == NULL)
		{
			lastToken++;
		}
		if (*lastToken != '\0')
		{
			*lastToken++ = '\0';
		}
		return (token);
	}
	lastToken = NULL;
	return (NULL);
}

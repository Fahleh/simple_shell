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

    if (!line || !s) {
        return (-1);
    }


    /* Allocate initial buffer or resize if needed */
    if (*line == NULL || *s == 0) {
        *s = 128;  /* Initial buffer size */
        *line = (char *)malloc(*s);
        if (*line == NULL) {
            return (-1);  /* Memory allocation failure */
        }
    }

    while ((c = fgetc(stream)) != EOF && c != '\n')
    {
        if (i >= *s - 1) {
            /* Resize the buffer */
            *s *= 2;
            temp = (char *)realloc(*line, *s);
            if (temp == NULL) {
                free(*line);
                *line = NULL;
                return (-1);  /* Memory allocation failure */
            }
            *line = temp;
        }
        (*line)[i++] = (char)c;
    }

    if (i == 0 && c == EOF) {
        return (-1);  /* No characters read, reached end of file */
    }

    (*line)[i] = '\0';  /* Null-terminate the string */

    return (i);  /* Return the number of characters read */
}


#include "shell.h"

/**
 * _tokenize - A function to tokenize a string.
 * @cmd: Input from user.
 * @args: Pointer to memory for tokens.
 * Return: tokens.
 */

void _tokenize(char *cmd, char **args)
{

	int i = 0;
	char *token = strtok(cmd, DELIM);


	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, DELIM);

	}
	args[i] = NULL;
}

/**
 * _freedptr - A function to free a double pointer.
 *
 * @args: Double pointer to an array of strings.
 *
 * Return: Void.
 */

void _freedptr(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * _testCommand - A function that tests if a command is executable.
 * @path: Command to test.
 *
 * Return: Void
 */

bool _testCommand(char *path)
{
	if (path == NULL)
	{
		return (false);
	}

	return (access(path, X_OK) == 0);
}

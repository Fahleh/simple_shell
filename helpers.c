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
	char *token = _strTok(cmd, DELIM);


	while (token)
	{
		args[i] = token;
		i++;
		token = _strTok(NULL, DELIM);

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

/**
 * _checkKeyword - A function that checks for certain keywords
 * @args: Tokenized command arguments.
 * @cmd: User commands.
 * @av: Command-line arguments.
 * @env: The executing environment.
 *
 * Return: 1 if match found, 0 otherwise.
 */

int _checkKeyword(char **args, char *cmd, char **av, char **env)
{
	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			_exitCmd(args, av, cmd);
			return (1);
		}
		else
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
	}
	else if (strcmp(args[0], "env") == 0)
	{
		_printEnv(env);
		return (1);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		_setEnv(args[1], args[2]);
		return (1);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		_unsetEnv(args[1]);
		return (1);
	}
	return (0);
}

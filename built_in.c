#include "shell.h"

/**
 * _prompt - Displays a prompt
 * Return: Void
 */

void _prompt(void)
{
	_printf("#->$ ");
}

/**
 * read_cmd - A function to read user input.
 * @cmd: Pointer to string containing user input.
 * Return: Void.
 */

void read_cmd(char **cmd)
{
	size_t s = 0;

	if (_getLine(cmd, &s, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(*cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			_printf("Error: Failed to read input\n");
			free(*cmd);
			exit(EXIT_FAILURE);
		}
	}

	(*cmd)[strcspn(*cmd, "\n")] = '\0';
}

/**
 * _getPath - A function that gets the path to a command
 * @command: The first token (args[0]).
 * Return: path, if found, or null, if !exist
 */

char *_getPath(char *command)
{
	/* Get the PATH environment variable */
	char *tempPath, *pToken, *path = getenv("PATH");
	char *fullPath, cmdPath[BUFFER_SIZE];

	tempPath = strdup(path);

	/* Tokenize the PATH */
	pToken = strtok(tempPath, ":");

	while (pToken != NULL)
	{
		/* Concatenate the strings in pToken & command */
		snprintf(cmdPath, BUFFER_SIZE, "%s/%s", pToken, command);

		/* Check if the command exists */
		if (access(cmdPath, X_OK) == 0)
		{
			fullPath = malloc(strlen(cmdPath) + 1);
			strcpy(fullPath, cmdPath);

			free(tempPath);
			return (fullPath);
		}
		pToken = strtok(NULL, ":");
	}
	free(tempPath);

	return (NULL);
}

/**
 * _printEnv - A function that prints out the environment.
 * @env: Environment variable.
 *
 */

void _printEnv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		_printf("%s\n", env[i]);
		i++;
	}
}

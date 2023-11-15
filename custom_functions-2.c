#include "shell.h"

/**
 * _exitCmd -  A function that exits the program.
 * @args: exit and status.
 * @av: Command line argumenta.
 * @cmd: User commands.
 * return: Void.
 */

void _exitCmd(char **args, char **av, char *cmd)
{
	int i, status;

		for (i = 0; args[1][i] != '\0'; i++)
		{
			if (!isdigit(args[1][i]))
			{
				fprintf(stderr, "%s: 1: %s: Illegal number: %s\n"
						, av[0], args[0], args[1]);
				free(cmd);
				exit(2);
			}
		}
		status = atoi(args[1]);
		free(cmd);
		exit(status);
}

/**
 * _operatorCheck - A function that checks for && or || in the command.
 * @cmd: User command.
 * @av: Command line arguments.
 * @env: Executing environment.
 * Return: 0 if no operator found, 1 otherwise.
 */

int _operatorCheck(char *cmd, char **av, char **env)
{
	char *commands[128], *args[128], *delim = NULL, *currCmd, *token, *path;
	int i = 0, j;

	if (strstr(cmd, "&&") != NULL)
		delim = "&&";
	if (strstr(cmd, "||") != NULL)
		delim = "||";
	if (delim != NULL)
	{
		token = strtok(cmd, delim);
		while (token != NULL)
		{
			commands[i++] = token;
			token = strtok(NULL, delim);
		}
		for (j = 0; j < i; ++j)
		{
			currCmd = commands[j];
			_tokenize(currCmd, args);
			if (args[0] == NULL)
				continue;
			if (_checkKeyword(args, currCmd, av, env))
				continue;
			if (strchr(args[0], '/') != NULL)
				path = strdup(args[0]);
			else
				path = _getPath(args[0]);
			if (_testCommand(path))
			{
				_fork(path, args, av, env);
				if (strcmp(delim, "||") == 0)
					break;
			}
			else
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
				free(path);
			}
		} return (0);
	} return (1);
}

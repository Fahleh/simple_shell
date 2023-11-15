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

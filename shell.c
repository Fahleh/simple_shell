#include "shell.h"
/**
 * main - Entry point for simple_shell program.
 * @ac: argument count
 * @av: argument vectors
 * @env: The executing environment.
 *
 * Return: 0 on success.
 */

int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *cmd = NULL;
	int isInteractive = isatty(STDIN_FILENO);

	signal(SIGINT, _handleSignal);
	while (1)
	{
		if (isInteractive)
			_prompt();

		read_cmd(&cmd);

		if (cmd != NULL)
		{
			executeCommand(cmd, av, env);
		}
		else
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}

	return (0);
}

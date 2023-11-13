#include "shell.h"

/**
 * _fork - A function that creates a child process and processes
 * the execution of user commands.
 *
 * @path: Command Path.
 * @args: Command arguments.
 * @av: Command-line arguments.
 * @env: The executing environment.
 */

void _fork(char *path, char **args, char **av, char **env)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror(av[0]);
		free(path);
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, args, env);

		/* If execution fails */
		perror("execve");
		free(path);
		free(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
	}
}

/**
 * executeCommand - executes user commands
 * @cmd: User commands.
 * @av: Command-line arguments.
 * @env: The executing environment.
 */

void executeCommand(char *cmd, char **av, char **env)
{
	char *args[INPUT_BUFFER];
	char *path;

	_tokenize(cmd, args);

	if (args[0] == NULL)
	{
		return;
	}

	if(strcmp(args[0], "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}

	if(strcmp(args[0], "env") == 0)
	{
		_printEnv(env);
		return;
	}

	/* check if command string contains / */
	if (strchr(args[0], '/') != NULL)
	{
		path = strdup(args[0]);
	}
	else
	{
		path = _getPath(args[0]);
	}

	/* check if command is executable */
	if (_testCommand(path))
	{
		_fork(path, args, av, env);
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
		free(path);
		return;
	}
}
#include "shell.h"

/**
 * _setEnv - A function that sets an environment variable.
 * @var: Variable to set.
 * @val: Value to assign to variable.
 * Return: On success 0, -1 on failure.
 */

int _setEnv(const char *var, const char *val)
{
	if (var == NULL || val == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}


	if (setenv(var, val, 1) == -1)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * _unsetEnv - A function that removees an environment variable.
 * @var: Variable to unset.
 * Return: On success 0, -1 on failure.
 */

int _unsetEnv(const char *var)
{
	if (var == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(var) == -1)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}

/**
 * _handleCD - changes directory
 * @args: Command arguments.
 * Return: 0 on success, -1 otherwise.
 */

int _handleCD(char **args)
{
	char *newDir, *currDir;

	if (args[1] == NULL)
	{
		newDir = getenv("HOME");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		newDir = getenv("OLDPWD");
		if (newDir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (-1);
		}
	}
	else
	{
		newDir = args[1];
	}

	currDir = getcwd(NULL, 0);
	if (currDir == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (chdir(newDir) == -1)
	{
		perror("chdir");
		free(currDir);
		return (-1);
	}
	if (_updateEnv(currDir) == -1)
	{
		free(currDir);
		return (-1);
	}
	free(currDir);
	return (0);

}


/**
 * _updateEnv - Updates the PWD variable after directory change.
 * @currDir: The current working directory.
 * Return: 0 on success, -1 otherwise.
 */

int _updateEnv(char *currDir)
{
	char *pwd;

	pwd = NULL;
	asprintf(&pwd, "PWD=%s", currDir);

	if (pwd == NULL)
	{
		perror("asprintf");
		return (-1);
	}

	if (_setEnv("OLDPWD", currDir) == -1 || _setEnv("PWD", currDir) == -1)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (0);
}

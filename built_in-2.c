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


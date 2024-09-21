#include "shell.h"

/**
 * create_envi - Creates an array of Enviroment Variables
 * @envi: Array to store Enviroment Variables
 */

void create_envi(char **envi)
{
	int i;

	for (i = 0; environ[i]; i++)
		envi[i] = _strdup(environ[i]);
	envi[i] = NULL;
}

/**
 * free_env - Frees the memory of the created Enviroment Variables array
 * @env:  Array of Environment variables
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}

/**
 * _setenv - Handles the setenv built-in command
 * @cmd: Command arguments
 * Return: 0 on success, -1 on failure
 */
int _setenv(char **cmd)
{
	if (cmd[1] == NULL || cmd[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	if (setenv(cmd[1], cmd[2], 1) == -1)
		return (-1);

	return (0);
}

/**
 * _unsetenv - Handles the unsetenv built-in command
 * @cmd: Command arguments
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char **cmd)
{
	if (cmd[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(cmd[1]) == -1)
		return (-1);

	return (0);
}

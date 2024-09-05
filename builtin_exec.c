#include "shell.h"

/**
 * change_dir - Changes directory
 * @cmd: Parsed command
 * @st: Status of last command executed
 * Return: 0 on success 1 if failed (For OLDPWD Always 0 incase of no OLDPWD)
 */
int change_dir(char **cmd, __attribute__((unused))int st)
{
	int value = -1;
	char cwd[PATH_MAX], *oldpwd;

	if (cmd[1] == NULL)
		value = chdir(_getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		oldpwd = _getenv("OLDPWD");
		if (oldpwd == NULL)
		{
			fprintf(stderr, "hsh: cd: OLDPWD not set \n");
			return (0);
		}
		value = chdir(oldpwd);
		if (value != -1)
			printf("%s\n", oldpwd);
	}
	else
		value = chdir(cmd[1]);
	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("OLDPWD", _getenv("PWD"), 1);
			setenv("PWD", cwd, 1);
		}
		else
		{
			perror("hsh: getcwd");
			return (-1);
		}
	}
	return (0);
}

/**
 * dis_env - Display enviroment variable
 * @cmd: parsed command
 * @st: status of last command executed
 * Return: Always 0
 */
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st)
{
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * echo_bul - execute echo cases
 * @st: statue of last command executed
 * @cmd: parsed command
 * Return: Always 1 Or execute normal echo
 */
int echo_bul(char **cmd, int st)
{
	char *path;
	unsigned int pid = getpid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_int(st);
		PRINT("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINT("\n");
	}
	else if (cmd[1][0] == '$')
	{
		path = _getenv(cmd[1] + 1);
		if (path)
		{
			PRINT(path);
			PRINT("\n");
			free(path);
		}
		else
			PRINT("\n");
	}
	else
		return (print_echo(cmd));

	return (1);
}

/**
 * history_dis - display history of user input on simple_shell
 * @c: parsed command
 * @st: status of last command executed
 * Return: 0 success or -1 if fail
 */
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int st)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = _itoa(counter);
		PRINT(er);
		free(er);
		PRINT(" ");
		PRINT(line);
	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}

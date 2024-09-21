#include "shell.h"

/**
 * main - Entry point to program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Returns condition
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *input, **cmd, **commands;
	int count = 0, i, condition = 1, stat = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal(SIGINT, signal_to_handle);
	while (condition)
	{
		count++;
		if (isatty(STDIN_FILENO))
			prompt();
		input = get_line();
		if (input[0] == '\0')
			continue;
		history(input);
		commands = separator(input);
		for (i = 0; commands[i] != NULL; i++)
		{
			cmd = parse_cmd(commands[i]);
			if (_strcmp(cmd[0], "exit") == 0)
			{
				free(commands);
				exit_bul(cmd, input, argv, count, stat);
			}
			else if (_strcmp(cmd[0], "setenv") == 0)
			{
				if (_setenv(cmd) == -1)
					perror("setenv");
			}
			else if (_strcmp(cmd[0], "unsetenv") == 0)
			{
				if (_unsetenv(cmd) == -1)
					perror("unsetenv");
			}
			else if (check_builtin(cmd) == 0)
			{
				stat = handle_builtin(cmd, stat);
				free(cmd);
				continue;
			}
			else
				stat = check_cmd(cmd, input, count, argv);
			free(cmd);
		}
		free(input);
		free(commands);
		wait(&stat);
	}
	return (stat);
}

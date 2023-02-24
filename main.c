#include "shell.h"

/**
 * main - code that compiles all my functions
 * Return: 0 on success and -1 on failure
 */
int main(void)
{
	char *command = NULL, *command_copy = NULL, *token;
	char **argv;
	size_t n = 0;
	const char *delim = " \n";
	pid_t my_pid;
	int num_chars, num_tokens, status, i;

	while (1)
	{
		printf("$ ");
		num_chars = getline(&command, &n, stdin);
		if (num_chars == -1)
		{
			putchar('\n');
			return (-1);
		}
		command_copy = malloc(sizeof(char) * num_chars);
		strcpy(command_copy, command);
		token = strtok(command, delim);
		for (num_tokens = 0; token != NULL; num_tokens++)
			token = strtok(NULL, delim);
		num_tokens++;
		argv =  malloc(sizeof(char *) * num_tokens);
		token = strtok(command_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		my_pid = fork();
		if (my_pid == 0)
			execmd(argv);
		else
			wait(&status);
	}
	free(command_copy);
	free(command);
	return (0);
}

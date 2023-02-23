#include "shell.h"

int main(void)
{
	char *command = NULL, *command_copy = NULL, *token;
	char **argv;
	size_t n = 0;
	ssize_t num_chars;
	const char *delim = " \n";
	int num_tokens, i;

	while (1)
	{
		printf("$ ");
		num_chars = getline(&command, &n, stdin);
		if (num_chars == -1){
			putchar('\n');
			return (-1);
		}

		command_copy = malloc(sizeof(char) * num_chars);
		if (command_copy == NULL){
			perror("tsh: memory allocation error\n");
			return (-1);
		}
		strcpy(command_copy, command);
	
		token = strtok(command, delim);
		for (num_tokens = 0; token != NULL; num_tokens++)
			token = strtok(NULL, delim);
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);
		token = strtok(command_copy, delim);
		for (i = 0; token != NULL; i++){
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		execmd(argv);
	}
	free(command_copy);
	free(command);
	return (0);
}

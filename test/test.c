#include "shell.h"

/**
 * main - main code
 * ac: argument count
 * av: argument vector
 * env: environment
 * Return: 0 on success
 */
int main(int ac, char **av, char *env[])
{
	char *token; char *command = NULL;
	char **arr;
	size_t n = 0;
	ssize_t num;
	pid_t my_pid;
	int status, i;

	(void)ac; (void)av;

	while (1)
	{
		printf("$ ");
		num = getline(&command, &n, stdin);
		if (num == -1){
			putchar('\n');
			free(command);
			return (-1);
		}

		token = strtok(command, " \n");
		arr = malloc(sizeof(char *) * num);
		arr[0] = token;
		if (strcmp(arr[0], "exit") == 0)
			exit(0);
		if (strcmp(arr[0], "env") == 0){
			for (i = 0; env[i] != NULL; i++)
				printf("%s\n", env[i]);
		}

		for (i = 1; token != NULL; i++){
			token = strtok(NULL, " \n");
			arr[i] = token;
		}

		my_pid = fork();
		if (my_pid == -1){
			perror("Error");
			return (1);
		}
		else if (my_pid == 0){
			execve(arr[0], arr, NULL);
			if (execve(arr[0], arr, NULL) == -1)
				perror("Error");
		}
		else{
			wait(&status);
		}
		
	}
	free(command);
	return (0);
}

#include "shell.h"

int main(int ac, char **av)
{
	char *token;
	char *command = NULL;
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
			return (-1);
		}

		token = strtok(command, " \n");
		char **arr = malloc(sizeof(char *) * num);
		arr[0] = token;
		if (strcmp(arr[0], "exit") == 0)
			exit(0);

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
		}
		else{
			wait(&status);
		}
		
	}
	free(command);
	return (0);
}

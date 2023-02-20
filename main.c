#include "shell.h"

int main(int ac, char **av)
{
	char *prompt = "$ "; char *buffer; char *buffer_copy;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " ";

	(void)ac; (void)av;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&buffer, &n, stdin);
		if (nchars_read == -1){
			printf("Exiting Shell...\n");
			return (-1);
		}
		printf("%s", buffer);
	}
	free(buffer);
	return (0);
}

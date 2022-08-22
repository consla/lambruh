#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[1024];

char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 1024, stdin);
	char* cpy = malloc(strlen(buffer+1));
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

void add_history(char* unused) {}

#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {

	puts("lambruh: lambda but bruh\n");
	
	for (;;) {
		char* input = readline("lambruh=> ");
		add_history(input);

		printf("%d\n", input);
		free(input);
	}

	return 0;
}

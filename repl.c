#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

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

int DEBUG = 1;

int get_string_l(char* str) {
	int pos = 0;

	while (str[pos] != '\0') {
		pos++;
	}

	return pos;
}

int main(int argc, char** argv) {

	mpc_parser_t* Decimal     = mpc_new("decimal");
	mpc_parser_t* Whole       = mpc_new("whole");
	mpc_parser_t* Number      = mpc_new("number");
	mpc_parser_t* Operator    = mpc_new("operator");
	mpc_parser_t* Exp         = mpc_new("exp");
	mpc_parser_t* Lambruh     = mpc_new("lambruh");

	mpca_lang(MPCA_LANG_DEFAULT,
	    "                                                                \
		decimal   : /-?[0-9]+\\.[0-9]+/ ;                             \
	        whole     : /-?[0-9]+/ ;                                     \
	        number    : <decimal> | <whole> ;                            \
		operator  : '+' | '-' | '*' | '/' | '%'                      \
		          | \"add\" | \"sub\" | \"mul\" | \"div\" ;          \
		exp       : <number> | '(' <operator> <exp>+ ')' ;           \
		lambruh   : /^/<exp>*/$/ ;                                   \
	    ", Decimal, Whole, Number, Operator, Exp, Lambruh);

	// mpca_lang(MPCA_LANG_DEFAULT,
	//     "                                                                \
	//         number    : /-?[0-9]+/ ;                                     \
	// 	decimal   : /-?[0-9]+\.[0-9]+/ ;                             \
	// 	operator  : '+' | '-' | '*' | '/' | '%'                      \
	// 	          | \"add\" | \"sub\" | \"mul\" | \"div\" ;          \
	// 	exp       : <number> | '(' <operator> <exp>+ ')' ;           \
	// 	lambruh   : /^/ <exp>+ /$/ ;                                 \
	//     ", Number, Operator, Exp, Lambruh);

	puts("lambruh: lambda but bruh\n");
	
	for (;;) {
		char* input = readline("lambruh=> ");
		if (&input[0] == '\0') {
			break;
		}
		add_history(input);

		mpc_result_t r;
		if (DEBUG) {
			printf("%s\n", input);
		}
		if (mpc_parse("<stdin>", input, Lambruh, &r)) {
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
			
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		if (DEBUG) {
			fputs("\n", stdout);
		}
		// printf("%s\n", input);
		free(input);
	}

	mpc_cleanup(6, Decimal, Whole, Number, Operator, Exp, Lambruh);

	return 0;
}

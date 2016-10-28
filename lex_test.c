#include <assert.h>
#include <stdio.h>

#include "lex.h"

int main() {
	struct lexer *l = lex_make();
	int status;
	
	if ((status = lex(l, "'hello'")) != 0) {
		printf("errored with %d\n", status);
	}
	
	if ((status = lex(l, "12345")) != 0) {
		printf("errored with %d\n", status);
	}
	
	if ((status = lex(l, "[ 1234, 4321, 2342 ]")) != 0)
		printf("errored with %d\n", status);
	
	if ((status = lex(l, "[ 'wow', \"wow\", 'wowza' ]")) != 0)
		printf("errored with %d\n", status);
		
	if ((status = lex(l, "{ \"hello\": \"wag1\" }")) != 0)
		printf("errored with %d\n", status);
	
	if ((status = lex(l, "{ \"hello\": \"wag1\", 'cool': 1234 }")) != 0)
		printf("errored with %d\n", status);
	
	struct token *tk;
	for (int i = 0; i < l->i; i++) {
		tk = *(l->tks+i);
		printf("token: %s %.*s\n", tt_string(tk->typ), tk->len, tk->st);
	}
	
	lex_delete(l);
}

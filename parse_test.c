#include <stdio.h>
#include <assert.h>

#include "lex.h"
#include "parse.h"

int main() {
	struct json *j = parse("[ 'hello', 1234, true ]");
	assert(j != NULL);

	printf("len: %d\n", j->num);
	struct ls_item *curr = j->val.arr;
	int i;
	for (i = 0; curr != NULL && i < j->num; curr = curr->next, i++) {
		printf("%d\n", i);
		print_json(curr->v);
	}
}

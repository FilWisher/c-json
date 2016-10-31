#include <stdio.h>
#include <assert.h>

#include "lex.h"
#include "parse.h"

int main() {
	struct json *j = parse("[ 'hello', 1234, true ]");
	assert(j != NULL);

	printf("len: %d\n", j->num);
	assert(j->typ == P_ARRAY);
	print_json(j);
}

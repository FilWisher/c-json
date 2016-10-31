#include <stdio.h>
#include <assert.h>

#include "hashtable.h"
#include "lex.h"
#include "parse.h"

int main() {
	struct json *jarray = parse("[ 'hello', 1234, true ]");
	assert(jarray != NULL);

	assert(jarray->typ == P_ARRAY);
	print_json(jarray);
	
	struct json *jobject = parse("{ 'hello': 1234 }");
	assert(jobject != NULL);
	
	assert(jobject->typ == P_OBJECT);
	
	struct json *val = ht_read(jobject->val.obj, "hello");
	assert(val != NULL);
	assert(val->typ == P_NUMBER);
	print_json(val);
	
}

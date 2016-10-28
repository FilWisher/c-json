#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "parse.h"
#include "hashtable.h"

int main() {

	struct hashtable *ht = ht_make();
	struct json *i = (struct json *)malloc(sizeof(struct json));
	i->typ = P_STRING;	
	i->num = 7;
	
	struct json *j = (struct json *)malloc(sizeof(struct json));
	j->typ = P_STRING;	
	j->num = 10;
	
	ht_insert(ht, "hello", i);
	ht_insert(ht, "boo", j);
	
	struct json *j2 = ht_read(ht, "hello");
	assert(j2 != NULL);
	assert(j2->num == 7);
	
	struct json *i2 = ht_read(ht, "boo");
	assert(i2 != NULL);
	assert(i2->num == 10);
	
	struct json *non = ht_read(ht, "ballywag");
	assert(non == NULL);

}
